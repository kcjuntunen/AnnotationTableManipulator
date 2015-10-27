#include "stdafx.h"
#include "Part.h"


Part::Part() {
  opid = gcnew array<short int>(5);
  PartCount++;
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
  blank_qty = parse<unsigned short>(qty);
}

void Part::SetOverL(string^ over) {
  overl = parse<double>(over);
}

void Part::SetOverW(string^ over) {
  overw = parse<double>(over);
}

void Part::SetEdgeFrontID(string^ id) {
  efid = parse<unsigned int>(id);
}

void Part::SetEdgeBackID(string^ id) {
  ebid = parse<unsigned int>(id);
}

void Part::SetEdgeLeftID(string^ id) {
  elid = parse<unsigned int>(id);
}

void Part::SetEdgeRightID(string^ id) {
  erid = parse<unsigned int>(id);
}

void Part::SetDeptID(string^ id) {
  deptid = parse<unsigned short>(id);
}

void Part::SetUpdateCNC(string^ tf) {
  update_cnc = parse<bool>(tf);
}

void Part::SetOpID(string^ id, int opNo) {
  opid[opNo] = parse<unsigned short>(id);
}

void Part::SetHash(string^ hexhash) {
  try {
    hash = System::Convert::ToInt32(hexhash, 16);
  }
  catch (System::Exception ^e) {
    throw gcnew System::Exception("SetHash() threw an exception.", e);
  }
}

string^ Part::str() {
  return string::Format("PartNumber: {0}\nDescription: {1}\nQTY.: {2}\nMATID: {3}\nL: {4}\nW: {5}\nT: {6}\nBLANKQTY: {7}\nOVERL: {8}\nOVERW: {9}\nCNC1: {10}\nCNC2: {11}", 
    PartNumber, Description, Qty, MaterialID, Length, Width, Thickness, BlankQty, OverL, OverW, CNC1, CNC2);
}