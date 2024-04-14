#pragma once

#include "object/renderable.hh"
#include "mesh/mesh.hh"
#include "object/transform.hh"

class Object : public Renderable{
  public:
    Object(Mesh &mesh);
    Transform transform = Transform::identity();
    void render(Shader& shader) override;

  private:
    Mesh &attachedMesh_;
};
