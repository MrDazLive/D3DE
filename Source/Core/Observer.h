#pragma once

#include <set>
#include <vector>
#include <functional>

namespace Core {
  
  template <typename T>
  class Observable {
  public:
    class Observer {
    public:
      virtual                           ~Observer();
    };
  private:
    using ObserverList                  = std::set<Observer*>;
    using ObservableList                = std::vector<Observable<T>*>;
  public:

                                        Observable            ();
                                        ~Observable           ();

    void                                AddObserver           (Observer* const);
    void                                RemoveObserver        (Observer* const);

    static const ObservableList&        GetObservables        ();

    static void                         AddGlobalObserver     (Observer* const);
    static void                         RemoveGlobalObserver  (Observer* const);
  protected:
    void                                NotifyObservers       (std::function<void(Observer*)>);
  private:
           ObserverList                 m_observers           {};
    static ObserverList                 s_globalObservers;
    static ObservableList               s_observables;
  };

  template <typename T>
  std::vector<Observable<T>*> Observable<T>::s_observables = {};

  template <typename T>
  Observable<T>::Observer::~Observer() {
    Observable<T>::RemoveGlobalObserver(this);
    for (auto obs : Observable<T>::GetObservables()) {
      obs->RemoveObserver(this);
    }
  }

  template <typename T>
  Observable<T>::Observable() {
    s_observables.push_back(this);
  }

  template <typename T>
  Observable<T>::~Observable() {
    for (auto obs = s_observables.begin(); obs != s_observables.end(); ++obs) {
      if ((*obs) == this) {
        s_observables.erase(obs);
        return;
      }
    }
  }

  template <typename T>
  void Observable<T>::AddObserver(Observer* const ptr) {
    m_observers.emplace(ptr);
  }

  template <typename T>
  void Observable<T>::RemoveObserver(Observer* const ptr) {
    m_observers.erase(ptr);
  }

  template <typename T>
  const std::vector<Observable<T>*>& Observable<T>::GetObservables() {
    return s_observables;
  }

  template <typename T>
  void Observable<T>::AddGlobalObserver(Observer* const ptr) {
    s_globalObservers.emplace(ptr);
  }

  template <typename T>
  void Observable<T>::RemoveGlobalObserver(Observer* const ptr) {
    s_globalObservers.erase(ptr);
  }

  template <typename T>
  void Observable<T>::NotifyObservers(std::function<void(Observer*)> function) {
    for (Observer* const ptr : m_observers) {
      function(ptr);
    }
  }

#define NOTIFY_OBSERVERS(FUNC)                          \
  NotifyObservers([&](auto* const ptr) { ptr->FUNC; }); \

}