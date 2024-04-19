#include "camera.hh"
#include "tools.hh"
#include <GLFW/glfw3.h>
#include <glm/common.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/quaternion_float.hpp>
#include <glm/ext/quaternion_trigonometric.hpp>
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>

mat4 Camera::getMatrix() {
    mat4 m = transform.getMatrix();
    mat4 pers = glm::perspective(glm::radians(fov_), WIDTH / (1.0f * HEIGHT),
                                 near_, far_);
    m = pers * m;
    return m;
}

Camera::Camera(float fov, float near, float far)
    : fov_(fov), near_(near), far_(far) {}

void Camera::inputs(GLFWwindow *win) {
    float deg = glm::radians(sensitivity);
    quat rot = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS)
        transform.position += speed * -transform.left();
    if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS)
        transform.position += speed * transform.left();
    if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS)
        transform.position += speed * transform.front();
    if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS)
        transform.position += speed * -transform.front();
    if (glfwGetKey(win, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        transform.position += speed * transform.up();
    if (glfwGetKey(win, GLFW_KEY_SPACE) == GLFW_PRESS)
        transform.position += speed * -transform.up();
    if (glfwGetKey(win, GLFW_KEY_L) == GLFW_PRESS) {
        rot = glm::angleAxis(deg, vec3(0.0f, 1.0f, 0.0f));
    }
    if (glfwGetKey(win, GLFW_KEY_H) == GLFW_PRESS)
        rot = glm::angleAxis(-deg, vec3(0.0f, 1.0f, 0.0f)) * rot;
    if (glfwGetKey(win, GLFW_KEY_J) == GLFW_PRESS)
        rot = glm::angleAxis(deg, vec3(1.0f, 0.0f, 0.0f)) * rot;
    if (glfwGetKey(win, GLFW_KEY_K) == GLFW_PRESS)
        rot = glm::angleAxis(-deg, vec3(1.0f, 0.0f, 0.0f)) * rot;
    transform.rotation = rot * transform.rotation;
}
Camera &Camera::mainCamera() {
    static Camera camera;
    return camera;
}
