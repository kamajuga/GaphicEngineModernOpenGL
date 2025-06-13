#ifndef __gl_h_
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#endif // !__gl_h_
#include <iostream>
#include <filesystem>
#include <fstream>
#include <fstream>
#include <sstream>



#include "pch.h"
#include "LibMath/Angle.h"
#include "Model.h"
#include "Mesh.h"
#include "Application.h"
#include "Camera.h"
#include "Shader.h"
#include "Light.h"
#include "Texture.h"
#include "memoryLeak.h"


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);

	{
		int run = 0;
		Application app;

		app.m_ressourceManager.create<Shader>("shaders");
		app.m_ressourceManager.create<Model>("model");
		app.m_ressourceManager.create<Model>("ground");

		run = app.windowLoop();
		return run;
	}
	
}



