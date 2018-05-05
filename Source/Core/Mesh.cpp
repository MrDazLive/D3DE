#include "Mesh.h"

namespace Core {


  Mesh::Mesh(const Flag8& attribs) { attributes.RaiseFlags(attribs); }

  bool Mesh::isValid() const {
    if (attributes.GetFlags() == 0 || elements.empty())
      return false;

    auto validate = [this] (Flags flag, const size_t vSize, size_t& size) {
      if (attributes.CheckFlags(flag)) {
        if  (vSize == 0)  return false;
        if  (size  == 0)  size = vSize;
        else              return size == vSize;
      }
      return true;
    };

    size_t size = 0;
    if (!validate(Flags::POSITION,  positions.size(), size)) return false;
    if (!validate(Flags::NORMAL,    normals.size(),   size)) return false;
    if (!validate(Flags::UV,        uvs.size(),       size)) return false;
    
    for (auto i : elements)
      if (i[0] > size || i[1] > size || i[2] > size)
        return false;

    return true;
  }

  static void Normals(Mesh& mesh, const unsigned int resolution) {
    for (unsigned int j = 0; j < resolution; ++j) {
      for (unsigned int i = 0; i < resolution; ++i) {
        unsigned int a = (j * (resolution + 1)) + i;
        unsigned int b = a + 1;
        unsigned int c = a + resolution + 1;
        unsigned int d = c + 1;
        mesh.elements.push_back({ a, b, c });
        mesh.elements.push_back({ c, b, d });
      }
    }
  }

  void Mesh::Plane(Mesh& mesh, const unsigned int resolution) {
    const float step = 1.0f / (float)resolution;
    for (unsigned int j = 0; j <= resolution; ++j) {
      for (unsigned int i = 0; i <= resolution; ++i) {
        float u = step * (float)i;
        float v = step * (float)j;
        if (mesh.attributes.CheckFlags(Flags::POSITION)) mesh.positions.push_back  ({ u - 0.5f, 0.0f, v - 0.5f });
        if (mesh.attributes.CheckFlags(Flags::NORMAL  )) mesh.normals.push_back    ({ 0.0f, 1.0f, 0.0f });
        if (mesh.attributes.CheckFlags(Flags::UV      )) mesh.uvs.push_back        ({ u, v });
      }
    }
    Normals(mesh, resolution);
  }

  void Mesh::Sphere(Mesh& mesh, const unsigned int resolution) {
    const float step = 1.0f / (float)resolution;
    for (unsigned int j = 0; j <= resolution; ++j) {
      for (unsigned int i = 0; i <= resolution; ++i) {
        const float HALF_PI = (float)PI / 2.0f;
        float u = step * (float)i;
        float v = step * (float)j;
        float x = u * (float)PI - HALF_PI;
        float y = v * (float)PI * 2.0f;
        float a = cos(x) * cos(y);
        float b = cos(x) * sin(y);
        float c = sin(x);
        if (mesh.attributes.CheckFlags(Flags::POSITION)) mesh.positions.push_back  ({ a * 0.5f, b * 0.5f, c * 0.5f });
        if (mesh.attributes.CheckFlags(Flags::NORMAL  )) mesh.normals.push_back    ({ a, b, c });
        if (mesh.attributes.CheckFlags(Flags::UV      )) mesh.uvs.push_back        ({ u, v });
      }
    }
    Normals(mesh, resolution);
  }

}