#include "TestClearColour.h"
#include "GL/glew.h"
#include "Renderer.h"
#include "imgui/imgui.h"

namespace test {
	TestClearColour::TestClearColour()
		:m_ClearColour{0.2f, 0.3f, 0.8f, 1.0f}
	{
	}
	TestClearColour::~TestClearColour()
	{
	}
	void TestClearColour::OnUpdate(float deltatime)
	{
	}
	void TestClearColour::OnRender()
	{
		GLCall(glClearColor(m_ClearColour[0], m_ClearColour[1], m_ClearColour[2], m_ClearColour[3]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}
	void TestClearColour::OnImGui()
	{
		ImGui::ColorEdit4("Clear Colour", &m_ClearColour[0]);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}