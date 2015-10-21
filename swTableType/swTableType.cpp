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
					insert_parts();
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

		col_count = swTable->RowCount;
		row_count = swTable->ColumnCount;

		part_table = gcnew array<string^, 2>(col_count, row_count);
		if (swTable) {
			for (int i = 0; i < col_count; i++) {
				for (int j = 0; j < row_count; j++) {
					part_table[i, j] = swTable->DisplayedText[i, j];
				}
			}
		}
	}

	void swTableType::insert_parts() {
		for (int i = 1; i < RowCount; i++) {
			insert_part(i);
		}
	}

	void swTableType::insert_part(int prt) {
		Part^ p = gcnew Part();
		p->PartNumber = get_property(prt, "PART");
		p->Description = get_property(prt, "DESCRIPTION");
		p->SetQuantity(get_property(prt, "QTY."));
		p->SetMaterialID(get_property(prt, "MATID"));
		p->SetLength(get_property(prt, "L"));
		p->SetWidth(get_property(prt, "W"));
		p->SetThickness(get_property(prt, "T"));
		p->SetBlankQty(get_property(prt, "BLANK QTY"));
		p->SetOverL(get_property(prt, "OVERL"));
		p->SetOverW(get_property(prt, "OVERW"));
		p->CNC1 = get_property(prt, "CNC1");
		p->CNC2 = get_property(prt, "CNC2");
		string^ op = string::Empty;
		for (int i = 0; i < 5; i++) {
			op = string::Format("OP{0}ID", i + 1);
			p->SetOpID(get_property(prt, op), i);
		}

		p->SetEdgeFrontID(get_property(prt, "FEDGEID"));
		p->SetEdgeBackID(get_property(prt, "BEDGEID"));
		p->SetEdgeLeftID(get_property(prt, "LEDGEID"));
		p->SetEdgeRightID(get_property(prt, "REDGEID"));
		p->Comment = get_property(prt, "COMMENT");
		p->SetDeptID(get_property(prt, "DEPTID"));
		p->SetUpdateCNC(get_property(prt, "UPDATE_CNC"));
		if (!parts->ContainsKey(p->PartNumber)) {
			parts->Add(p->PartNumber, p);
		}
	}

	string^ swTableType::get_property_by_part(string^ part, string^ prop, string^ part_column_name) {
		int prtcol = get_column_by_name(part_column_name);
		int prpcol = get_column_by_name(prop);
		string^ res = string::Empty;

		for (int i = 0; i < RowCount; i++) {
			if (part_table[prtcol, i]->Trim()->ToUpper()->Equals(prop->ToUpper())) {
				res = part_table[i, prpcol];
			}
		}
		return res;
	}

	string^ swTableType::get_property_by_part(int row, string^ prop, string^ part_column_name) {
		int prtcol = get_column_by_name(part_column_name);
		int prpcol = get_column_by_name(prop);
		string^ res = string::Empty;

		for (int i = 0; i < RowCount; i++) {
			if (part_table[prtcol, i]->Trim()->ToUpper()->Equals(prop->ToUpper())) {
				res = part_table[i, prpcol];
			}
		}
		return res;
	}

	string^ swTableType::get_property(string^ part, string^ prop) {
		return get_property_by_part(part, prop, part_column);
	}

	string^ swTableType::get_property(int row, string^ prop) {
		return get_property_by_part(row, prop, part_column);
	}

	int swTableType::get_column_by_name(string^ prop) {
		int res = 0;
		for (int i = 0; i < ColumnCount; i++) {
			if (part_table[0, i]->Trim()->ToUpper()->Equals(prop->ToUpper())) {
				res = i;
			}
		}
		return res;
	}
}