#pragma once
#include <glm.hpp>
#include <filesystem>
#include <string>
#include <vector>
#include "shader.hpp"

struct Vertex
{
	glm::vec3 pos;
	glm::vec3 normal;
	glm::vec2 texPos;
};

struct Texture
{
	enum TYPE { DIFF, SPEC, NORM, HEIGHT };
	unsigned int id;
	TYPE type;
	std::filesystem::path path;
};

class Mesh
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	unsigned int VAO = 0;
	unsigned int VBO = 0;
	unsigned int EBO = 0;
	void setupMesh()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texPos));
		glBindVertexArray(0);
	}
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) :
		vertices(vertices), indices(indices), textures(textures) {
		setupMesh();
	}
	void draw(Shader& shader)
	{
		unsigned int diffNum = 1;
		unsigned int specNum = 1;
		unsigned int normNum = 1;
		unsigned int heightNum = 1;
		for (size_t i = 0; i < textures.size(); ++i)
		{
			std::string name = "material.";
			glActiveTexture(GL_TEXTURE0 + i);
			switch (textures[i].type)
			{
			default:
			case Texture::DIFF:
				name += "diffuse";
				name += std::to_string(diffNum++);
				shader.setInt(i, name.c_str());
				break;
			case Texture::SPEC:
				name += "specular";
				name += std::to_string(specNum++);
				shader.setInt(i, name.c_str());
				break;
			case Texture::NORM:
				name += "normal";
				name += std::to_string(normNum++);
				shader.setInt(i, name.c_str());
				break;
			case Texture::HEIGHT:
				name += "height";
				name += std::to_string(normNum++);
				shader.setInt(i, name.c_str());
			}
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glActiveTexture(GL_TEXTURE0);
	}
};