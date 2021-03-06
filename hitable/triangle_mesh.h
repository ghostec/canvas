#ifndef HITABLE_TRIANGLEMESHH
#define HITABLE_TRIANGLEMESHH

#include <vector>
#include <array>
#include "util/vec3.h"
#include "util/kd_node.h"
#include "hitable.h"

namespace canvas {

using std::vector;
using std::array;

class TriangleMesh : public Hitable {
private:
  KDNode* kd_node;
public:
  TriangleMesh(const vector<vec3>& vertices, const vector<vec3>& normals, const vector<array<size_t, 3>>& faces);
  TriangleMesh(const vector<vec3>& vertices, const vector<vec3>& normals,
      const vector<array<size_t, 3>>& faces, Material* material_ptr);
  virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
  virtual bool boundingBox(AABB& box) const;
};

}

#endif
