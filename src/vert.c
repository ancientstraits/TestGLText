#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "vert.h"

GLuint makeVertBuffer(GLfloat* vert_points, GLuint vert_count, GLuint draw_state){
	GLuint vbo;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 3 * vert_count * sizeof(GLfloat), vert_points,
	draw_state);

	return vbo;
}

GLuint makeVertArray(GLuint vbo){
	GLuint vao;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	return vao;
}