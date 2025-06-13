#pragma once

#include "pch.h"

#ifndef __gl_h_
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#endif // !__gl_h_

#include <iostream>
#include <vector>

#include "RessourceManager.h"
#include "LibMath/Vector/Vector3.h"
#include "Camera.h"
#include "Light.h"
#include "SceneGraph.h"
#include "SkyBox.h"
#include "memoryLeak.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

class Application
{
public:
	Application();
	~Application() = default;

	int windowLoop(void);
	int initWindow(void);
	
	void loadRessource(void);
	void initLight(void);
	void uploadLightCountToGPU(void);
	void uploadToGPU(float deltaTime);

	RessourceManager m_ressourceManager;
private:
	
	SkyBox m_skybox;

	Camera m_camera;

	Mesh m_mesh;
	Mesh m_groundMesh;

	std::vector<PointLight> m_pointLights;
	std::vector<SpotLight> m_spotLights;
	DirectionalLight m_directionalLight;

	float m_lastFrame = 0.0;

	Graph<SceneNode> m_graph;

	void processInput(GLFWwindow* window, Camera& camera);

	GLFWwindow* m_window = NULL;
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

