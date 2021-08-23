#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "vert.h"
#include "shader.h"

static void getWindowSize(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

static GLfloat vert_points[] = {
	0.0f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5, -0.5f, 0.0f,
};

int main(int argc, char *argv[]) {
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		return 1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE)
#endif
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(600, 400, "Tutorial 01", NULL, NULL);
	if (!window) {
		fprintf(stderr, "Failed to create window\n");
		return 1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, getWindowSize);

	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return 1;
	}

	GLuint vbo = makeVertBuffer(vert_points, 3, GL_STATIC_DRAW);
	GLuint vao = makeVertArray(vbo);
	GLuint shader = createShader("res/main.vert", "res/main.frag");
	if (!shader) return 1;

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0, 0.3, 0.3, 0.0);

		glUseProgram(shader);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}