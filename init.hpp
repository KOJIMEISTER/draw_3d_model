#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.hpp"
#include "camera.hpp"
#include "model.hpp"

void callbackResize(GLFWwindow* window, int width, int height);
void callbackMouse(GLFWwindow* window, double xpos, double ypos);

class OGLMain
{
	GLFWwindow* window = nullptr;
	Shader* sceneShader = nullptr;
	int windWidth = 800;
	int windHeight = 600;
	void inputEvent()
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			Camera::getInst()->moveFront();
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			Camera::getInst()->moveBack();
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			Camera::getInst()->moveLeft();
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			Camera::getInst()->moveRight();
		}
	}
	void initSceneShader()
	{
		sceneShader = new Shader();
		sceneShader->loadShaderVertex("scene.vert");
		sceneShader->loadShaderFragment("scene.frag");
		sceneShader->linkShader();
	}
	void initLight()
	{
		sceneShader->setVec3(Camera::getInst()->getPos(), "viewPos");
		sceneShader->setFloat(32.0f, "material.shininess");
		sceneShader->setVec3(glm::cos(-0.2f + (float)glfwGetTime()), glm::sin(-1.0f + (float)glfwGetTime()), -0.3f, "dirLight.direction");
		sceneShader->setVec3(0.05f, 0.05f, 0.05f, "dirLight.ambient");
		sceneShader->setVec3(0.4f, 0.4f, 0.4f, "dirLight.diffuse");
		sceneShader->setVec3(0.5f, 0.5f, 0.5f, "dirLight.specular");
	}
	OGLMain() {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		window = glfwCreateWindow(windWidth, windHeight, "CG", NULL, NULL);
		glfwMakeContextCurrent(window);
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		glfwSetFramebufferSizeCallback(window, callbackResize);
		glfwSetCursorPosCallback(window, callbackMouse);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glViewport(0, 0, windWidth, windHeight);
		glEnable(GL_DEPTH_TEST);
		glfwSetCursorPos(window, windWidth / 2, windHeight / 2);
		stbi_set_flip_vertically_on_load(true);
		initSceneShader();
	}
	~OGLMain() {
		glfwTerminate();
		if (sceneShader)
			delete sceneShader;
	}
public:
	static OGLMain* getInst()
	{
		static OGLMain oglmain;
		return &oglmain;
	}
	void changeSize(int width, int height)
	{
		windWidth = width;
		windHeight = height;
		glViewport(0, 0, windWidth, windHeight);
	}
	void moveMouse(double xpos, double ypos)
	{
		Camera::getInst()->changePitch(windHeight / 2 - ypos);
		Camera::getInst()->changeYaw(xpos - windWidth / 2);
		glfwSetCursorPos(window, windWidth / 2, windHeight / 2);
	}
	void run()
	{
		Model model("model\\untitled.obj");
		while (!glfwWindowShouldClose(window))
		{
			inputEvent();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			sceneShader->use();
			sceneShader->setMat4(Camera::getInst()->getView(), "view");
			sceneShader->setMat4(glm::perspective(glm::radians(90.f), (float)windWidth / (float)windHeight, .1f, 100.f), "projection");
			sceneShader->setMat4(glm::mat4(1.f), "model");
			initLight();
			model.draw(*sceneShader);
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}
};

void callbackResize(GLFWwindow* window, int width, int height)
{
	OGLMain::getInst()->changeSize(width, height);
}

void callbackMouse(GLFWwindow* window, double xpos, double ypos)
{
	OGLMain::getInst()->moveMouse(xpos, ypos);
}