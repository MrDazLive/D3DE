#include <IRender/IRender.h>
#include <Platform/Platform.h>
#include <Core/Log.h>
#include <Core/Command.h>
#include <Types/Vector3.h>
#include <Types/Matrix4.h>

#ifdef _WIN32
#define APIENTRY __stdcall
#endif
#include <glad/glad.h>

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
    if (k == System::KeyCode::Q) {
      wireframe = !wireframe;
      glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
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

  if (!IRender::Initialise() || !gladLoadGL())
    exit(-1);

  const char* ShaderVersion = "#version 130 \n";
	const char* VertexSource[] = {
    ShaderVersion,
    "in vec3 in_pos;\n"
    "out vec3 vt_pos;\n"
    "out float vt_z;\n"
    "uniform mat4 M;\n"
    "uniform mat4 VP;\n"
    "void main() {\n"
      "mat4 MVP = VP * M;\n"
      "vt_pos = in_pos;\n"
      "vt_z = (M * vec4(in_pos, 1.0)).z;\n"
      "gl_Position = MVP * vec4(in_pos, 1.0);\n"
    "}"
  };
	int VertexShaderID = IRender::CreateVertexShader(VertexSource, 2);

  char const* FragmentSource[] = {
    ShaderVersion,
    "in vec3 vt_pos;\n"
    "in float vt_z;\n"
    "out vec4 color;\n"
    "uniform mat4 M;\n"

    // 2D Random
    "float random(in vec2 st) {"
    "return fract(sin(dot(st.xy,"
      "vec2(12.9898,78.233)))"
      "* 43745.5453123);"
    "}"

    // 2D Noise based on Morgan McGuire @morgan3d
    // https://www.shadertoy.com/view/4dS3Wd
    "float noise(in vec2 st) {"
      "vec2 i = floor(st);"
      "vec2 f = fract(st);"

      // Four corners in 2D of a tile
      "float a = random(i);"
      "float b = random(i + vec2(1.0, 0.0));"
      "float c = random(i + vec2(0.0, 1.0));"
      "float d = random(i + vec2(1.0, 1.0));"

      // Smooth Interpolation

      // Cubic Hermine Curve.  Same as SmoothStep()
      "vec2 u = f*f*(3.0 - 2.0*f);"
      //"u = smoothstep(0.,1.,f);"

      // Mix 4 coorners porcentages
      "return mix(a, b, u.x) +"
        "(c - a)* u.y * (1.0 - u.x) +"
        "(d - b) * u.x * u.y;"
    "}"

    "void main() {\n"
      "vec2 pos = vec2(vt_pos.x * vt_pos.y, vt_pos.z * vt_pos.y);\n"
      "pos = pos / 2.0f + 0.5f;\n"
      "color = M[3] * noise(pos * 16);\n"
      //"color = vec4(vt_pos / 2.0f + 0.5f, 1.0f);\n"
      //"color *= vec4(vec3(vt_z / 2.0f + 0.5f), 1.0f);\n"
    "}"
  };
	int FragmentShaderID = IRender::CreateFragmentShader(FragmentSource, 2);

  int shaders[] = { VertexShaderID, FragmentShaderID };
  int ProgramID = IRender::CreateShaderProgram(shaders, 2);

  int VAO = IRender::CreateVertexArray();
  int VBO = IRender::CreateArrayBuffer();
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
  IRender::SetActiveShaderProgram(ProgramID);

  IRender::SetClearColour(0.2f, 0.2f, 0.4f, 1.0f);
  IRender::EnableDepthTest();
  IRender::EnableCullFace();

  float time = 0.0f;
  Matrix4f V(1.0f);
  V[3][2] = -2.0f;
  
  Platform::Event::Check();
  while(Platform::ValidateWindow(display)) {
    float secs = (float)(((double)clock())/CLOCKS_PER_SEC);
    float delta = secs - time;
    if(move) {
      Matrix4f T;
      T[3][2] = delta * move;
      V = Matrix4f(T * V);
      dirty = true;
    }
    if (rot) {
      V = yRotation(rot * delta) * V;
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

      GLuint uID = glGetUniformLocation(ProgramID, "VP");
      glUniformMatrix4fv(uID, 1, GL_FALSE, V.inversed() * P);
      
      IRender::SetViewport(0, 0, viewport.x, viewport.y);
      dirty = false;
    }

    IRender::ClearBuffer(IRender::BufferBit::COLOUR | IRender::BufferBit::DEPTH);

    LOG->PrintMessage(String("FPS: %.2f", 1.0f / delta));
    time = secs;
    Matrix4f M = yRotation(secs) * xRotation(toRad(330.f)) * Matrix4f(2.0f);
    GLuint uID = glGetUniformLocation(ProgramID, "M");

    M[3][0] = 1.0f;
    M[3][1] = 0.0f;
    M[3][2] = 0.0f;
    glUniformMatrix4fv(uID, 1, GL_FALSE, M);
    IRender::DrawElements(IRender::DrawMode::TRIANGLES, elements.size() * 3, 0);

    M[3][0] = 0.0f;
    M[3][1] = 1.0f;
    M[3][2] = 0.0f;
    glUniformMatrix4fv(uID, 1, GL_FALSE, M);
    IRender::DrawElements(IRender::DrawMode::TRIANGLES, elements.size() * 3, 0);

    M[3][0] = 0.0f;
    M[3][1] = 0.0f;
    M[3][2] = 1.0f;
    glUniformMatrix4fv(uID, 1, GL_FALSE, M);
    IRender::DrawElements(IRender::DrawMode::TRIANGLES, elements.size() * 3, 0);

    IRender::SwapBuffer(display, Platform::WindowContext(display));

    LOG->PrintMessage("Display updated.");
    dirty = false;

    Platform::Event::Check();
  }
  return 0;
}