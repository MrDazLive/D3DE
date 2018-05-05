#include "Flags.h"

#include <Types/Vector3.h>

#include <vector>

namespace Core {

  struct Mesh {
    enum Flags : Flag8 {
      POSITION  = FLAG(0),
      NORMAL    = FLAG(1),
      UV        = FLAG(2)
    };

    std::vector<DTU::Vector3f>  positions     { };
    std::vector<DTU::Vector3f>  normals       { };
    std::vector<DTU::Vector2f>  uvs           { };

    std::vector<DTU::Vector3u>  elements      { };
    Flags8                      attributes    { };

                                Mesh          (const Flag8&);

    bool                        isValid       () const;

    static void                 Plane         (Mesh&, const unsigned int);
    static void                 Sphere        (Mesh&, const unsigned int);
  };

}