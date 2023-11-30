#ifndef MESH_H
#define MESH_H

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>

struct tri{
    int vids[3];
    int vtids[3];
};

struct mesh{
    float*v;
    unsigned int v_nb;
    float *vt;
    unsigned int vt_nb;
    struct tri* tris;
    unsigned int tris_nb;
};

typedef void (*lineParser)(char *line, size_t size, struct mesh *m);

struct mesh*create_mesh_from_obj(const char *path);
void destroy_mesh(struct mesh *mesh);

#endif /* !MESH_H */
