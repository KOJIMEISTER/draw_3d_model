#pragma once
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Shader
{
	unsigned int program = 0;
	unsigned int vertex = 0;
	unsigned int fragment = 0;
	std::string strContent = "";
	const char* content = nullptr;
	void fileRead(std::filesystem::path path)
	{
		std::ifstream input(path);
		if (input.is_open())
		{
			std::stringstream str;
			str << input.rdbuf();
			strContent = str.str();
			content = strContent.c_str();
			input.close();
		}
	}
	void checkCompileErrors(GLuint shader, std::string type)
	{
		GLint success;
		GLchar infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}
public:
	void loadShaderVertex(std::filesystem::path path)
	{
		vertex = glCreateShader(GL_VERTEX_SHADER);
		fileRead(path);
		glShaderSource(vertex, 1, &content, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "SHADER");
	}
	void loadShaderFragment(std::filesystem::path path)
	{
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		fileRead(path);
		glShaderSource(fragment, 1, &content, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "SHADER");
	}
	void linkShader()
	{
		program = glCreateProgram();
		glAttachShader(program, vertex);
		glAttachShader(program, fragment);
		glLinkProgram(program);
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		checkCompileErrors(program, "SHADER");
	}
	void use()
	{
		glUseProgram(program);
	}
	unsigned int& getProgram()
	{
		return program;
	}
	void setMat4(glm::mat4 value, std::string name)
	{
		glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}
	void setInt(unsigned int value, std::string name)
	{
		glUniform1i(glGetUniformLocation(program, name.c_str()), value);
	}
	void setVec3(float value1, float value2, float value3, std::string name)
	{
		glUniform3f(glGetUniformLocation(program, name.c_str()), value1, value2, value3);
	}
	void setVec3(glm::vec3 value, std::string name)
	{
		glUniform3f(glGetUniformLocation(program, name.c_str()), value.x, value.y, value.z);
	}
	void setFloat(float value, std::string name)
	{
		glUniform1f(glGetUniformLocation(program, name.c_str()), value);
	}
};