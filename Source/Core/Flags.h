#pragma once

#include <cstdint>

namespace Core {

  /// <summary>
  /// Class used for holding and maintaining flags.
  /// Can be used as a base class or an object.
  /// </summary>
  template <typename T>
  class Flags {
  public:
    /// <summary>
    /// Enumerator used to identify desired flags. Should be expanded upon by derived class.
    /// </summary>
    enum        Flag          { NONE = T(0), ALL = ~T(0) };

                /// <summary>
                /// Default constructor.
                /// </summary>
                Flags         () = default;

                /// <summary>
                /// Default virtual destructor.
                /// </summary>
    virtual     ~Flags        () = default;

    /// <summary>
    /// Gets the current state of the flags.
    /// </summary>
    const T&    GetFlags      () const;

    /// <summary>
    /// Sets the current state of the flags.
    /// </summary>
    void        SetFlags      (const T& = Flag::NONE);

    /// <summary>
    /// Clears all flags.
    /// </summary>
    void        ClearFlags    ();

    /// <summary>
    /// Raises the desired flags.
    /// </summary>
    /// <param name = "flags">The flags to be raised.</param>
    void        RaiseFlags    (const T& = Flag::ALL);

    /// <summary>
    /// Lowers the desired flags.
    /// </summary>
    /// <param name = "flags">The flags to be lowered.</param>
    void        LowerFlags    (const T& = Flag::ALL);

    /// <summary>
    /// Toggles the desired flags.
    /// </summary>
    /// <param name = "flags">The flags to be raised.</param>
    void        ToggleFlags   (const T& = Flag::ALL);

    /// <summary>
    /// Compares the status of the desired flags.
    /// </summary>
    /// <param name = "flags">The flags to be checked.</param>
    /// <param name = "strict">Defines whether the checked flags all need to be raised.</param>
    /// <returns>Returns whether the checked flags are risen or not.</returns>
    const bool  CheckFlags    (const T&, bool = false) const;
  protected:
  private:
    T           m_flags       { 0 };
  };

  template <typename T>
  const T& Flags<T>::GetFlags() const {
    return m_flags; 
  }

  template <typename T>
  void Flags<T>::SetFlags(const T& flags) {
    m_flags = flags;
  }

  template <typename T>
  void Flags<T>::ClearFlags() {
    m_flags = Flag::NONE;
  }

  template <typename T>
  void Flags<T>::RaiseFlags(const T& flags) {
    m_flags |= flags;
  }

  template <typename T>
  void Flags<T>::LowerFlags(const T& flags) {
    m_flags &= ~flags;
  }

  template <typename T>
  void Flags<T>::ToggleFlags(const T& flags) {
    m_flags ^= flags;
  }

  template <typename T>
  const bool Flags<T>::CheckFlags(const T& flags, bool strict) const {
    return strict ?
      m_flags == (m_flags | flags):   // Alternate solution: !(~m_flags & flags)
      (m_flags & flags) != 0;
  }

#define _FLAGS(SIZE)                        \
  typedef uint ##SIZE##_t     Flag##SIZE;   \
  typedef Flags<Flag##SIZE>   Flags##SIZE;  \

  _FLAGS(8);
  _FLAGS(16);
  _FLAGS(32);
  _FLAGS(64);

#define FLAG(V) 1 << V

}