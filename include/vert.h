#ifndef VERT_H
#define VERT_H

#include <GLFW/glfw3.h>

GLuint makeVertBuffer(GLfloat* vert_points, GLuint vert_count, GLuint draw_state);
GLuint makeVertArray(GLuint vbo);

#endif