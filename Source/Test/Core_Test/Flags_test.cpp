#include "declerations.h"

#include <Core/Flags.h>

class Flags_Dumby : public Core::Flags8 {
public:
  enum Flag {
    A = FLAG(0),
    B = FLAG(1),
    C = FLAG(2)
  };
  Flags_Dumby() {}
} flags;

namespace Core_Test {

  void Flags::Reset() {
    flags.ClearFlags();
  }

  void Flags::Examine() {
    TestCase([]() {
      return flags.NONE == 0 && flags.A == 1 && flags.B == 2 && flags.C == 4;
    }, "Flags::Flag");

    TestCase([]() {
      return flags.GetFlags() == 0;
    }, "Flags::GetFlags");

    TestCase([]() {
      flags.SetFlags(Flags_Dumby::A | Flags_Dumby::C);
      return flags.GetFlags() == 5;
    }, "Flags::SetFlags");

    TestCase([]() {
      flags.SetFlags(Flags_Dumby::A | Flags_Dumby::C);
      flags.ClearFlags();
      return flags.GetFlags() == 0;
    }, "Flags::Clear");

    TestCase([]() {
      flags.SetFlags(Flags_Dumby::A | Flags_Dumby::C);
      flags.RaiseFlags(Flags_Dumby::A | Flags_Dumby::B);
      return flags.GetFlags() == 7;
    }, "Flags::RaiseFlags");

    TestCase([]() {
      flags.SetFlags(Flags_Dumby::A | Flags_Dumby::C);
      flags.LowerFlags(Flags_Dumby::A | Flags_Dumby::B);
      return flags.GetFlags() == 4;
    }, "Flags::LowerFlags");

    TestCase([]() {
      flags.SetFlags(Flags_Dumby::A | Flags_Dumby::C);
      flags.ToggleFlags(Flags_Dumby::A | Flags_Dumby::B);
      return flags.GetFlags() == 6;
    }, "Flags::ToggleFlags");

    TestCase([]() {
      flags.SetFlags(Flags_Dumby::A | Flags_Dumby::C);
      return flags.CheckFlags(Flags_Dumby::A | Flags_Dumby::B) && !flags.CheckFlags(Flags_Dumby::B);
    }, "Flags::CheckFlags(false)");

    TestCase([]() {
      flags.SetFlags(Flags_Dumby::A | Flags_Dumby::C);
      return flags.CheckFlags(Flags_Dumby::A, true) && flags.CheckFlags(Flags_Dumby::A | Flags_Dumby::C, true) && !flags.CheckFlags(Flags_Dumby::A | Flags_Dumby::B, true);
    }, "Flags::CheckFlags(true)");
  }

}