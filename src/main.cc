#include <algorithm>
#include <cstdlib>
#include <glm/fwd.hpp>
#include <iostream>
#include <GL/glew.h>
#include "constants.hh"
#include "mesh/mesh.hh"
#include "object/camera.hh"
#include "object/object.hh"
#include "shader/compute.hh"
#include "shader/render.hh"
#include "tools.hh"
#include <GLFW/glfw3.h>
#include <string.h>

void prettyPrintMat4(const glm::mat4 &matrix) {

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << matrix[i][j] << " ";
        }

        std::cout << std::endl;
    }
}
void GLAPIENTRY DebugCallback(GLenum source, GLenum type, GLuint id,
                              GLenum severity, GLsizei length,
                              const GLchar *msg, const void *userParam) {
    (void)source;
    (void)type;
    (void)id;
    (void)severity;
    (void)length;
    (void)userParam;
    std::cout << msg << '\n';
    std::flush(std::cout);
}
int main() {
    glfwInit();
    // Define required version of OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Specify that the project uses modern functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    // Debug
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

    // Creation of the window
    GLFWwindow *win =
        glfwCreateWindow(screenSize.x, screenSize.y, "FEngine", nullptr, nullptr);
    FAIL_ON(win == nullptr, "An error occured while creating the window");
    glfwMakeContextCurrent(win);

    FAIL_ON(glewInit() != GLEW_OK, "Glew could not be initialized");
    glViewport(0, 0, screenSize.x, screenSize.y);

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(DebugCallback, 0);

    Render render =
        Render("assets/shaders/default.vert", "assets/shaders/default.frag");

    Mesh mesh = Mesh::createFrom("assets/teddy.obj");
    Object obj = mesh.createObject();
    auto t = obj.getTransform();
    t.position.z = -1.0f;
    //t.scale = vec3(0.1f);
    obj.setTransform(t);
    *obj.getColor() = vec4(1.0f, 0.1f, 0.1f, 1.0f);

    glfwSetTime(0);
    double lastSec = glfwGetTime();
    int fps = 0;

    glEnable(GL_DEPTH_TEST);
    Camera::mainCamera().transform.position.z = -13.5;
    // Main loop
    while (!glfwWindowShouldClose(win)) {
        // Take care of events
        glfwPollEvents();
        // Background color
        glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        double cur = glfwGetTime();
        if (cur - lastSec >= 1.0) {
            lastSec += 1.0;
            std::cout << "FPS: " << fps << '\n';
            fps = 0;
        }
        fps++;

        Camera::mainCamera().inputs();
        mesh.render(render, Camera::mainCamera()); 

        glfwSwapBuffers(win);
    }

    clean_exit(0);
}
