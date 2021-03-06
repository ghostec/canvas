#include "hitable_list.h"

namespace canvas {

HitableList::HitableList(const std::vector<Hitable*>& v) : list(v), Hitable(nullptr) {}

HitableList::HitableList(const std::vector<Hitable*>& v, Material* material_ptr) : list(v), Hitable(material_ptr) {}

bool HitableList::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
  hit_record tmp_rec;
  bool hit_anything = false;
  float closest_so_far = t_max;
  for(int i = 0; i < list.size(); i++) {
    if(list[i]->hit(r, t_min, closest_so_far, tmp_rec)) {
      hit_anything = true;
      closest_so_far = tmp_rec.t;
      rec = tmp_rec;
    }
  }
  if(hit_anything && material_ptr) rec.material_ptr = material_ptr; 
  return hit_anything;
}

bool HitableList::boundingBox(AABB& box) const {
  AABB b;
  bool has_box = false;
  for(const auto& h : list) {
    if(has_box && h->boundingBox(b)) box.expand(b);
    else if(h->boundingBox(b)) {
      box = b;
      has_box = true;
    } 
  }
  return has_box;
}

void HitableList::set(const std::vector<Hitable*> v) {
  list = v;
}

void HitableList::append(Hitable* h) {
  list.push_back(h);
}

HitableList& HitableList::operator+=(Hitable* el) {
  list.push_back(el);
  return *this;
}

HitableList& HitableList::operator=(const std::vector<Hitable*>& v) {
  list = v;
  return *this;
}

HitableList& HitableList::operator+=(const std::vector<Hitable*>& v) {
  list.insert(std::end(list), std::begin(v), std::end(v));
  return *this;
}

}
