#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "mesh.hpp"
#include <algorithm>

class Model
{
	std::vector<Mesh> meshes;
	std::vector<Texture> texturesLoaded;
	std::filesystem::path path;
	std::filesystem::path dir;
	bool gammaCorrection;
	void loadModel()
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path.string(), aiProcess_Triangulate | aiProcess_FlipUVs);
		dir = path.parent_path();
		processNode(scene->mRootNode, scene);
	}
	void processNode(aiNode* node, const aiScene* scene)
	{
		for (unsigned int i = 0; i < node->mNumMeshes; ++i)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(processMesh(mesh, scene));
		}
		for (unsigned int i = 0; i < node->mNumChildren; ++i)
		{
			processNode(node->mChildren[i], scene);
		}
	}
	Mesh processMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;
		for (int i = 0; i < mesh->mNumVertices; ++i)
		{
			Vertex vertex;
			glm::vec3 vector;
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.pos = vector;
			if (mesh->HasNormals())
			{
				vector.x = mesh->mNormals[i].x;
				vector.y = mesh->mNormals[i].y;
				vector.z = mesh->mNormals[i].z;
				vertex.normal = vector;
			}
			if (mesh->mTextureCoords[0])
			{
				glm::vec2 vector2;
				vector2.x = mesh->mTextureCoords[0][i].x;
				vector2.y = mesh->mTextureCoords[0][i].y;
				vertex.texPos = vector2;
			}
			else {
				vertex.texPos = glm::vec2(0.f, 0.f);
			}
			vertices.push_back(vertex);
		}
		for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
		{
			aiFace* face = &mesh->mFaces[i];
			for (unsigned int j = 0; j < face->mNumIndices; ++j)
			{
				indices.push_back(face->mIndices[j]);
			}
		}
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture> diffMaps = loadMaterialTexture(material, aiTextureType_DIFFUSE, Texture::DIFF);
		textures.insert(textures.end(), diffMaps.begin(), diffMaps.end());
		std::vector<Texture> specMaps = loadMaterialTexture(material, aiTextureType_SPECULAR, Texture::SPEC);
		textures.insert(textures.end(), specMaps.begin(), specMaps.end());
		std::vector<Texture> normMaps = loadMaterialTexture(material, aiTextureType_NORMALS, Texture::NORM);
		textures.insert(textures.end(), normMaps.begin(), normMaps.end());
		std::vector<Texture> heightMaps = loadMaterialTexture(material, aiTextureType_HEIGHT, Texture::HEIGHT);
		textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
		return Mesh(vertices, indices, textures);
	}
	std::vector<Texture> loadMaterialTexture(aiMaterial* mat, aiTextureType type, Texture::TYPE typeIdx)
	{
		std::vector<Texture> textures;
		for (unsigned int i = 0; i < mat->GetTextureCount(type); ++i)
		{
			aiString path;
			mat->GetTexture(type, i, &path);
			auto itTex = std::find_if(texturesLoaded.begin(), texturesLoaded.end(), [&path](Texture& texture) {return texture.path == path.C_Str(); });
			if (itTex != texturesLoaded.end())
			{
				textures.push_back(*itTex);
			}
			else {
				Texture texture;
				texture.id = textureFromFile(path.C_Str());
				texture.type = typeIdx;
				texture.path = path.C_Str();
				textures.push_back(texture);
				texturesLoaded.push_back(texture);
			}
		}
		return textures;
	}
	unsigned int textureFromFile(std::filesystem::path path)
	{
		unsigned int texId = 0;
		int width = 0, height = 0, comps = 0;
		glGenTextures(1, &texId);
		std::filesystem::path imgPath = this->dir;
		imgPath += '\\';
		imgPath += path;
		unsigned char* data = stbi_load(imgPath.string().c_str(), &width, &height, &comps, 0);
		if (data)
		{
			GLenum format;
			switch (comps) {
			default:
			case 1:
				format = GL_RED;
				break;
			case 3:
				format = GL_RGB;
				break;
			case 4:
				format = GL_RGBA;
			}
			glBindTexture(GL_TEXTURE_2D, texId);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			stbi_image_free(data);
		}
		return texId;
	}
public:
	Model(std::filesystem::path path) : path(path) {
		loadModel();
	}
	void draw(Shader& shader)
	{
		for (auto& mesh : meshes)
			mesh.draw(shader);
	}
};