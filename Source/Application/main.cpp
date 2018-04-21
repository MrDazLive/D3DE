#include <IRender/IRender.h>
#include <Platform/Platform.h>
#include <Core/Log.h>
#include <Core/Command.h>
#include <Types/Vector3.h>
#include <Types/Matrix.h>

#ifdef _WIN32
#define APIENTRY __stdcall
#endif
#include <glad/glad.h>

using namespace DTU;
#include <ctime>
#include <math.h>
#include <vector>
#define toRad(Deg) Deg * PI / 180.f

int dir = 0;
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
      const float HALF_PI = PI / 2.0f;
      float a = 0.5f * cos((x * i * PI) + HALF_PI) * cos(y * j * PI * 2);
      float b = 0.5f * cos((x * i * PI) + HALF_PI) * sin(y * j * PI * 2);
      float c = 0.5f * sin((x * i * PI) + HALF_PI);
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
    if (k == System::KeyCode::W) ++dir;
    if (k == System::KeyCode::S) --dir;
    if (k == System::KeyCode::Q) {
      wireframe = !wireframe;
      glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
    }
  }

  void  KeyboardReleased  (const System::KeyCode k, const unsigned int) override {
    if (k == System::KeyCode::W) --dir;
    if (k == System::KeyCode::S) ++dir;
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
    "uniform mat4 V;\n"
    "uniform mat4 P;\n"
    "void main() {\n"
      "float PI = 3.14159265359f;\n"
      "float S = 1/tan((45.0f * PI)/360.0f);\n"
      "mat4 MVP = P * V * M;\n"
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
    "void main() {\n"
      "color = vec4(vt_pos / 2.0f + 0.5f, 1.0f);\n"
      //"color = vec4(vec3(vt_z / 2.0f + 0.5f), 1.0f);\n"
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
  IRender::AddVertexAttribute<float>(0, 3, 0, 0);
  IRender::SetActiveShaderProgram(ProgramID);

  IRender::SetClearColour(0.2f, 0.2f, 0.4f, 1.0f);
  IRender::EnableDepthTest();
  IRender::EnableCullFace();

  double time = 0.0;
  float z_offset = 0.0f;

  while(Platform::ValidateWindow(display)) {
    if (dirty) {
      {
        Matrix4f V(1.0f);
        V[3][2] = 2.0f;

        GLuint uID = glGetUniformLocation(ProgramID, "V");
        glUniformMatrix4fv(uID, 1, GL_FALSE, V);
      }
      {
        float S = 1.0f / tan(toRad(25.f));
        float F = 1000.0f, N = 0.01f, R = viewport.x / viewport.y;
        Matrix4f P(0.0f);
        P[0][0] = S / R;
        P[1][1] = S;
        P[2][2] = -(F + N) / (N - F);
        P[2][3] = 1.0f;
        P[3][2] = (F * N) / (N - F);

        GLuint uID = glGetUniformLocation(ProgramID, "P");
        glUniformMatrix4fv(uID, 1, GL_FALSE, P);
      }
      
      glViewport(0, 0, viewport.x, viewport.y);
      dirty = false;
    }

    IRender::ClearBuffer(IRender::BufferBit::COLOUR | IRender::BufferBit::DEPTH);

    double secs = (((double)clock())/CLOCKS_PER_SEC);
    double delta = secs - time;
    z_offset += delta * dir;

    LOG->PrintMessage(String("FPS: %.2f", 1.0f / delta));
    time = secs;
    Matrix4f M = yRotation(secs) * xRotation(toRad(330.f));
    GLuint uID = glGetUniformLocation(ProgramID, "M");

    glUniformMatrix4fv(uID, 1, GL_FALSE, M);
    glDrawElements(GL_TRIANGLES, elements.size() * 3, GL_UNSIGNED_INT, (void*)0);

    M[3][0] = 1.0f;
    M[3][1] = 1.0f;
    M[3][2] = z_offset;
    glUniformMatrix4fv(uID, 1, GL_FALSE, M);
    glDrawElements(GL_TRIANGLES, elements.size() * 3, GL_UNSIGNED_INT, (void*)0);

    IRender::SwapBuffer(display, Platform::WindowContext(display));

    LOG->PrintMessage("Display updated.");
    dirty = false;

    Platform::Event::Check();
  }
  return 0;
}