in vec3 in_pos;
in mat4 M;

uniform mat4 VP;

out vec3 vt_worldPos;
flat out vec3 vt_worldPosI;
out float vt_z;
//uniform mat4 M;

void main() {
  mat4 MVP = VP * M;
  vt_worldPos = in_pos;
  vt_worldPosI = M[3].xyz;
  gl_Position = MVP * vec4(in_pos, 1.0);
}