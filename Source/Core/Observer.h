#pragma once

#include <set>
#include <vector>
#include <functional>

namespace Core {

  template <typename T>
  class ObserverBase {
  public:
    virtual                             ~ObserverBase         ();
  };

  template <typename T>
  class Observable {
    typedef std::set<ObserverBase<T>*>  ObserverList;
    typedef std::vector<Observable<T>*> ObservableList;
  public:
                                        Observable            ();
                                        ~Observable           ();

    void                                AddObserver           (ObserverBase<T>* const);
    void                                RemoveObserver        (ObserverBase<T>* const);

    static const ObservableList&        GetObservables        ();

    static void                         AddGlobalObserver     (ObserverBase<T>* const);
    static void                         RemoveGlobalObserver  (ObserverBase<T>* const);
  protected:
    void                                NotifyObservers       (std::function<void(ObserverBase<T>*)>);
  private:
           ObserverList                 m_observers           {};
    static ObserverList                 s_globalObservers;
    static ObservableList               s_observables;
  };

  template <typename T>
  std::set<ObserverBase<T>*>    Observable<T>::s_globalObservers  = {};

  template <typename T>
  std::vector<Observable<T>*>   Observable<T>::s_observables      = {};

  template <typename T>
  ObserverBase<T>::~ObserverBase() {
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
  void Observable<T>::AddObserver(ObserverBase<T>* const ptr) {
    m_observers.emplace(ptr);
  }

  template <typename T>
  void Observable<T>::RemoveObserver(ObserverBase<T>* const ptr) {
    m_observers.erase(ptr);
  }

  template <typename T>
  const std::vector<Observable<T>*>& Observable<T>::GetObservables() {
    return s_observables;
  }

  template <typename T>
  void Observable<T>::AddGlobalObserver(ObserverBase<T>* const ptr) {
    s_globalObservers.emplace(ptr);
  }

  template <typename T>
  void Observable<T>::RemoveGlobalObserver(ObserverBase<T>* const ptr) {
    s_globalObservers.erase(ptr);
  }

  template <typename T>
  void Observable<T>::NotifyObservers(std::function<void(ObserverBase<T>*)> function) {
    for (ObserverBase<T>* const ptr : m_observers) {
      function(ptr);
    }
  }

#define NOTIFY_OBSERVERS(FUNC)                                                    \
  NotifyObservers([&](auto* const ptr) { dynamic_cast<Observer*>(ptr)->FUNC; });  \

}