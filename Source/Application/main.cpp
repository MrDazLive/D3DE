#include <IRender/IRender.h>
#include <Platform/Platform.h>
#include <Core/Log.h>
#include <Core/File.h>
#include <Core/Command.h>
#include <Types/Vector3.h>
#include <Types/Matrix4.h>

using namespace DTU;
#include <ctime>
#include <math.h>
#include <vector>
#define toRad(Deg) Deg * (float)PI / 180.f

int move = 0;
int rot = 0;
bool wireframe = false;
bool dirty = true;
Vector2u viewport;

int ProgramID;

void ReloadShaders() {
  auto LoadShader = [](const int idx, const char* doc, void(*cmp)(const int, const char**, const size_t)) {
    static const char* ShaderVersion = "#version 130 \n";

    Core::File file(doc);
    DTU::String source;
    file.getContent(source, true);

    const char* array[] = { ShaderVersion, source} ;
    cmp(idx, array, 2);
  };
  int Shaders[] = { IRender::CreateVertexShader(), IRender::CreateFragmentShader() };
  LoadShader(Shaders[0], "vs.glsl", &IRender::CompileVertexShader);
  LoadShader(Shaders[1], "fs.glsl", &IRender::CompileVertexShader);

  IRender::DeleteShaderProgram(ProgramID);
  ProgramID = IRender::CreateShaderProgram(Shaders, 2);
  IRender::DeleteVertexShader(Shaders[0]);
  IRender::DeleteFragmentShader(Shaders[1]);
  IRender::SetActiveShaderProgram(ProgramID);
  dirty = true;
}

Matrix4f xRotation(float rads) {
  Matrix4f r(1.0f);
  r[1][1] = r[2][2] = cos(rads);
  r[1][2] = sin(rads);
  r[2][1] = -r[1][2];
  return r;
}

Matrix4f yRotation(float rads) {
  Matrix4f r(1.0f);
  r[0][0] = r[2][2] = cos(rads);
  r[2][0] = sin(rads);
  r[0][2] = -r[2][0];
  return r;
}

Matrix4f zRotation(float rads) {
  Matrix4f r(1.0f);
  r[0][0] = r[1][1] = cos(rads);
  r[0][1] = sin(rads);
  r[1][0] = - r[0][1];
  return r;
}

void cubeMesh(std::vector<Vector3f>& verts, std::vector<Vector3i>& elements) {
  verts.push_back({ -0.5f, -0.5f, -0.5f });
  verts.push_back({ -0.5f, -0.5f,  0.5f });
  verts.push_back({ -0.5f,  0.5f, -0.5f });
  verts.push_back({ -0.5f,  0.5f,  0.5f });
  verts.push_back({  0.5f, -0.5f, -0.5f });
  verts.push_back({  0.5f, -0.5f,  0.5f });
  verts.push_back({  0.5f,  0.5f, -0.5f });
  verts.push_back({  0.5f,  0.5f,  0.5f });

  elements.push_back({ 1, 0, 2 });
  elements.push_back({ 1, 2, 3 });

  elements.push_back({ 4, 5, 6 });
  elements.push_back({ 6, 5, 7 });

  elements.push_back({ 2, 0, 4 });
  elements.push_back({ 2, 4, 6 });

  elements.push_back({ 1, 3, 5 });
  elements.push_back({ 5, 3, 7 });

  elements.push_back({ 0, 1, 4 });
  elements.push_back({ 4, 1, 5 });

  elements.push_back({ 3, 2, 6 });
  elements.push_back({ 3, 6, 7 });
}

void sphereMesh(std::vector<Vector3f>& verts, std::vector<Vector3i>& element) {
  int w = 100, h = 100;
  float x = 1.0f / (float)w, y = 1.0f / (float)h;
  for (int j = 0; j <= h; ++j) {
    for (int i = 0; i <= w; ++i) {
      const float HALF_PI = (float)PI / 2.0f;
      float u = (x * (float)i * (float)PI) + HALF_PI;
      float v = y * (float)j * (float)PI * 2.0f;
      float a = 0.5f * cos(u) * cos(v);
      float b = 0.5f * cos(u) * sin(v);
      float c = 0.5f * sin(u);
      verts.push_back({ a, b, c });
    }
  }
  for (int j = 0; j < h; ++j) {
    for (int i = 0; i < w; ++i) {
      int a = (j * (w + 1)) + i;
      int b = a + 1;
      int c = a + h + 1;
      int d = c + 1;
      element.push_back({ b, a, c });
      element.push_back({ b, c, d });
    }
  }
}

class PEL : public Platform::Event::Listener {
  void  WindowClosed      (const int i) override {
    Platform::CloseWindow(i);
  }

  void  WindowResized     (const int i, const int x, const int y, const unsigned int w, const unsigned int h) override {
    viewport = Vector2u(w, h);
    dirty = true;
  }

  void  KeyboardPressed   (const System::KeyCode k, const unsigned int) override {
    if (k == System::KeyCode::W) ++move;
    if (k == System::KeyCode::S) --move;
    if (k == System::KeyCode::A) --rot;
    if (k == System::KeyCode::D) ++rot;
    if (k == System::KeyCode::E) ReloadShaders();
    if (k == System::KeyCode::Q) {
      wireframe = !wireframe;
      //glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
    }
  }

