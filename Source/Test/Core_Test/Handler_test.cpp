#include "declerations.h"

#include <Core\Handler.h>


namespace Core_Test {

  class Dumby : public Core::Handler<Dumby> {
  public:
                Dumby   ()                {}
                Dumby   (const int val)   : m_val(val) {}
    const int   getVal  () const          { return m_val; };
    void        setVal  (const int val)   { m_val = val; }
  private:
    int         m_val   { 0 };
  };

  void Handler::Reset() {
    Dumby::DestroyAll();
  }

  void Handler::Examine() {
    TestCase([]() {
      Dumby dud;
      return Dumby::getCount() == 0;
    }, "Handler::Handler");

    TestCase([]() {
      Dumby::Create();
      return Dumby::getCount() == 1;
    }, "Handler::Create");

    TestCase([]() {
      Dumby* dud = Dumby::Create();
      return dud->getIndex() == 0;
    }, "Handler::getIndex");

    TestCase([]() {
      Dumby* dud = Dumby::Create(1);
      return dud->getVal() == 1;
    }, "Handler::getVal");

    TestCase([]() {
      Dumby::Create();
      Dumby::Create();
      Dumby::Destroy(1);
      return Dumby::getCount() == 1;
    }, "Handler::Destroy(int)");

    TestCase([]() {
      Dumby::Destroy(Dumby::Create());
      return Dumby::getCount() == 0;
    }, "Handler::Destroy(const Handler*)");

    TestCase([]() {
      Dumby::Create();
      Dumby::Destroy(Dumby::Create());
      Dumby::Create();
      return Dumby::getCount() == 2;
    }, "Handler::Count");

    TestCase([]() {
      Dumby::Create();
      Dumby::Create(3);
      Dumby::Create(2);
      auto list = Dumby::getAll();
      return list[1]->getVal() == 3;
    }, "Handler::getAll");

    TestCase([]() {
      Dumby::Create();
      Dumby::Create(3);
      Dumby::Create();
      return Dumby::getWithIndex(1)->getVal() == 3;
    }, "Handler::getWithIndex");

    TestCase([]() {
      Dumby::Create();
      Dumby::Create(3);
      Dumby::Create();

      Dumby* ptr = Dumby::getWhere([](auto ptr) { return ptr->getIndex() == 1; });
      return ptr->getVal() == 3;
    }, "Handler::getWhere");

    TestCase([]() {
      Dumby* ptr1 = Dumby::Create(0);
      Dumby* ptr2 = Dumby::Create(3);

      Dumby::forEach([](auto ptr) { ptr->setVal(1); });
      return ptr1->getVal() == 1 && ptr1->getVal() == 1;
    }, "Handler::forEach");
  }
}