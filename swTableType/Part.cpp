#include "stdafx.h"
#include "Part.h"


Part::Part() {
	opid = gcnew array<int>(5);
}

void Part::SetQuantity(string^ qty) {
	//int tp = 1;
	//if (int::TryParse(qty, tp)) {
	//	quantity = tp;
	//}
	quantity = parse<int>(qty);
}

void Part::SetMaterialID(string^ id) {
	matid = parse<int>(id);
}

void Part::SetLength(string^ len) {
	l = parse<double>(len);
}

void Part::SetWidth(string^ wid) {
	w = parse<double>(wid);
}

void Part::SetThickness(string^ thk) {
	t = parse<double>(thk);
}

void Part::SetBlankQty(string^ qty) {
	blank_qty = parse<int>(qty);
}

void Part::SetOverL(string^ over) {
	overl = parse<double>(over);
}

void Part::SetOverW(string^ over) {
	overw = parse<double>(over);
}

void Part::SetEdgeFrontID(string^ id) {
	efid = parse<int>(id);
}

void Part::SetEdgeBackID(string^ id) {
	ebid = parse<int>(id);
}

void Part::SetEdgeLeftID(string^ id) {
	elid = parse<int>(id);
}

void Part::SetEdgeRightID(string^ id) {
	erid = parse<int>(id);
}

void Part::SetDeptID(string^ id) {
	deptid = parse<int>(id);
}

void Part::SetUpdateCNC(string^ tf) {
	update_cnc = parse<bool>(tf);
}

void Part::SetOpID(string^ id, int opNo) {
	opid[opNo] = parse<int>(id);
}