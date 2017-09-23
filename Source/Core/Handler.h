#pragma once

#include <vector>
#include <functional>

#include "Log.h"

namespace Core {

  /// <summary>
  /// Base class used for handling objects of the derived type across the application.
  /// </summary>
  template <typename T>
  class Handler {
  public:
                              /// <summary>
                              /// Default constructor. Creates an unhandled instance of the object.
                              /// </summary>
                              Handler         () = default;

                              /// <summary>
                              /// Default virtual destructor.
                              /// </summary>
    virtual                   ~Handler        () = default;

    /// <summary>
    /// Gets the index of the handled object.
    /// </summary>
    const size_t              getIndex        () const;


    /// <summary>
    /// <i>Static function.</i><br/>
    /// Creates and returns a handled instance of the object.
    /// </summary>
    /// <param name = "args">The arguments used in order to enact the desired constructor.</param>
    template <typename ... V>
    static T* const           Create          (V...);

    /// <summary>
    /// <i>Static function.</i><br/>
    /// Deletes the desired handled object. Adjusting other objects accordingly.
    /// </summary>
    /// <param name = "index">The index to the object to be destroyed.</param>
    static void               Destroy         (const size_t);

    /// <summary>
    /// <i>Static function.</i><br/>
    /// Deletes the desired handled object. Adjusting other objects accordingly.
    /// </summary>
    /// <param name = "instance">The pointer to the object to be destroyed.</param>
    static void               Destroy         (T* const);

    /// <summary>
    /// <i>Static function.</i><br/>
    /// Deletes all instances of handled objects.
    /// </summary>
    static void               DestroyAll      ();

    /// <summary>
    /// <i>Static function.</i><br/>
    /// Obtains the total amount of instance being handled.
    /// </summary>
    static size_t             getCount        ();


    /// <summary>
    /// <i>Static function.</i><br/>
    /// Obtains the vector of all objects being handled.
    /// </summary>
    static std::vector<T*>&   getAll();

    /// <summary>
    /// <i>Static function.</i><br/>
    /// Obtains the desireed object.
    /// </summary>
    /// <param name = "index">The index to the object to be collected.</param>
    /// <returns>The pointer to the desired object. Returns <b>nullptr</b> if index is out of bounds.</returns>
    static T* const           getWithIndex    (const unsigned int);

    /// <summary>
    /// <i>Static function.</i><br/>
    /// Obtains an object that meets the specified criteria.
    /// </summary>
    /// <param name = "condition">The conditional method used to locate a suitable object; returning <b>true</b> is suitable.</param>
    /// <returns>The pointer to the desired object. Returns <b>nullptr</b> if no suitable object is found.</returns>
    static T* const           getWhere        (std::function<bool(T* const)>);

    /// <summary>
    /// <i>Static function.</i><br/>
    /// Iterates through each handled object, modifying it as deisred.
    /// </summary>
    /// <param name = "modifier">The alteration method used to modify the objects.</param>
    static void               forEach         (std::function<void(T* const)>);

  protected:
  private:
    size_t                    m_index         { 0 };
    static std::vector<T*>    m_instances;
  };

  template <typename T>
  std::vector<T*> Handler<T>::m_instances;

  template <typename T>
  const size_t Handler<T>::getIndex() const {
    return m_index;
  }

  template <typename T> template <typename ... V>
  T* const Handler<T>::Create(V... args) {
    T* obj = new T(args...);
    Handler<T>* handle = dynamic_cast<Handler<T>*>(obj);

    LOG->PrintAssert(handle != nullptr, "Provided type has not been flagged for handling.");

    handle->m_index = m_instances.size();
    m_instances.push_back(obj);

    return obj;
  }

  template <typename T>
  void Handler<T>::Destroy(const size_t index) {
    delete m_instances[index];
    m_instances.erase(m_instances.begin() + index);

    const size_t count = m_instances.size();
    for (size_t ind = index; ind < count; ++ind) {
      --(m_instances[ind]->m_index);
    }
  }

  template <typename T>
  void Handler<T>::Destroy(T* const instance) {
    Destroy(instance->getIndex());
  }

  template <typename T>
  void Handler<T>::DestroyAll() {
    forEach([](T* const ptr) { delete ptr; });
    m_instances.clear();
  }

  template <typename T>
  size_t Handler<T>::getCount() {
    return m_instances.size();
  }

  template <typename T>
  std::vector<T*>& Handler<T>::getAll() {
    return m_instances;
  }

  template <typename T>
  T* const Handler<T>::getWithIndex(const unsigned int index) {
    return index < m_instances.size() ? m_instances[index] : nullptr;
  }

  template <typename T>
  T* const Handler<T>::getWhere(std::function<bool(T* const)> condition) {
    for (T* obj : m_instances) {
      if (condition(obj))
        return obj;
    }
    return nullptr;
  }

  template <typename T>
  void Handler<T>::forEach(std::function<void(T* const)> modifier) {
    for (T* obj : m_instances) {
      modifier(obj);
    }
  }

}