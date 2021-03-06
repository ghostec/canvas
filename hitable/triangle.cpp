#include <cmath>
#include "triangle.h"

namespace canvas {

Triangle::Triangle(const vec3& a, const vec3& b, const vec3& c,
      const vec3& n_a, const vec3& n_b, const vec3& n_c)
  : a(a), b(b), c(c), n_a(n_a), n_b(n_b), n_c(n_c) {}

Triangle::Triangle(const vec3& a, const vec3& b, const vec3& c,
      const vec3& n_a, const vec3& n_b, const vec3& n_c, Material* material_ptr)
  : a(a), b(b), c(c), n_a(n_a), n_b(n_b), n_c(n_c), Hitable(material_ptr) {}

bool Triangle::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
  vec3 e1, e2;
  e1 = b - a;
  e2 = c - a;

  float ERR = 0.001;

  vec3 P = r.d ^ e2;
  float det = e1 * P;
  if(det > -ERR && det < ERR) return false;

  float inv_det = 1.0 / det;

  vec3 T = r.o - a;

  float u = (T * P) * inv_det;
  if(u < 0.0 || u > 1.0) return false;

  vec3 Q = T ^ e1;

  float v = (r.d * Q) * inv_det;
  if(v < 0.0 || v > 1.0) return false;
  if(u + v > 1.0) return false;

  float t = (e2 * Q) * inv_det;
  

  if(t < t_min) return false;

  vec3 normal = ((1.0-u-v) * n_a + u * n_b + v * n_c).hat();
  //vec3 normal = e1 ^ e2;
  rec.t = t;
  rec.p = r.point_at_parameter(t);
  rec.normal = normal;
  rec.material_ptr = material_ptr;
  return true;
}

bool Triangle::boundingBox(AABB& box) const {
  float ERR = 0.001;
  vec3 _min, _max;
  _min[0] = std::min({a[0], b[0], c[0]}) - ERR;
  _min[1] = std::min({a[1], b[1], c[1]}) - ERR;
  _min[2] = std::min({a[2], b[2], c[2]}) - ERR;
  _max[0] = std::max({a[0], b[0], c[0]}) + ERR;
  _max[1] = std::max({a[1], b[1], c[1]}) + ERR;
  _max[2] = std::max({a[2], b[2], c[2]}) + ERR;
  box = AABB(_min, _max);
  return true;
}

}
