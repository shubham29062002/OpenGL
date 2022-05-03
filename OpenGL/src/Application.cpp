#include<GL/glew.h>
#include <GLFW/glfw3.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"


#include<iostream>
#include<string>
#include<stdio.h>

#include"ErrorCheck.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"VertexArray.h"
#include"Shader.h"
#include"Texture.h"
#include"Renderer.h"

#include"tests/test.h"
#include"tests/TestClearColour.h"
#include"tests/TestQuadRenderer.h"
#include"tests/TestTexture2D.h"
#include"tests/TestCubeRenderer.h"

int main()
{
	if (!glfwInit())
		return -1;

	GLFWwindow* window;
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	
	if (glewInit() != GLEW_OK) {
		std::cout << "error" << std::endl;
	}

	std::cout << "Version          : " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GPU Manufacturer : " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "GPU Name         : " << glGetString(GL_RENDERER) << std::endl;

	Renderer renderer;
	
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	
	test::Test* CurrentTest = nullptr;
	test::TestMenu* testmenu = new test::TestMenu(CurrentTest);
	CurrentTest = testmenu;

	testmenu->RegisterTest<test::TestClearColour>("Clear Color");
	testmenu->RegisterTest<test::TestQuadRenderer>("Basic Quad Render");
	testmenu->RegisterTest<test::TestTexture2D>("Basic Texture 2D");
	testmenu->RegisterTest<test::TestCubeRenderer>("Basic Cube Renderer");

	while (!glfwWindowShouldClose(window))
	{	
		renderer.clear();
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		if (CurrentTest) 
		{

			CurrentTest->OnUpdate(0.0f);
			CurrentTest->OnRender();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			ImGui::Begin("Test");
			if (CurrentTest != testmenu && ImGui::Button("<-"))
			{
				delete CurrentTest;
				CurrentTest = testmenu;
			}
			CurrentTest->OnImGui();
			ImGui::End();

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}
		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	delete CurrentTest;
	if (CurrentTest != testmenu)
		delete testmenu;
	
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	
	glfwTerminate();
	return 0;
}