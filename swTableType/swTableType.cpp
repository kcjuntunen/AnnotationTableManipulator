// This is the main DLL file.

#include "stdafx.h"
#include "swTableType.h"

namespace swTableType {
  swTableType::swTableType(IModelDoc2^ md, array<string^>^ tablehashes) {
    master_hashes = tablehashes;
    cols = gcnew string_list_type();
    prts = gcnew string_list_type();
    path_list = gcnew fi_list_type();
    part = md;
    swSelMgr = part->ISelectionManager;
    if (part != nullptr && swSelMgr != nullptr) {
        IBomFeature^ swBom = nullptr;
        
        try {
          swBom = (IBomFeature^)swSelMgr->GetSelectedObject6(1, -1);
        } catch (System::Exception^) {
            // Not an IBomFeature
        }

      if (swBom != nullptr) {
        fill_table(swBom);
      }
      else {
        find_bom();
      }
    }
  }

  swTableType::~swTableType() {
    // Destructor
  }

  void swTableType::fill_table(IBomFeature^ bom) {
    string ^itno = string::Empty;
    string ^ptno = string::Empty;
    cols->Clear();
    prts->Clear();
    swTable = (ITableAnnotation^)bom->IGetTableAnnotations(1);
    part->ClearSelection2(true);
    
    int count = 0;

    col_count = swTable->ColumnCount;
    row_count = swTable->RowCount;
    for (int i = 0; i < col_count; i++) {
      cols->Add(swTable->DisplayedText[0, i]);
    }
        
    Object^ ta = bom->GetTableAnnotations();
    count = bom->GetTableAnnotationCount();
    array<Object^>^ bomtaa = gcnew array<Object^>(count);
    bomtaa = (array<Object^>^)bom->GetTableAnnotations();
    SolidWorks::Interop::sldworks::BomTableAnnotation^ bta = (SolidWorks::Interop::sldworks::BomTableAnnotation^)bomtaa[0];
    int prtcol = get_column_by_name(part_column);
    for (int i = 0; i < row_count; i++) {
      string^ dt = swTable->DisplayedText[i, prtcol];
      prts->Add(dt);
      array<string^>^ pathnames = gcnew array<string^>(count);
      pathnames = (array<string^>^)bta->GetModelPathNames(i, itno, ptno);
      if (pathnames != nullptr) {
        for each (string ^v in pathnames) {
          path_list->Add(gcnew FileInfo(v));
        }
      }
    }

    initialated = true;
  }

  void swTableType::insert_parts() {
    for (int i = 1; i < row_count; i++) {
      insert_part(i);
    }
  }

  void swTableType::insert_part(int prt) {
    Part^ p = return_part(prt);

    if (!parts->ContainsKey(p->PartNumber)) {
      parts->Add(p->PartNumber, p);
    }
  }

  Part^ swTableType::return_part(int prt) {
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
    p->SetDeptID(GetProperty(prt, "DEPTID"));
    p->SetUpdateCNC(GetProperty(prt, "UPDATE CNC")->ToUpper()->Contains("Y") ? "True" : "False");
    p->SetHash(GetProperty(prt, "CRC32"));
    return p;
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
    if (!initialated) {
      for (int i = 0; i < col_count; i++) {
        if (swTable->DisplayedText[0, i]->Trim()->ToUpper()->Equals(prop->ToUpper())) {
          return i;
        }
      }
    }
    else {
      int count = 0;
      for each (string^ s in cols) {
        if (s->ToUpper()->Trim()->Equals(prop->ToUpper()->Trim())) {
          return count;
        }
        count++;
      }
    }
    return 0xffffffff;
  }

  int swTableType::get_row_by_partname(string^ prt) {
    if (!initialated) {
      int prtcol = get_column_by_name(part_column);
      for (int i = 0; i < row_count; i++) {
        if (swTable->DisplayedText[i, prtcol]->Trim()->ToUpper()->Equals(prt->Trim()->ToUpper())) {
          return i;
        }
      }
    }
    return prts->IndexOf(prt);
  }

  void swTableType::find_bom() {
    bool found = false;
    IFeature^ feature = (IFeature^)part->FirstFeature();
    if (part != nullptr) {
      while (feature != nullptr) {
        if (feature->GetTypeName2()->ToUpper() == "BOMFEAT") {
          feature->Select2(false, -1);
          IBomFeature^ bom = (IBomFeature^)swSelMgr->GetSelectedObject6(1, -1);
          fill_table(bom);
          if (identify_table(cols, master_hashes)) {
            found = true;
            break;
          }
        }
        feature = (IFeature^)feature->GetNextFeature();
      }
    }
    if (!found) {
      throw gcnew System::NullReferenceException("I can't find a table anywhere.");
    }
  }

  bool swTableType::identify_table(string_list_type^ table, array<string^>^ tablehashes) {
    bool match = false;
    string^ str = string::Empty;
    array<string^>^ ss = gcnew array<string^>(table->Count);
    table->CopyTo(ss);
    System::Array::Sort(ss);
    for each (string^ s in ss) {
      str += string::Format("{0}|", s->ToUpper());
    }

    System::IO::Stream^ columns = gcnew System::IO::MemoryStream();
    columns->Write(System::Text::Encoding::UTF8->GetBytes(str), 0, str->Length - 1);

    string^ hash = System::BitConverter::ToString(MD5::Create()->ComputeHash(to_byte_array(str)));
    for each (string^ h in tablehashes) {
      match |= hash == h;
    }
    return match;
  }

  bool swTableType::match_filter(string^ s, array<string^>^ filter_strings) {
    string^ pn = s->Trim();
    for each (string^ pattern in filter_strings) {
      Regex ^r = gcnew Regex(pattern);
      if (r->IsMatch(pn))
        return true;
    }

    return false;
  }

  array<byte>^ swTableType::to_byte_array(string^ s) {
    array<byte>^ ba = gcnew array<byte>(s->Length);
    int count = 0;
    for each (char c in s) {
      ba[count] = (byte)c;
      count++;
    }
    return ba;
  }

  string^ swTableType::GetProperty(string^ part, string^ prop) {
    return get_property_by_part(part, prop, part_column);
  }

  string^ swTableType::GetProperty(int row, string^ prop) {
    return get_property_by_part(row, prop, part_column);
  }

  string_list_type^ swTableType::GetPartList() {
    string_list_type^ slt = gcnew string_list_type();
    for (int i = 1; i < row_count; i++) {
      slt->Add(prts[i]);
    }
    return slt;
  }

  Parts^ swTableType::GetParts() {
    parts = gcnew Parts();
    for each (string^ s in GetPartList()) {
      parts->Add(s, GetPart(s));
    }
    return parts;
  }

  Parts^ swTableType::GetParts(array<string^>^ filter_strings) {
    parts = gcnew Parts();
    for each (string^ s in GetPartList()) {
      if (match_filter(s, filter_strings) && !parts->ContainsKey(s)) {
        parts->Add(s, GetPart(s));
      }
    }
    return parts;
  }

  Part^ swTableType::GetPart(string^ prt) {
    int prtrow = get_row_by_partname(prt);
    return return_part(prtrow);
  }

  Part^ swTableType::GetPart(int row) {
    return return_part(row);
  }
}
