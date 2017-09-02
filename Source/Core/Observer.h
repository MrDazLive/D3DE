#pragma once

#include <list>
#include <functional>

namespace Core {

  template <typename T>
  class Observer {
  public:
    virtual                           ~Observer             ();
  };

  template <typename T>
  class Observable {
  public:
                                      Observable            ();
                                      ~Observable           ();

    void                              AddObserver           (Observer<T>* const);
    void                              RemoveObserver        (Observer<T>* const);

    static void                       AddGlobalObserver     (Observer<T>* const);
    static void                       RemoveGlobalObserver  (Observer<T>* const);
  protected:
    template <typename U>
    void                              NotifyObservers       (std::function<void(U*)>);
  private:
    std::list<Observer<T>*>           m_observers           {};
    static std::list<Observable<T>*>  s_observables;
  };

  template <typename T>
  std::list<Observable<T>*> Observable<T>::s_observables = {};

  template <typename T>
  Observer<T>::~Observer() {
    Observable<T>::RemoveGlobalObserver(this);
  }

  template <typename T>
  Observable<T>::Observable() {
    s_observables.push_back(this);
  }

  template <typename T>
  Observable<T>::~Observable() {
    s_observables.remove(this);
  }

  template <typename T>
  void Observable<T>::AddObserver(Observer<T>* const ptr) {
    if (!m_observers.empty() && std::find(m_observers.begin(), m_observers.end(), ptr) != m_observers.end()) {
      m_observers.push_back(ptr);
    }
  }

  template <typename T>
  void Observable<T>::RemoveObserver(Observer<T>* const ptr) {
    m_observers.remove(ptr);
  }

  template <typename T>
  void Observable<T>::AddGlobalObserver(Observer<T>* const ptr) {
    for (Observable<T>* const obs : s_observables) {
      obs->AddObserver(ptr);
    }
  }

  template <typename T>
  void Observable<T>::RemoveGlobalObserver(Observer<T>* const ptr) {
    for (Observable<T>* const obs : s_observables) {
      obs->RemoveObserver(ptr);
    }
  }

  template <typename T>
  template <typename U>
  void Observable<T>::NotifyObservers(std::function<void(U*)> function) {
    for (Observer<T>* const ptr : m_observers) {
      function((U*)ptr);
    }
  }

#define NOTIFY_OBSERVERS(OBS, FUNC)                             \
  NotifyObservers<OBS>([&](OBS* const ptr) { ptr->FUNC; });  \

}