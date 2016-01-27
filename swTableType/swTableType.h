// swTableType.h

#using <mscorlib.dll>
#include "Part.h"
#pragma once

namespace swTableType {
  typedef SolidWorks::Interop::sldworks::SelectionMgr SelectionMgr;
  typedef SolidWorks::Interop::sldworks::BomFeature BomFeature;
  typedef SolidWorks::Interop::sldworks::TableAnnotation TableAnnotation;
  typedef SolidWorks::Interop::sldworks::IModelDoc2 IModelDoc2;
  typedef SolidWorks::Interop::sldworks::SldWorksClass SldWorksClass;
  typedef SolidWorks::Interop::sldworks::ISldWorks ISldWorks;
  typedef SolidWorks::Interop::sldworks::ITableAnnotation ITableAnnotation;
  typedef SolidWorks::Interop::sldworks::IFeature IFeature;
  typedef SolidWorks::Interop::sldworks::IBomTableAnnotation IBomTableAnnotation;
  typedef SolidWorks::Interop::sldworks::IBomFeature IBomFeature;
  typedef System::Collections::Generic::List<ITableAnnotation^> ita_list_type;

  typedef System::String string;
  typedef System::Collections::Generic::List<string^> string_list_type;
  typedef System::Collections::Generic::List<int> int_list_type;
  typedef System::Collections::Generic::Dictionary<string^, Part^>  Parts;
  typedef System::Security::Cryptography::MD5 MD5;
  typedef System::Byte byte;

  public ref class swTableType {
  private:
    SelectionMgr^ swSelMgr;
    //TableAnnotation^ swTableAnn;
    ITableAnnotation^ swTable;
    IModelDoc2^ part;
    //string_list_type slt;
    string^ part_column = "PART";
    string^ inc_column = "INCLUDE IN CUTLIST";
    string^ master_hash;
    //array<string^, 2>^ part_table;
    string_list_type^ cols;
    string_list_type^ prts;
    int row_count = 0;
    int col_count = 0;
    bool initialated = false;
    void fill_table(IBomFeature^ bom);
    void insert_part(int prt);
    void insert_parts();
    string^ get_property_by_part(string^ part, string^ prop, string^ part_column_name);
    string^ get_property_by_part(int row, string^ prop, string^ part_column_name);

    string^ get_cell_contents(int col, int row) { return swTable->DisplayedText[col, row]; }
    string^ get_column_heading(int col) { return swTable->DisplayedText[col, 0]; }
    void set_part_column(string^ name) { part_column = name; }
    void set_include_column(string^ name) { inc_column = name; }

    int get_column_by_name(string^ prop);
    int get_row_by_partname(string^ prt);
    Part^ return_part(int prt);

    void find_bom();
    bool identify_table(string_list_type^ table, string^ tablehash);
    static array<byte>^ swTableType::to_byte_array(string^ s);

    property int ColumnCount {
      int get() { return col_count; }
    }

    property int RowCount {
      int get() { return row_count; }
    }

    Parts^ parts;
    ISldWorks^ swApp;
  public:

    //swTableType();
    swTableType(IModelDoc2^ md, string^ tablehash);
    ~swTableType();
    Part^ GetPart(string^ part);
    Part^ GetPart(int row);
    string^ GetProperty(string^ part, string^ prop);
    string^ GetProperty(int row, string^ prop);
    string_list_type^ GetPartList();
    Parts^ GetParts();

    property ISldWorks^ SldWorksApp {
      ISldWorks^ get() {
        return swApp;
      }

      void set(ISldWorks^ value) {
        swApp = value;
      }
    }
  };
}
