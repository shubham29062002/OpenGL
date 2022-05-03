#include "TestQuadRenderer.h"

#include<imgui/imgui.h>
#include<glm/gtc/matrix_transform.hpp>

namespace test {

	TestQuadRenderer::TestQuadRenderer()
	{
		float vertexdata[] = {
			//vertexCoords            //colorData
			-100.0, -100.0,  0.0f,    1.0f, 1.0f, 0.0f,
			+100.0, -100.0,  0.0f,    1.0f, 0.0f, 1.0f,
			+100.0, +100.0,  0.0f,    0.0f, 0.0f, 1.0f,
			-100.0, +100.0,  0.0f,    0.0f, 1.0f, 1.0f
		};

		unsigned int indices[] = {
			0, 1, 2,
			0, 3, 2
		};

		proj = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, 0.0f, 1.0f);
		view = glm::mat4(1.0f);
	
		va = std::make_unique<VertexArray>();
		vb = std::make_unique<VertexBuffer>(vertexdata, 4 * 6 * sizeof(float));
		ib = std::make_unique<IndexBuffer>(indices, 6);
		layout.Push<float>(3);
		layout.Push<float>(3);
		va->AddBuffer(*vb, layout);

		shader = std::make_unique<Shader>("res/Shaders/SimpleColour.shader");
	}

	TestQuadRenderer::~TestQuadRenderer()
	{
	}

	void TestQuadRenderer::OnUpdate(float deltatime)
	{
	}

	void TestQuadRenderer::OnRender()
	{
		model = glm::translate(glm::mat4(1.0f), translate);
		glm::mat4 MVP = proj * view * model;
		glm::mat4 test = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, 0.0f, 1.0f);
		shader->Bind();
		shader->SetUniformMat4("MVP", MVP);
		renderer.draw(*va, *ib, *shader);
	}

	void TestQuadRenderer::OnImGui()
	{
		ImGui::SliderFloat("TranslateX", &translate[0], 0, 640);
		ImGui::SliderFloat("TranslateY", &translate[1], 0, 480);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}