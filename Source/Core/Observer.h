#pragma once

#include <set>
#include <vector>
#include <functional>

namespace Core {
  
  /// <summary>
  /// Base class used for establishing observable objects.
  /// </summary>
  template <typename T>
  class Observable {
  public:
    class Observer;
    class ObserverDestructor {
    public:
                                        /// <summary>
                                        /// Virtual constructor.
                                        /// Removes Observer from observer lists.
                                        /// </summary>
                                        ~ObserverDestructor();
    };
  private:
    using ObserverMethod                = std::function<void(Observer* const)>;
    using ObserverList                  = std::set<Observer*>;
    using ObservableList                = std::vector<Observable<T>*>;
  public:
                                        /// <summary>
                                        /// Constructor.
                                        /// </summary>
                                        Observable            ();

                                        /// <summary>
                                        /// Destructor.
                                        /// </summary>
                                        ~Observable           ();

    /// <summary>
    /// Adds an observer to this instance of the observable.
    /// </summary>
    /// <param name = "ptr">A pointer to the observer that wishes to observe.</param>
    void                                AddObserver           (Observer* const);

    /// <summary>
    /// Removes an observer from this instance of the observable.
    /// </summary>
    /// <param name = "ptr">A pointer to the observer that wishes to stop observing.</param>
    void                                RemoveObserver        (Observer* const);

    /// <summary>
    /// Adds an observer that wishes to observe all instances of the observable.
    /// </summary>
    /// <param name = "ptr">A pointer to the observer that wishes to observe.</param>
    static void                         AddGlobalObserver     (Observer* const);

    /// <summary>
    /// Removes an observer that wishes to stop observing all instances of the observable.
    /// </summary>
    /// <param name = "ptr">A pointer to the observer that wishes to stop observing.</param>
    static void                         RemoveGlobalObserver  (Observer* const);

    /// <summary>
    /// Gets the count of the observers that are observing this instance.
    /// </summary>
    const size_t                        ObserverCount         () const;

    /// <summary>
    /// Gets the count of the observers that are observing all instances.
    /// </summary>
    static const size_t                 GlobalObserverCount   ();

    /// <summary>
    /// Gets a the list of all exisitng observables.
    /// </summary>
    static const ObservableList&        GetObservables        ();
  protected:
    /// <summary>
    /// Calls the provided method, passing each observer (from the local and global lists) as a parameter.
    /// </summary>
    /// <param name = "function">The function to called.</param>
    void                                NotifyObservers       (ObserverMethod);

    /// <summary>
    /// Calls the provided method, passing each observer (from the provided list) as a parameter.
    /// </summary>
    /// <param name = "list">The list of observers to be iterated through.</param>
    /// <param name = "function">The function to called.</param>
    void                                NotifyObservers       (const ObserverList&, ObserverMethod&);
  private:
           ObserverList                 m_observers           {};
    static ObserverList                 s_globalObservers;
    static ObservableList               s_observables;
  };

  #define OBSERVER_CLASS(T) template<> class Core::Observable<T>::Observer : public Core::Observable<T>::ObserverDestructor

  template <typename T>
  std::vector<Observable<T>*> Observable<T>::s_observables = {};

  template <typename T>
  Observable<T>::ObserverDestructor::~ObserverDestructor() {
    Observer* const this_ = static_cast<Observer*>(this);
    Observable<T>::RemoveGlobalObserver(this_);
    for (auto obs : Observable<T>::GetObservables()) {
      obs->RemoveObserver(this_);
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
  void Observable<T>::AddGlobalObserver(Observer* const ptr) {
    s_globalObservers.emplace(ptr);
  }

  template <typename T>
  void Observable<T>::RemoveGlobalObserver(Observer* const ptr) {
    s_globalObservers.erase(ptr);
  }

  template <typename T>
  const size_t Observable<T>::ObserverCount() const {
    return m_observers.size();
  }

  template <typename T>
  const size_t Observable<T>::GlobalObserverCount() {
    return s_globalObservers.size();
  }

  template <typename T>
  const std::vector<Observable<T>*>& Observable<T>::GetObservables() {
    return s_observables;
  }

  template <typename T>
  void Observable<T>::NotifyObservers(std::function<void(Observer* const)> function) {
    NotifyObservers(m_observers, function);
    NotifyObservers(s_globalObservers, function);
  }

  template <typename T>
  void Observable<T>::NotifyObservers(const ObserverList& list, std::function<void(Observer* const)>& function) {
    for (Observer* const ptr : list) {
      function(ptr);
    }
  }

#define NOTIFY_OBSERVERS(FUNC)                          \
  NotifyObservers([&](auto* const ptr) { ptr->FUNC; }); \

}