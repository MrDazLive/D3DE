#include "declerations.h"

#include <Core/Observer.h>

class Observable_Dumby;

namespace Core {
  OBSERVER_CLASS(Observable_Dumby) {
  public:
    const int   getVal  () const          { return m_val; };
    void        setVal  (const int val)   { m_val = val; }
  private:
    int         m_val   { 0 };
  };
}

class Observable_Dumby : public Core::Observable<Observable_Dumby> {
public:
  void        setVal  (const int v) { NotifyObservers(&Observer::setVal, v); }
};

template <>
std::set <Core::Observable<Observable_Dumby>::Observer*> Core::Observable<Observable_Dumby>::s_globalObservers = {};

namespace Core_Test {

  void Observer::Reset() {

  }

  void Observer::Examine() {
    TestCase([]() {
      Observable_Dumby d1;
      Observable_Dumby::Observer o1;

      d1.AddObserver(&o1);
      d1.setVal(2);

      return o1.getVal() == 2;
    }, "Observable::AddObserver");

    TestCase([]() {
      Observable_Dumby d1;
      Observable_Dumby::Observer o1;

      d1.AddObserver(&o1);
      d1.RemoveObserver(&o1);
      d1.setVal(2);

      return o1.getVal() == 0;
    }, "Observable::RemoveObserver");

    TestCase([]() {
      Observable_Dumby::Observer o1;

      Observable_Dumby::AddGlobalObserver(&o1);

      Observable_Dumby d1;
      d1.setVal(2);

      return o1.getVal() == 2;
    }, "Observable::AddGlobalObserver");

    TestCase([]() {
      Observable_Dumby::Observer o1;

      Observable_Dumby::AddGlobalObserver(&o1);
      Observable_Dumby::RemoveGlobalObserver(&o1);

      Observable_Dumby d1;
      d1.setVal(2);

      return o1.getVal() == 0;
    }, "Observable::RemoveGlobalObserver");

    TestCase([]() {
      Observable_Dumby d1;
      Observable_Dumby d2;
      return Observable_Dumby::GetObservables().size() == 2;
    }, "Observable::GetObservables");

    TestCase([]() {
      Observable_Dumby d1;

      Observable_Dumby::Observer o1;
      Observable_Dumby::Observer o2;

      d1.AddObserver(&o1);
      d1.AddObserver(&o1);
      d1.AddObserver(&o2);

      return d1.ObserverCount() == 2;
    }, "Observable::ObserverCount");

    TestCase([]() {
      Observable_Dumby::Observer o1;
      Observable_Dumby::Observer o2;

      Observable_Dumby::AddGlobalObserver(&o1);
      Observable_Dumby::AddGlobalObserver(&o1);
      Observable_Dumby::AddGlobalObserver(&o2);

      return Observable_Dumby::GlobalObserverCount() == 2;
    }, "Observable::GlobalObserverCount");

    TestCase([]() {
      Observable_Dumby d1;
      {
        Observable_Dumby::Observer o1;
        Observable_Dumby::AddGlobalObserver(&o1);
      }
      return d1.ObserverCount() == 0 && Observable_Dumby::GlobalObserverCount() == 0;
    }, "Observer::~Observer");
  }

}