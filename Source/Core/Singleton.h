#pragma once


namespace Core {
  template <typename T>
  class Singleton {
  public:
    template <typename ... V>
    static T* const   Instance    (V...);
  protected:
                      Singleton   () = default;
    virtual           ~Singleton  () = default;
  private:
    static T*         m_instance;
  };

  template <typename T>
  T* Singleton<T>::m_instance = nullptr;

  template <typename T> template <typename ... V>
  T* const Singleton<T>::Instance(V... arg) {
    return m_instance ? m_instance : (m_instance = new T(arg...));
  }
}