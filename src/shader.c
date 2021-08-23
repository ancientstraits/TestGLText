#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "util.h"

static GLuint singleShader(GLuint shader_state, const char* shader_code) {
	GLuint shader = glCreateShader(shader_state);
	glShaderSource(shader, 1, &shader_code, NULL);
	glCompileShader(shader);

	GLint result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (!result) {
		GLint log_length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
		
		char log_err[log_length + 1];
		glGetShaderInfoLog(shader, log_length, NULL, log_err);

		printf("Failed to compile %s shader:\n%s\n",
			shader_state == GL_VERTEX_SHADER ? "vertex" : "fragment",
			log_err);
		
		return 0;
	}

	return shader;
}

GLuint
createShader(const char* vert_path,
const char* frag_path) {
	char* vert_code = readFile(vert_path);
	if (!vert_code) return 0;
	GLuint vert_shader = singleShader(GL_VERTEX_SHADER, vert_code);
	free(vert_code);
	if (!vert_shader) return 0;

	char* frag_code = readFile(frag_path);
	if (!frag_code) return 0;
	GLuint frag_shader = singleShader(GL_FRAGMENT_SHADER, frag_code);
	free(frag_code);
	if (!frag_shader) return 0;

	GLuint full_shader = glCreateProgram();

	glAttachShader(full_shader, vert_shader);
	glAttachShader(full_shader, frag_shader);
	glLinkProgram(full_shader);

	return full_shader;
}