  void  KeyboardReleased  (const System::KeyCode k, const unsigned int) override {
    if (k == System::KeyCode::W) --move;
    if (k == System::KeyCode::S) ++move;
    if (k == System::KeyCode::A) ++rot;
    if (k == System::KeyCode::D) --rot;
  }
};

int main(int argc, char **args) {
  Core::Command::Collect(argc, args);

  PEL pel;
  int display;
  Platform::CreateWindow(&display, 120, 120, 720, 540, "Application");
  IRender::CreateContext(display, Platform::WindowContext(display));

  if (!IRender::Initialise())
    exit(-1);

  int VAO = IRender::CreateVertexArray();
  int VBO = IRender::CreateArrayBuffer();
  int VIA = IRender::CreateArrayBuffer();
  int VEA = IRender::CreateElementBuffer();

  std::vector<Vector3f> verts;
  std::vector<Vector3i> elements;
  //cubeMesh(verts, elements);
  sphereMesh(verts, elements);

  IRender::SetActiveVertexArray(VAO);
  IRender::SetActiveElementBuffer(VEA);
  IRender::SetElementBufferData(elements.data(), sizeof(Vector3i) * elements.size());
  IRender::SetActiveArrayBuffer(VBO);
  IRender::SetArrayBufferData(verts.data(), sizeof(Vector3f) * verts.size());
  IRender::AddVertexAttribute<float>(0, 3, sizeof(Vector3f), 0);
  /*IRender::SetActiveArrayBuffer(VIA);
  IRender::AddVertexAttribute<float>(1, 4, sizeof(Matrix4f), 0);
  IRender::AddVertexAttribute<float>(2, 4, sizeof(Matrix4f), sizeof(Matrix<float,1,4>));
  IRender::AddVertexAttribute<float>(3, 4, sizeof(Matrix4f), sizeof(Matrix<float,2,4>));
  IRender::AddVertexAttribute<float>(4, 4, sizeof(Matrix4f), sizeof(Matrix<float,3,4>));
  IRender::SetInstancedAttribute(1);
  IRender::SetInstancedAttribute(2);
  IRender::SetInstancedAttribute(3);
  IRender::SetInstancedAttribute(4);*/

  IRender::SetClearColour(0.2f, 0.2f, 0.4f, 1.0f);
  IRender::EnableDepthTest();
  IRender::EnableCullFace();

  float time = 0.0f;
  Matrix4f V(1.0f);
  V[3][2] = -2.0f;

  ReloadShaders();
  
  Platform::Event::Check();
  while(Platform::ValidateWindow(display)) {
    float secs = (float)(((double)clock())/CLOCKS_PER_SEC);
    float delta = secs - time;
    if (move || rot) {
      Matrix4f T;
      if (rot)  T = yRotation(rot * delta);
      if (move) T[3][2] += delta * move;
      V = T * V;
      dirty = true;
    }

    if (dirty) {
      float S = 1.0f / tan(toRad(25.f));
      float F = 1000.0f, N = 0.01f, R = (float)viewport.x / (float)viewport.y;
      Matrix4f P(0.0f);
      P[0][0] = S / R;
      P[1][1] = S;
      P[2][2] = -(F + N) / (N - F);
      P[2][3] = 1.0f;
      P[3][2] = (F * N) / (N - F);

      int uID = IRender::GetUniformIndex(ProgramID, "VP");
      IRender::SetUniformValue<float, 4, 4>(uID, V.inversed() * P);
      
      IRender::SetViewport(0, 0, viewport.x, viewport.y);
      dirty = false;
    }

    IRender::ClearBuffer(IRender::BufferBit::COLOUR | IRender::BufferBit::DEPTH);

    LOG->PrintMessage(String("FPS: %.2f", 1.0f / delta));
    time = secs;
    Matrix4f M = yRotation(secs) * xRotation(toRad(330.f)) * Matrix4f(2.0f);
    int uID = IRender::GetUniformIndex(ProgramID, "M");

    Matrix4f xform[3] = { M, M, M };
    xform[0][3][0] = 1.0f;
    xform[1][3][1] = 1.0f;
    xform[2][3][2] = 1.0f;
    //IRender::SetActiveArrayBuffer(VIA);
    //IRender::SetArrayBufferData(xform, sizeof(xform));
    //IRender::DrawElementsInstanced(IRender::DrawMode::TRIANGLES, elements.size() * 3, 0, 3);
    
    IRender::SetUniformValue<float, 4, 4>(uID, xform[0]);
    IRender::DrawElements(IRender::DrawMode::TRIANGLES, elements.size() * 3, 0);
    
    IRender::SetUniformValue<float, 4, 4>(uID, xform[1]);
    IRender::DrawElements(IRender::DrawMode::TRIANGLES, elements.size() * 3, 0);
    
    IRender::SetUniformValue<float, 4, 4>(uID, xform[2]);
    IRender::DrawElements(IRender::DrawMode::TRIANGLES, elements.size() * 3, 0);

    IRender::SwapBuffer(display, Platform::WindowContext(display));

    LOG->PrintMessage("Display updated.");
    dirty = false;

    Platform::Event::Check();
  }
  return 0;
}