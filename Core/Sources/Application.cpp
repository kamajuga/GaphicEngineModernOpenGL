#include "Application.h"
#include "Model.h"
#include "Shader.h"
#include "Mesh.h"
#include "LibMath/Angle.h"
#include "memoryLeak.h"
#include <STB/stb_image.h>

void CheckGLError(const std::string& location) {
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		std::cout << "OpenGL error at " << location << ": " << error << std::endl;
	}
}


unsigned int loadCubemap(std::vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrComponents;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrComponents, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}

int Application::initWindow(void)
{
	// glfw: initialize and configure
	// ------------------------------
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	m_window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (m_window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(m_window);
	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

	// capture mouse
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(m_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

	// glad: load all OpenGL function pointers

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST); // Enable depth testing for 3D rendering
	//glfwWindowHint(GLFW_DEPTH_BITS, 24);

	return 0;
}

void Application::loadRessource(void)
{
	Model* model = m_ressourceManager.get<Model>("model");
	

	Model* ground = m_ressourceManager.get<Model>("ground");

	Shader* Shaders = m_ressourceManager.get<Shader>("shaders");

	Texture* texture = m_ressourceManager.create<Texture>("texture");
	texture->loadTexture("../../Core/Assets/Textures/awesomeface.png");
	texture->bindTextureUnit();

	*model = Parser::parse3DObject("../../Core/Assets/Meshes/tyra.obj");
	*ground = Parser::parse3DObject("../../Core/Assets/Meshes/floor.obj");

	std::vector<std::string> faces = { "../../Core/Assets/Textures/right.jpg",
							"../../Core/Assets/Textures/left.jpg",
							"../../Core/Assets/Textures/top.jpg",
							"../../Core/Assets/Textures/bottom.jpg",
							"../../Core/Assets/Textures/front.jpg",
							"../../Core/Assets/Textures/back.jpg" };

	Shaders->setVertexShader("../../Core/Shaders/VertexShader.vert");
	Shaders->setFragmentShader("../../Core/Shaders/FragmentShader.frag");
	Shaders->link();

	initLight();

}

void Application::initLight(void)
{
	// Directional light
	/*m_directionalLight = DirectionalLight(LibMath::Vector3(0.0f, 0.0f, 0.0f),
											LibMath::Radian(0.0f), 
											LibMath::Vector3(1.0f, 1.0f, 1.0f));*/
	// Point light
	PointLight pointLight(LibMath::Vector3(0, 05, 5), LibMath::Radian(0.f), LibMath::Vector3(1.f, 1.f, 1.f));
	m_pointLights.push_back(pointLight);
	// Ajust other parameters
	
	// Spot light
	/*SpotLight spotLight(LibMath::Vector3(0, 5, 5), LibMath::Radian(0), LibMath::Vector3(1.f, 1.f, 1.f));
	m_spotLights.push_back(spotLight);*/
	// Ajust other parameters
}

void Application::uploadLightCountToGPU(void)
{
	// Upload light count to GPU
	Shader* Shaders = m_ressourceManager.get<Shader>("shaders");

	GLint location = glGetUniformLocation(Shaders->m_program, "nbPointLights");
	if (location == -1) {
		std::cerr << "Warning: uniform 'nbPointLights' not found in shader program." << std::endl;
	}
	else {
		glUniform1i(location, (int)m_pointLights.size());
	}

	location = glGetUniformLocation(Shaders->m_program, "nbSpotLights");
	if (location == -1) {
		std::cerr << "Warning: uniform 'nbSpotLights' not found in shader program." << std::endl;
	}
	else {
		glUniform1i(location, (int)m_spotLights.size());
	}
}

void Application::uploadToGPU(float deltaTime)
{
	Shader* Shaders = m_ressourceManager.get<Shader>("shaders");

	m_camera.uploadPositionToGPU(Shaders->m_program, "CameraPos");
	CheckGLError("after UploadPositionToGPU");

	m_mesh.uploadMaterialToGPU(Shaders->m_program, "material");
	CheckGLError("after mesh.UploadMaterialToGPU");

	m_groundMesh.uploadMaterialToGPU(Shaders->m_program, "material");
	CheckGLError("after groundMesh.UploadMaterialToGPU");

	uploadLightCountToGPU();
	CheckGLError("after UploadLightCountToGPU");


	// Set up the light
	m_directionalLight.uploadLightToGPU(Shaders->m_program, "dLight", 0);
	CheckGLError("after directionalLight");

	for (size_t i = 0; i < m_pointLights.size(); i++)
	{
		m_pointLights[i].uploadLightToGPU(Shaders->m_program, "pLight", (int)i);
		CheckGLError("after pointLight " + std::to_string(i));
	}


	for (size_t i = 0; i < m_spotLights.size(); i++)
	{
		m_spotLights[i].update(deltaTime);
		m_spotLights[i].uploadLightToGPU(Shaders->m_program, "sLight", (int)i);
		CheckGLError("after spotLight " + std::to_string(i));
	}
}

Application::Application()
{
	m_camera = Camera(
		LibMath::Vector3(0.0f, 0.0f, 5.0f),   // eye (position)
		LibMath::Vector3(0.0f, 0.0f, 0.0f),   // center
		LibMath::Vector3(0.0f, 1.0f, 0.0f),   // up,
		45.0f, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
}

int Application::windowLoop(void)
{
	if (initWindow())
	{
		std::cout << "Failed to initialize window" << std::endl;
		return -1;
	}
	
	loadRessource();

	Model* model = m_ressourceManager.get<Model>("model");
	Model* ground = m_ressourceManager.get<Model>("ground");
	Shader* Shaders = m_ressourceManager.get<Shader>("shaders");
	Texture* texture = m_ressourceManager.get<Texture>("texture");

	Shader skyBoxShader;

	skyBoxShader.setVertexShader("../../Core/Shaders/SkyBoxVert.vert");
	skyBoxShader.setFragmentShader("../../Core/Shaders/SkyBoxFrag.frag");
	skyBoxShader.link();

	// Set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float skyboxVertices[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};

	unsigned int skyboxVAO, skyboxVBO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	model->bind();

	ground->bind();
	ground->setTexture(texture);

	std::vector<std::string> faces = { "../../Core/Assets/Textures/right.jpg",
							"../../Core/Assets/Textures/left.jpg",
							"../../Core/Assets/Textures/top.jpg",
							"../../Core/Assets/Textures/bottom.jpg",
							"../../Core/Assets/Textures/front.jpg",
							"../../Core/Assets/Textures/back.jpg" };

	unsigned int cubemapTexture = loadCubemap(faces);

	// Mesh
	m_mesh= model;
	m_mesh.SetMaterial(LibMath::Vector4(0.0f, .0f, .0f, 1.f), LibMath::Vector4(0.85f, .72f, .6f, 1.f), LibMath::Vector4(1.0f, 1.0f, 1.0f, 1.f), 32.0f);

	m_groundMesh =ground;
	m_groundMesh.SetMaterial(LibMath::Vector4(0.0f, .0f, .0f, 1.f), LibMath::Vector4(0.85f, .72f, .6f, 1.f), LibMath::Vector4(1.0f, 1.0f, 1.0f, 1.f), 32.0f);

	// Scene Graph
	std::shared_ptr<SceneNode>sceneNode = std::make_shared<SceneNode>();
	sceneNode->initialize(&m_mesh, Shaders, LibMath::Matrix4::identity().createTranslate({0.f, 0.f, 0.f}));
	sceneNode->addChild(&m_groundMesh, Shaders, LibMath::Matrix4::identity().createTranslate({ -1.f, 1.f, 2.f }));

	m_graph.addNode(sceneNode);

	float rotation = 0.0f;

	skyBoxShader.use();
	skyBoxShader.setInt("skybox", 0);


	while (!glfwWindowShouldClose(m_window))
	{
		// input
		glfwPollEvents();
		processInput(m_window, m_camera);
		CheckGLError("after processInput");

		float now = static_cast<float>(glfwGetTime());
		float deltaTime = now - m_lastFrame ;
		m_lastFrame = now;

		// update camera

		LibMath::Matrix4 viewMatrix = m_camera.getViewMatrix();
		LibMath::Matrix4 projectMatrix = m_camera.getProjectionMatrix();
		CheckGLError("after matrices");

		LibMath::Matrix4 VPMatrix = projectMatrix * viewMatrix;

		uploadToGPU(deltaTime);
		// render
		
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f); // Paint in blue
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draw the mesh
		//rotation += 0.0001f * deltaTime;

		sceneNode->update(LibMath::Matrix4::createRotationY(LibMath::Radian(rotation)));
		CheckGLError("after Update");

		m_graph.drawAll(VPMatrix);
		CheckGLError("after DrawAll");


		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)

		glfwSwapBuffers(m_window);
		CheckGLError("after swapBuffers");


	}
	// Delete used ressources
	m_graph.clearNodes();
	m_ressourceManager.freeRessources();
	glDeleteVertexArrays(1, &skyboxVAO);
	glDeleteBuffers(1, &skyboxVBO);

	glfwDestroyWindow(m_window);
	glfwTerminate();
	//delete m_window;

	return 0;
}



// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly

void Application::processInput(GLFWwindow* window, Camera& camera)
{
	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_window, true);

	float velocity = camera.m_moveSpeed;
	if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
		camera.m_position += camera.m_front * velocity;
	if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
		camera.m_position -= camera.m_front * velocity;
	if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
		camera.m_position -= camera.m_right * velocity;
	if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
		camera.m_position += camera.m_right * velocity; 
	if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera.m_position += camera.m_worldUp * velocity;
	if (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		camera.m_position -= camera.m_worldUp * velocity;

	double xpos, ypos;
	glfwGetCursorPos(m_window, &xpos, &ypos);
	if (camera.m_firstMouse) {
		camera.m_lastX = static_cast<float>(xpos);
		camera.m_lastY = static_cast<float>(ypos);
		camera.m_firstMouse = false;
	}
	float xoffset = static_cast<float>(xpos) - camera.m_lastX;
	float yoffset = camera.m_lastY - static_cast<float>(ypos);
	camera.m_lastX = static_cast<float>(xpos);
	camera.m_lastY = static_cast<float>(ypos);

	xoffset *= camera.m_mouseSensitivity;
	yoffset *= camera.m_mouseSensitivity;

	camera.m_yaw += LibMath::Degree(xoffset);
	camera.m_pitch += LibMath::Degree(yoffset);

	camera.updateCameraVectors();
	camera.m_viewMatrix = camera.lookAt(camera.m_position, camera.m_position + camera.m_front, camera.m_up);
}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}
