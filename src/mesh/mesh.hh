#pragma once

#include "mesh/submesh.hh"
#include "object/object.hh"
#include <GL/gl.h>
#include "object/transform.hh"
#include "shader/render.hh"
#include <glm/fwd.hpp>
#include <string>
#include <vector>

using namespace glm;

class Mesh : public Renderable {
  public:
    static Mesh createFrom(std::string path);
    void render(Render &shader, Camera &camera);
    const unsigned int id;

    std::vector<Object> &getObjects();
    Object &createObject();

  private:
    std::vector<SubMesh> subMeshes_;
    std::vector<Object> objects_;
    Mesh();
};
