#include "declerations.h"

#include <Core\Handler.h>

class Handler_Dumby : public Core::Handler<Handler_Dumby> {
public:
              Handler_Dumby ()                {}
              Handler_Dumby (const int val)   : m_val(val) {}
  const int   getVal        () const          { return m_val; };
  void        setVal        (const int val)   { m_val = val; }
private:
  int         m_val         { 0 };
};

namespace Core_Test {

  void Handler::Reset() {
    Handler_Dumby::DestroyAll();
  }

  void Handler::Examine() {
    TestCase([]() {
      Handler_Dumby dud;
      return Handler_Dumby::getCount() == 0;
    }, "Handler::Handler");

    TestCase([]() {
      Handler_Dumby::Create();
      return Handler_Dumby::getCount() == 1;
    }, "Handler::Create");

    TestCase([]() {
      Handler_Dumby* dud = Handler_Dumby::Create();
      return dud->getIndex() == 0;
    }, "Handler::getIndex");

    TestCase([]() {
      Handler_Dumby* dud = Handler_Dumby::Create(1);
      return dud->getVal() == 1;
    }, "Handler::getVal");

    TestCase([]() {
      Handler_Dumby::Create();
      Handler_Dumby::Create();
      Handler_Dumby::Destroy(1);
      return Handler_Dumby::getCount() == 1;
    }, "Handler::Destroy(int)");

    TestCase([]() {
      Handler_Dumby::Destroy(Handler_Dumby::Create());
      return Handler_Dumby::getCount() == 0;
    }, "Handler::Destroy(const Handler*)");

    TestCase([]() {
      Handler_Dumby::Create();
      Handler_Dumby::Destroy(Handler_Dumby::Create());
      Handler_Dumby::Create();
      return Handler_Dumby::getCount() == 2;
    }, "Handler::Count");

    TestCase([]() {
      Handler_Dumby::Create();
      Handler_Dumby::Create(3);
      Handler_Dumby::Create(2);
      auto list = Handler_Dumby::getAll();
      return list[1]->getVal() == 3;
    }, "Handler::getAll");

    TestCase([]() {
      Handler_Dumby::Create();
      Handler_Dumby::Create(3);
      Handler_Dumby::Create();
      return Handler_Dumby::getWithIndex(1)->getVal() == 3;
    }, "Handler::getWithIndex");

    TestCase([]() {
      Handler_Dumby::Create();
      Handler_Dumby::Create(3);
      Handler_Dumby::Create();

      Handler_Dumby* ptr = Handler_Dumby::getWhere([](auto ptr) { return ptr->getIndex() == 1; });
      return ptr->getVal() == 3;
    }, "Handler::getWhere");

    TestCase([]() {
      Handler_Dumby* ptr1 = Handler_Dumby::Create(0);
      Handler_Dumby* ptr2 = Handler_Dumby::Create(3);

      Handler_Dumby::forEach([](auto ptr) { ptr->setVal(1); });
      return ptr1->getVal() == 1 && ptr1->getVal() == 1;
    }, "Handler::forEach");
  }
}