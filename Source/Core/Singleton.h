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

    /// <summar>
    /// <i>Static function.</i><br/>
    /// Destroys the current instance of the object.
    /// </summary>
    static void       Destroy     ();
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
    static T*         s_instance;
  };

  template <typename T>
  T* Singleton<T>::s_instance = nullptr;

  template <typename T> template <typename ... V>
  T* const Singleton<T>::Instance(V... args) {
    return s_instance ? s_instance : (s_instance = new T(args...));
  }

  template <typename T> 
  void Singleton<T>::Destroy() {
    delete s_instance;
    s_instance = nullptr;
  }
}