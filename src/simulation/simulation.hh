#pragma once

#include "mesh/mesh.hh"
#include "gui/gui.hh"
#include "shader/compute.hh"
#include "shader/render.hh"
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

using namespace glm;
class Simulation {
  public:
    Simulation();
    vec2 screenSize = vec2(2000, 1000);
    vec3 bounds = vec3(10.0f, 10.0f, 0.0f);
    ivec2 size = ivec2(10, 10);
    vec2 offset = vec2(1.0f, 1.0f);
    float mass = 3.0f;
    float pressureMultiplier = 20.0f;
    float targetedDensity = 2.0f;
    float radius = 1.5f;
    float viscosity = 1.5f;
    const float appearanceRadiusCoeff = 0.3f;
    vec3 gravity = vec3(0.0, -9.0f, 0.0f);
    Camera cam;
    bool isRunning = false;
    void restartSimulation();
    void mainLoop();
    void step();
    std::vector<Object>& getParticles();

  private:
    void createObjects();
    void setupBuffers();
    void updateBuffers();
    void updateBbox();
    double last_;
    GUI gui_;
    Mesh particleMesh_;
    Mesh boundingMesh_;
    Compute densityCmpt_;
    Compute velocityCpt_;
    Render renderer_;
    GLFWwindow* win_;
};
