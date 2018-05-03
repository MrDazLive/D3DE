#include "Mesh.h"

namespace Core {


  Mesh::Mesh(const Flag8& attribs) : attributes(attribs) { }

  bool Mesh::isValid() const {
    if (attributes == 0 || elements.empty())
      return false;

    auto validate = [this] (Flags flag, const size_t vSize, size_t& size) {
      if (attributes & flag) {
        if  (vSize == 0)  return false;
        if  (size == 0)   size = vSize;
        else              return size == vSize;
      }
      return true;
    };

    size_t size = 0;
    if (!validate(Flags::POSITION,  positions.size(), size)) return false;
    if (!validate(Flags::NORMAL,    normals.size(),   size)) return false;
    if (!validate(Flags::UV,        uvs.size(),       size)) return false;
    
    for (auto i : elements)
      if (i > size)
        return false;

    return true;
  }

  void Mesh::Plane(Mesh& mesh, const unsigned int resolution) {

  }

  void Mesh::Sphere(Mesh& mesh, const unsigned int resolution) {
    const float step = 1.0f / (float)resolution;
    for (unsigned int j = 0; j <= resolution; ++j) {
      for (unsigned int i = 0; i <= resolution; ++i) {
        const float HALF_PI = (float)PI / 2.0f;
        float u = (step * (float)i * (float)PI) + HALF_PI;
        float v = step * (float)j * (float)PI * 2.0f;
        float a = 0.5f * cos(u) * cos(v);
        float b = 0.5f * cos(u) * sin(v);
        float c = 0.5f * sin(u);
        mesh.positions.push_back({ a, b, c });
      }
    }
    for (unsigned int j = 0; j < resolution; ++j) {
      for (unsigned int i = 0; i < resolution; ++i) {
        unsigned int a = (j * (resolution + 1)) + i;
        unsigned int b = a + 1;
        unsigned int c = a + resolution + 1;
        unsigned int d = c + 1;
        mesh.elements.push_back({ b, a, c });
        mesh.elements.push_back({ b, c, d });
      }
    }
  }

}