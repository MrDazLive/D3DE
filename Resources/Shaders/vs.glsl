layout(location = 0) in vec3 in_pos;
layout(location = 1) in vec3 in_nor;
//in mat4 M;

uniform mat4 M;
uniform mat4 VP;

out vec3 vt_localPosV;
out vec3 vt_localNorV;
flat out vec3 vt_localPosI;

void main() {
  mat4 MVP = VP * M;
  vt_localPosV = in_pos;
  vt_localNorV = in_nor;
  vt_localPosI = M[3].xyz;
  gl_Position = MVP * vec4(in_pos, 1.0);
}