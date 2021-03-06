#include <vector>
#include <array>
#include <string>
#include <cmath>
#include "util/vec3.h"
#include "util/obj_parser.h"
#include "hitable/sphere.h"
#include "hitable/triangle.h"
#include "hitable/triangle_mesh.h"
#include "material/lambertian.h"
#include "material/metal.h"
#include "material/dielectric.h"
#include "light/point_light.h"
#include "scene.h"

namespace canvas {

void Scene::build() {
  Hitable* el_1 = new Sphere(vec3(0,0,0), 0.5, new Lambertian(vec3(0.9, 0.1, 0.0)));
  Hitable* el_2 = new Sphere(vec3(0,-103.5,-1), 100, new Lambertian(vec3(0.8, 0.5, 0.7)));
  Hitable* el_3 = new Sphere(vec3(1,0,-1), 0.5, new Metal(vec3(0.8, 0.6, 0.2), 0.2));
  Hitable* el_4 = new Sphere(vec3(-1,0,-1), 0.5, new Lambertian(vec3(0.1, 0.2, 0.5)));
  Hitable* el_5 = new Sphere(vec3(0,1,-2), 0.5, new Lambertian(vec3(0.5, 0.0, 0.0)));

  ObjParser obj_parser;

  std::vector<vec3> vertices, normals;
  std::vector<std::array<size_t, 3>> faces;

  obj_parser.parse("cow.obj", vertices, normals, faces);
  Hitable* gourd = new TriangleMesh(vertices, normals, faces, new Lambertian(0.9));

  //world = {el_1, el_2, el_3, el_4, el_6};
  world = new HitableList({el_2, gourd});

  ambient_light = new AmbientLight(vec3(1), 0.3);

  lights = { new PointLight(vec3(-4, 7, 4), vec3(1.0), 5) };

  //lights = {};
}

void Scene::setWorld(std::vector<Hitable*> v_hitable) {
  world->set(v_hitable);
}

void Scene::addHitable(Hitable* hitable) {
  world->append(hitable);
}

void Scene::setAmbientLight(AmbientLight* ambient_light) {
  this->ambient_light = ambient_light;
}
void Scene::addLight(Light* light) {
  lights.push_back(light);
}

}
