#include <IRender/IRender.h>
#include <Platform/Platform.h>
#include <Core/Log.h>
#include <Core/Command.h>

#include <GL/gl.h>
#include <GL/glu.h>

bool dirty = true;

class PEL : public Platform::Event::Listener {
  void  WindowClosed      (const int i) override {
    Platform::CloseWindow(i);
  }

  void  WindowResized     (const int i, const int x, const int y, const unsigned int w, const unsigned int h) override {
    glViewport(0, 0, w, h);
    dirty = true;
  }
};

int main(int argc, char **args) {
  Core::Command::Collect(argc, args);
  
  PEL pel;
  int display;
  Platform::CreateWindow(&display, 0, 0, 480, 360, "Application");
  IRender::CreateContext(display, Platform::WindowContext(display));


  while(Platform::ValidateWindow(display)) {
    Platform::Event::Check();

    if(dirty) {
      glEnable(GL_DEPTH_TEST); 

      glClearColor(1.0, 1.0, 1.0, 1.0);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glOrtho(-1., 1., -1., 1., 1., 20.);

      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      gluLookAt(0., 0., 10., 0., 0., 0., 0., 1., 0.);

      glBegin(GL_QUADS);
        glColor3f(1., 0., 0.); glVertex3f(-.75, -.75, 0.);
        glColor3f(0., 1., 0.); glVertex3f( .75, -.75, 0.);
        glColor3f(0., 0., 1.); glVertex3f( .75,  .75, 0.);
        glColor3f(1., 1., 0.); glVertex3f(-.75,  .75, 0.);
      glEnd();

      IRender::SwapBuffer(display, Platform::WindowContext(display));

      LOG->PrintMessage("Display updated.");
      dirty = false;
    }
  }
  return 0;
}