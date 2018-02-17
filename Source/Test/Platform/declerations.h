#pragma once

#include <Core/UnitTest.h>

#include <Platform/Platform.h>

namespace Platform_Test {

  UNIT_TEST(Window  , "Window Methods"  );
  UNIT_TEST(Input   , "Input Methods"   );

  int DemoMode();
  
  void Flush();

}