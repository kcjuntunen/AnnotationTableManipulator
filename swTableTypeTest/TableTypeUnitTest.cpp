#include "stdafx.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

namespace swTableTypeTest {
  [TestClass]
  public ref class UnitTestForTableType {
  private:
    TestContext^ testContextInstance;

  public:
    /// <summary>
    ///Gets or sets the test context which provides
    ///information about and functionality for the current test run.
    ///</summary>
    property Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ TestContext
    {
      Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ get() {
        return testContextInstance;
      }
      System::Void set(Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ value) {
        testContextInstance = value;
      }
    };

#pragma region Additional test attributes
    //
    //You can use the following additional attributes as you write your tests:
    //
    //Use ClassInitialize to run code before running the first test in the class
    //[ClassInitialize()]
    //static void MyClassInitialize(TestContext^ testContext) {};
    //
    //Use ClassCleanup to run code after all tests in a class have run
    //[ClassCleanup()]
    //static void MyClassCleanup() {};
    //
    //Use TestInitialize to run code before running each test
    //[TestInitialize()]
    //void MyTestInitialize() {};
    //
    //Use TestCleanup to run code after each test has run
    //[TestCleanup()]
    //void MyTestCleanup() {};
    //
#pragma endregion 
    //[TestMethod]
    //void TestGetPartList() {
    //  swTableType::swTableType^ tt = gcnew swTableType::swTableType();
    //  System::Collections::Generic::List<String ^>^ slt;
    //  slt = tt->GetPartList();

    //  System::Diagnostics::Debug::Assert(slt != nullptr);
    //}

    //[TestMethod]
    //void TestGetParts() {
    //  swTableType::swTableType^ tt = gcnew swTableType::swTableType();
    //  System::Collections::Generic::Dictionary<String ^, Part^ >^ pp;
    //  pp = tt->GetParts();

    //  System::Diagnostics::Debug::Assert(pp != nullptr);
    //}

    //[TestMethod]
    //void TestColumnNotExist() {
    //  swTableType::swTableType^ tt = gcnew swTableType::swTableType();
    //  String^ s = tt->GetProperty("KOFX1502-05-02", "QQQ");
    //  System::Diagnostics::Debug::Assert(s == String::Empty);
    //}

    //[TestMethod]
    //void TestRowNotExist() {
    //  swTableType::swTableType^ tt = gcnew swTableType::swTableType();
    //  String^ s = tt->GetProperty("QQQ", "MATID");
    //  System::Diagnostics::Debug::Assert(s == String::Empty);
    //}

    //[TestMethod]
    //void TestLoop() {
    //  swTableType::swTableType^ tt = gcnew swTableType::swTableType();
    //  String^ s = String::Empty;
    //  for each (String^ x in tt->GetPartList()) {
    //    s = tt->GetProperty(x, "MATID");
    //  }

    //  System::Diagnostics::Debug::Print(s);
    //  System::Diagnostics::Debug::Assert(s == "1271");
    //};

    //[TestMethod]
    //void TestDirect() {
    //  swTableType::swTableType^ tt = gcnew swTableType::swTableType();
    //  String^ s = String::Empty;
    //  s = tt->GetProperty("KOFX1502-05-03", "DescriptION");

    //  System::Diagnostics::Debug::Print(s);
    //  System::Diagnostics::Debug::Assert(s == "PLATE");
    //}

    //[TestMethod]
    //void TestGetPart() {
    //  swTableType::swTableType^ tt = gcnew swTableType::swTableType();
    //  Part^ p = tt->GetPart("KOFX1502-05-02");
    //  double l = p->Length;
    //  System::Diagnostics::Debug::Assert(System::Math::Abs(l - 3.254) < .0005);
    //  int i = p->OpID[1];
    //  System::Diagnostics::Debug::Assert(i == 32);
    //}

    //[TestMethod]
    //void TestGetPartNoSuchPart() {
    //  // Checking for no exceptions.
    //  swTableType::swTableType^ tt = gcnew swTableType::swTableType();
    //  Part^ p = tt->GetPart("QQQQQQ");
    //  System::Diagnostics::Debug::Assert(p->Length == 0.0f);
    //}
  };
}
