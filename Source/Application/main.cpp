#include <IRender/IRender.h>
#include <Platform/Platform.h>
#include <Core/Log.h>
#include <Core/Command.h>
#include <Types/Matrix.h>

#ifdef _WIN32
#define APIENTRY __stdcall
#endif
#include <glad/glad.h>

using namespace DTU;
#include <ctime>
#include <math.h>
#define toRad(Deg) Deg * PI / 180.f

bool dirty = true;

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

  int display;
  Platform::CreateWindow(&display, 0, 0, 480, 360, "Application");
  IRender::CreateContext(display, Platform::WindowContext(display));

  if (!IRender::Initialise() || !gladLoadGL())
    exit(-1);

  PEL pel;

  const char* ShaderVersion = "#version 130 \n";
	const char* VertexSource[] = {
    ShaderVersion,
    "in vec3 in_pos;\n"
    "out vec3 vt_pos;\n"
    "out float vt_z;\n"
    "uniform mat4 M;\n"
    "uniform mat4 VP;\n"
    "void main() {\n"
      "float PI = 3.14159265359f;\n"
      "float S = 1/tan((45.0f * PI)/360.0f);\n"
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
    "void main() {\n"
      "color = vec4(vec3(vt_z / 2.0f + 0.05f), 1.0f);\n"
    "}"
  };
	int FragmentShaderID = IRender::CreateFragmentShader(FragmentSource, 2);

  int shaders[] = { VertexShaderID, FragmentShaderID };
  int ProgramID = IRender::CreateShaderProgram(shaders, 2);

  int VAO = IRender::CreateVertexArray();
  int VBO = IRender::CreateArrayBuffer();
  int VEA = IRender::CreateElementBuffer();

  static const GLfloat verts[] = {
    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f
  };

  static const GLint elements[] = {
    1, 0, 2,
    1, 2, 3,

    4, 5, 6,
    6, 5, 7,

    2, 0, 4,
    2, 4, 6,

    1, 3, 5,
    5, 3, 7,

    0, 1, 4,
    4, 1, 5,

    3, 2, 6,
    3, 6, 7
  };

  IRender::SetActiveVertexArray(VAO);
  IRender::SetActiveElementBuffer(VEA);
  IRender::SetElementBufferData(elements, sizeof(elements));
  IRender::SetActiveArrayBuffer(VBO);
  IRender::SetArrayBufferData(verts, sizeof(verts));
  IRender::AddVertexAttribute<float>(0, 3, 0, 0);
  IRender::SetActiveShaderProgram(ProgramID);
  
  {
    Matrix4f V(1.0f);
    V[3][2] = -5.0f;
    /*GLuint uID = glGetUniformLocation(ProgramID, "V");
    glUniformMatrix4fv(uID, 1, GL_FALSE, V);*/
    
    float S = 1.0f/tan(toRad(25.f));
    float F = 1000.0f, N = 0.01f, R = 480.f / 360.f;
    Matrix4f P(0.0f);
    P[0][0] = S;
    P[1][1] = S;
    P[2][2] = (F + N) / (N - F);
    P[2][3] = -1.0f;
    P[3][2] = (F * N) / (N - F);

    GLuint uID = glGetUniformLocation(ProgramID, "VP");
    glUniformMatrix4fv(uID, 1, GL_FALSE, V * P);
  }

  while(Platform::ValidateWindow(display)) {
    if(true || dirty) {
      IRender::EnableDepthTest();
      
      glDepthMask(GL_TRUE);
      glDepthFunc(GL_LESS);
      glEnable(GL_CULL_FACE);
      glCullFace(GL_FRONT);

      IRender::SetClearColour(0.2f, 0.2f, 0.4f, 1.0f);
      IRender::ClearBuffer(IRender::BufferBit::COLOUR | IRender::BufferBit::DEPTH);

      float secs = (((float)clock())/CLOCKS_PER_SEC * 60);
      Matrix4f T = yRotation(secs) * xRotation(toRad(30.0f));
      GLuint uID = glGetUniformLocation(ProgramID, "M");
      
      glUniformMatrix4fv(uID, 1, GL_FALSE, T);
      glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);

      T[3][0] = 1.0f;
      T[3][1] = 1.0f;
      T[3][2] = 1.0f;
      glUniformMatrix4fv(uID, 1, GL_FALSE, T);
      glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);

      IRender::SwapBuffer(display, Platform::WindowContext(display));

      LOG->PrintMessage("Display updated.");
      dirty = false;
    }

    Platform::Event::Check();
  }
  return 0;
}