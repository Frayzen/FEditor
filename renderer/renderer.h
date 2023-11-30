#ifndef RENDERER_H
#define RENDERER_H

#include "renderer/mesh/mesh.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Renderer{
    GLFWwindow *window;
    GLint vertexShader;
    GLint fragmentShader;
    GLint shaderProgram;
    mesh** meshes; 
    unsigned int mesh_nb;
} renderer;

renderer *initRenderer(void);
void defineVertexShader(renderer *rd, const char *path);
void defineFragmentShader(renderer *rd, const char *path);
int startRendering(renderer *rd);
void destroyRenderer(renderer *rd);
void addMesh(renderer *rd, mesh *m);

#endif /* !RENDERER_H */
