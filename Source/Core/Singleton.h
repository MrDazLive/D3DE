#pragma once


namespace Core {

  /// <summary>
  /// Base class used for creating a singleton object.
  /// </summary>
  template <typename T>
  class Singleton {
  public:
    /// <summary>
    /// <i>Static function.</i><br/>
    /// Creates and returns the only permitted instance of the object.
    /// </summary>
    /// <param name = "args">The arguments to be provided to the constructor of the object.</param>
    template <typename ... V>
    static T* const   Instance    (V...);
  protected:
                      /// <summary>
                      /// Default constructor.
                      /// </summary>
                      Singleton   () = default;

                      /// <summary>
                      /// Default virtual destructor.
                      /// </summary>
    virtual           ~Singleton  () = default;
  private:
    static T*         m_instance;
  };

  template <typename T>
  T* Singleton<T>::m_instance = nullptr;

  template <typename T> template <typename ... V>
  T* const Singleton<T>::Instance(V... args) {
    return m_instance ? m_instance : (m_instance = new T(args...));
  }
}