#pragma once

#include <Core/UnitTest.h>

#include <Platform/Platform.h>
#include <unistd.h>

namespace Platform_Test {

  UNIT_TEST(Window  , "Window Methods"  );
  UNIT_TEST(Input   , "Input Methods"   );

  int DemoMode();
  
  static void Flush() {
    usleep(200000);
    Platform::Event::Check();
  }

}