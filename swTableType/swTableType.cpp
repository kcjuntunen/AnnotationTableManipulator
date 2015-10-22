// This is the main DLL file.

#include "stdafx.h"
#include "swTableType.h"

namespace swTableType {
  swTableType::swTableType() {
    swApp = gcnew SldWorksClass;

    if (!swApp)
      got_sw = false;
    else
      got_sw = true;

    if (got_sw) {
      swApp->Visible = true;
      part = swApp->IActiveDoc2;
      swSelMgr = part->ISelectionManager;

      if (part != nullptr && swSelMgr != nullptr) {
        IBomFeature^ swBom = (IBomFeature^)swSelMgr->GetSelectedObject6(1, -1);
        if (swBom != nullptr) {
          fill_table(swBom);
          //insert_parts();
        }
        else {
          int butn = (int)SolidWorks::Interop::swconst::swMessageBoxBtn_e::swMbOk;
          int icon = (int)SolidWorks::Interop::swconst::swMessageBoxIcon_e::swMbStop;
          swApp->SendMsgToUser2("Must select a Bom.", icon, butn);
        }
      }
    }
  }

  swTableType::~swTableType() {
    // Destructor
  }

  void swTableType::fill_table(IBomFeature^ bom) {
    swTable = (ITableAnnotation^)bom->IGetTableAnnotations(1);
    part->ClearSelection2(true);

    col_count = swTable->ColumnCount;
    row_count = swTable->RowCount;
    //parts = gcnew System::Collections::Generic::Dictionary<string^, Part^>(row_count);

    //part_table = gcnew array<string^, 2>(row_count, col_count);
    //if (swTable) {
    //  for (int i = 0; i < row_count; i++) {
    //    for (int j = 0; j < col_count; j++) {
    //      part_table[i, j] = swTable->DisplayedText[i, j];
    //    }
    //  }
    //}
  }

  void swTableType::insert_parts() {
    for (int i = 1; i < row_count; i++) {
      insert_part(i);
    }
  }

  void swTableType::insert_part(int prt) {
    Part^ p = gcnew Part();
    p->PartNumber = GetProperty(prt, "PART");
    p->Description = GetProperty(prt, "DESCRIPTION");
    p->SetQuantity(GetProperty(prt, "QTY."));
    p->SetMaterialID(GetProperty(prt, "MATID"));
    p->SetLength(GetProperty(prt, "L"));
    p->SetWidth(GetProperty(prt, "W"));
    p->SetThickness(GetProperty(prt, "T"));
    p->SetBlankQty(GetProperty(prt, "BLANK QTY"));
    p->SetOverL(GetProperty(prt, "OVERL"));
    p->SetOverW(GetProperty(prt, "OVERW"));
    p->CNC1 = GetProperty(prt, "CNC1");
    p->CNC2 = GetProperty(prt, "CNC2");
    string^ op = string::Empty;
    for (int i = 0; i < 5; i++) {
      op = string::Format("OP{0}ID", i + 1);
      p->SetOpID(GetProperty(prt, op), i);
    }

    p->SetEdgeFrontID(GetProperty(prt, "EFID"));
    p->SetEdgeBackID(GetProperty(prt, "EBID"));
    p->SetEdgeLeftID(GetProperty(prt, "ELID"));
    p->SetEdgeRightID(GetProperty(prt, "ERID"));
    p->Comment = GetProperty(prt, "COMMENT");
    p->SetDeptID(GetProperty(prt, "DEPT"));
    p->SetUpdateCNC(GetProperty(prt, "UPDATE_CNC"));

    parts->Add(p->PartNumber, p);
    if (!parts->ContainsKey(p->PartNumber)) {
      parts->Add(p->PartNumber, p);
    }
  }

  string^ swTableType::get_property_by_part(string^ prt, string^ prop, string^ part_column_name) {
    int prtrow = get_row_by_partname(prt);
    int prpcol = get_column_by_name(prop);
    return (prpcol < 1 || prtrow < 1) ? string::Empty : swTable->DisplayedText[prtrow, prpcol];
  }

  string^ swTableType::get_property_by_part(int row, string^ prop, string^ part_column_name) {
    int prpcol = get_column_by_name(prop);
    return (prpcol < 1 || row < 1) ? string::Empty : swTable->DisplayedText[row, prpcol];
  }

  int swTableType::get_column_by_name(string^ prop) {
    for (int i = 0; i < col_count; i++) {
      if (swTable->DisplayedText[0, i]->Trim()->ToUpper()->Equals(prop->ToUpper())) {
        return i;
      }
    }
    return 0;
  }

  int swTableType::get_row_by_partname(string^ prt) {
    int prtcol = get_column_by_name(part_column);
    for (int i = 0; i < row_count; i++) {
      if (swTable->DisplayedText[i, prtcol]->Trim()->ToUpper()->Equals(prt->Trim()->ToUpper())) {
        return i;
      }
    }
    return 0;
  }

  void swTableType::traverse_tables() {

  }

  bool swTableType::identify_table(ITableAnnotation^ table, string^ tablehash) {
    string^ str = string::Empty;
    for (int i = 0; i < col_count; i++) {
      str += string::Format("{0}|", table->DisplayedText[0, i]->ToUpper());
    }
    System::IO::Stream^ columns = gcnew System::IO::MemoryStream();

    columns->Write(System::Text::Encoding::UTF8->GetBytes(str), 0, str->Length - 1);
    string^ hash = System::BitConverter::ToString(MD5::Create()->ComputeHash(columns));

    return hash == tablehash;
  }

  string^ swTableType::GetProperty(string^ part, string^ prop) {
    return get_property_by_part(part, prop, part_column);
  }

  string^ swTableType::GetProperty(int row, string^ prop) {
    return get_property_by_part(row, prop, part_column);
  }

  string_list_type^ swTableType::GetParts() {
    int prtcol = get_column_by_name(part_column);
    string_list_type^ slt = gcnew string_list_type();
    for (int i = 1; i < row_count; i++) {
      slt->Add(swTable->DisplayedText[i, prtcol]->ToString());
    }
    return slt;
  }
}