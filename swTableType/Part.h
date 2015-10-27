#pragma once
#using <mscorlib.dll>

typedef System::String string;
typedef System::IO::FileInfo fileinfo;

public ref class Part {
private:
  unsigned int id;
  string^ part_number = string::Empty;
  string^ description = string::Empty;
  unsigned short quantity = 1;
  unsigned int matid = 2929;
  double l = 0.0f;
  double w = 0.0f;
  double t = 0.0f;
  unsigned short blank_qty = 0;
  double overl = 0.0f;
  double overw = 0.0f;
  string^ cnc1 = string::Empty;
  string^ cnc2 = string::Empty;
  array<short int>^ opid;
  unsigned int efid = 0;
  unsigned int ebid = 0;
  unsigned int elid = 0;
  unsigned int erid = 0;
  string^ comment = string::Empty;
  unsigned short deptid = 1;
  bool update_cnc = false;
  unsigned int hash;
  fileinfo^ fi;

  template<typename T>
  T parse(string^ input) {
    T tp;
    bool res = T::TryParse(input, tp);
    return tp;
  }

public:
  Part();
  static int PartCount = 0;
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
  void SetHash(string^ intHash);

  string^ str();

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

  property unsigned short Qty {
    unsigned short get() {
      return quantity;
    }
  }

  property unsigned int MaterialID {
    unsigned int get() {
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

  property unsigned short BlankQty {
    unsigned short get() {
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

  property unsigned short OpID[int] {
    unsigned short get(unsigned short ndx) {
      if (ndx > 0 && ndx < 6)
        return opid[ndx];
      else
        return 0;
    }
  }

  property unsigned int EdgeFrontID {
    unsigned int get() {
      return efid;
    }
  }

  property unsigned int EdgeBackID {
    unsigned int get() {
      return ebid;
    }
  }

  property unsigned int EdgeLeftID {
    unsigned int get() {
      return elid;
    }
  }

  property unsigned int EdgeRightID {
    unsigned int get() {
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

  property unsigned short DepartmentID {
    unsigned short get() {
      return deptid;
    }
  }

  property bool UpdateCNC {
    bool get() {
      return update_cnc;
    }
  }

  property unsigned int Hash {
    unsigned int get() {
      return hash;
    }
    void set(unsigned int value) {
      hash = value;
    }
  }

  property string^ FileName {
    string^ get() {
      return fi->Name->Split(' ', '.')[0];
    }
  }

  property string^ FullPath {
    string^ get() {
      return string::Format("{0}\\{1}", fi->Directory->FullName, FileName);
    }
  }

  property fileinfo^ FileInformation {
    fileinfo^ get() {
      return fi;
    }
    void set(fileinfo^ value) {
      fi = value;
    }

  }
};

