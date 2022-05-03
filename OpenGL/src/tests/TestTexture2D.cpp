#include "TestTexture2D.h"

#include<imgui/imgui.h>
#include<glm/gtc/matrix_transform.hpp>

namespace test {

	TestTexture2D::TestTexture2D()
	{
		float vertexdata[] = {
			//vertexCoords            //UVCoords     
			-100.0, -100.0,  0.0f,    0.0f, 0.0f,
			+100.0, -100.0,  0.0f,    1.0f, 0.0f,
			+100.0, +100.0,  0.0f,    1.0f, 1.0f,
			-100.0, +100.0,  0.0f,    0.0f, 1.0f
		};

		unsigned int indices[] = {
			0, 1, 2,
			0, 3, 2
		};

		proj = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, 0.0f, 1.0f);
		view = glm::mat4(1.0f);
	
		va = std::make_unique<VertexArray>();
		vb = std::make_unique<VertexBuffer>(vertexdata, 4 * 5 * sizeof(float));
		ib = std::make_unique<IndexBuffer>(indices, 6);
		layout.Push<float>(3);
		layout.Push<float>(2);
		va->AddBuffer(*vb, layout);

		shader = std::make_unique<Shader>("res/Shaders/SimpleTexture2D.shader");
		texture = std::make_unique<Texture>("res/Textures/xyz.bmp");
		texture->Bind();
	}

	TestTexture2D::~TestTexture2D()
	{
	}

	void TestTexture2D::OnUpdate(float deltatime)
	{
	}

	void TestTexture2D::OnRender()
	{
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		model = glm::translate(glm::mat4(1.0f), translate);
		glm::mat4 MVP = proj * view * model;
		shader->Bind();
		shader->SetUniformMat4("MVP", MVP);
		shader->SetUniform1i("Texture", 0);
		renderer.draw(*va, *ib, *shader);
		GLCall(glDisable(GL_BLEND));
	}

	void TestTexture2D::OnImGui()
	{
		ImGui::SliderFloat("TranslateX", &translate[0], 0, 640);
		ImGui::SliderFloat("TranslateY", &translate[1], 0, 480);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	}
}