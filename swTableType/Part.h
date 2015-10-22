#pragma once
#using <mscorlib.dll>

typedef System::String string;
public ref class Part {
private:
  string^ part_number = string::Empty;
  string^ description = string::Empty;
  int quantity = 1;
  int matid = 2929;
  double l = 0.0f;
  double w = 0.0f;
  double t = 0.0f;
  int blank_qty = 0;
  double overl = 0.0f;
  double overw = 0.0f;
  string^ cnc1 = string::Empty;
  string^ cnc2 = string::Empty;
  array<int>^ opid;
  int efid = 0;
  int ebid = 0;
  int elid = 0;
  int erid = 0;
  string^ comment = string::Empty;
  int deptid = 1;
  bool update_cnc = false;

  template<typename T>
  T parse(string^ input) {
    T tp;
    bool res = T::TryParse(input, tp);
    return tp;
  }
public:
  Part();
  void SetQuantity(string^ qty);
  void SetMaterialID(string^ id);
  void SetLength(string^ len);
  void SetWidth(string^ wid);
  void SetThickness(string^ thk);
  void SetBlankQty(string^ qty);
  void SetOverL(string^ over);
  void SetOverW(string^ over);
  void SetEdgeFrontID(string^ id);
  void SetEdgeBackID(string^ id);
  void SetEdgeLeftID(string^ id);
  void SetEdgeRightID(string^ id);
  void SetDeptID(string^ id);
  void SetUpdateCNC(string^ tf);
  void SetOpID(string^ id, int opNo);



  property string^ PartNumber {
    string^ get() {
      return part_number;
    }

    void set(string^ value) {
      part_number = value;
    }
  }

  property string^ Description {
    string^ get() {
      return description;
    }

    void set(string^ value) {
      description = value;
    }
  }

  property int Qty {
    int get() {
      return quantity;
    }
  }

  property int MaterialID {
    int get() {
      return matid;
    }
  }

  property double Length {
    double get() {
      return l;
    }
  }

  property double Width {
    double get() {
      return w;
    }
  }

  property double Thickness {
    double get() {
      return t;
    }
  }

  property int BlankQty {
    int get() {
      return blank_qty;
    }
  }

  property double OverL {
    double get() {
      return overl;
    }
  }

  property double OverW {
    double get() {
      return overw;
    }
  }

  property string^ CNC1 {
    string^ get() {
      return cnc1;
    }

    void set(string^ value) {
      cnc1 = value;
    }
  }

  property string^ CNC2 {
    string^ get() {
      return cnc2;
    }

    void set(string^ value) {
      cnc2 = value;
    }
  }

  property int OpID[int] {
    int get(int ndx) {
      if (ndx > 0 && ndx < 6)
        return opid[ndx];
      else
        return 0;
    }
  }

  property int EdgeFrontID {
    int get() {
      return efid;
    }
  }

  property int EdgeBackID {
    int get() {
      return ebid;
    }
  }

  property int EdgeLeftID {
    int get() {
      return elid;
    }
  }

  property int EdgeRightID {
    int get() {
      return erid;
    }
  }

  property string^ Comment {
    string^ get() {
      return comment;
    }

    void set(string^ value) {
      comment = value;
    }
  }

  property int DepartmentID {
    int get() {
      return deptid;
    }
  }

  property bool UpdateCNC {
    bool get() {
      return update_cnc;
    }
  }
};

