#include <IRender/IRender.h>
#include <Platform/Platform.h>
#include <Core/Log.h>
#include <Core/Command.h>

#ifdef _WIN32
#define APIENTRY __stdcall
#endif
#include <glad/glad.h>

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

  int display;
  Platform::CreateWindow(&display, 0, 0, 480, 360, "Application");
  IRender::CreateContext(display, Platform::WindowContext(display));

  if (!IRender::Initialise() || !gladLoadGL())
    exit(-1);

  PEL pel;

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	GLint Result = GL_FALSE;

	const GLchar* VertexSourcePointer = 
  "#version 130 \n"
  "in vec3 vertexPosition_modelspace;\n"
  "void main() {\n"
  "  gl_Position.xyz = vertexPosition_modelspace;\n"
  "  gl_Position.w = 1.0;\n"
  "}";
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	char const * FragmentSourcePointer = 
  "#version 130 \n"
  "out vec3 color;\n"
  "void main() {\n"
  "  color = vec3(1,0,0);\n"
  "}";
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);
	
	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);
	
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

GLuint VertexArrayID;
glGenVertexArrays(1, &VertexArrayID);
glBindVertexArray(VertexArrayID);

int VAO = IRender::CreateVertexArray();
IRender::SetActiveVertexArray(VAO);

static const GLfloat verts[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
};

int VBO = IRender::CreateArrayBuffer();
IRender::SetActiveArrayBuffer(VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
IRender::AddVertexAttribute<float>(0, 3, 0, 0);

  while(Platform::ValidateWindow(display)) {
    Platform::Event::Check();

    if(dirty) {
      IRender::EnableDepthTest();

      IRender::SetClearColour(0.2f, 0.2f, 0.4f, 1.0f);
      IRender::ClearBuffer(IRender::BufferBit::COLOUR | IRender::BufferBit::DEPTH);

      glUseProgram(ProgramID);
      glDrawArrays(GL_TRIANGLES, 0, 3);

      IRender::SwapBuffer(display, Platform::WindowContext(display));

      LOG->PrintMessage("Display updated.");
      dirty = false;
    }
  }
  return 0;
}