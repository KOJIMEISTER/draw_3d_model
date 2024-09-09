#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Camera
{
	glm::mat4 view = glm::mat4(0.f);
	glm::vec3 camDir = { 0.f, 0.f, 0.f };
	glm::vec3 camUp = { 0.f, 1.f, 0.f };
	glm::vec3 camFront = { 0.f, 0.f, -1.f };
	glm::vec3 camPos = { 0.f, 0.f, 0.f };
	glm::vec3 camRight = {0.f, 0.f, 0.f};
	glm::vec3 worldUp = {0.f, 1.f, 0.f};
	float sensitivity = 0.05f;
	float speed = 0.005f;
	float pitch = 0.f;
	float yaw = 0.f;
	Camera() {}
	~Camera() {}
	void calcCam()
	{
		camDir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		camDir.y = sin(glm::radians(pitch));
		camDir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		camFront = glm::normalize(camDir);
		camRight = glm::normalize(glm::cross(camFront, worldUp));
		camUp = glm::normalize(glm::cross(camRight, camFront));
	}
public:
	static Camera* getInst()
	{
		static Camera camera;
		return &camera;
	}
	void moveFront()
	{
		camPos += speed * camFront;
	}
	void moveBack()
	{
		camPos -= speed * camFront;
	}
	void moveRight()
	{
		camPos -= camRight * speed;
	}
	void moveLeft()
	{
		camPos += camRight * speed;
	}
	void changePitch(float difPitch)
	{
		pitch += difPitch * sensitivity;
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
		calcCam();
	}
	void changeYaw(float difYaw)
	{
		yaw += difYaw * sensitivity;
		if (yaw > 360.f)
			yaw = 0.f;
		if (yaw < -360.f)
			yaw = 0.f;
		calcCam();
	}
	glm::mat4 getView()
	{
		return view = glm::lookAt(camPos, camPos + camFront, camUp);;
	}
	glm::vec3 getPos()
	{
		return camPos;
	}
};