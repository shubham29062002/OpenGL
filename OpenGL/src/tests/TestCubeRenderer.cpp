#include "TestCubeRenderer.h"

#include<imgui/imgui.h>
#include<glm/gtc/matrix_transform.hpp>

namespace test {
	test::TestCubeRenderer::TestCubeRenderer()
	{
		float vertexdata[] = {
			//VertexCoords       //ColorData
			-1.0f, -1.0f, -1.0f,  (float)rand() / float(RAND_MAX), (float)rand() / float(RAND_MAX), (float)rand() / float(RAND_MAX),
			-1.0f,  1.0f, -1.0f,  (float)rand() / float(RAND_MAX), (float)rand() / float(RAND_MAX), (float)rand() / float(RAND_MAX),
			 1.0f,  1.0f, -1.0f,  (float)rand() / float(RAND_MAX), (float)rand() / float(RAND_MAX), (float)rand() / float(RAND_MAX),
			 1.0f, -1.0f, -1.0f,  (float)rand() / float(RAND_MAX), (float)rand() / float(RAND_MAX), (float)rand() / float(RAND_MAX),
			-1.0f, -1.0f,  1.0f,  (float)rand() / float(RAND_MAX), (float)rand() / float(RAND_MAX), (float)rand() / float(RAND_MAX),
			-1.0f,  1.0f,  1.0f,  (float)rand() / float(RAND_MAX), (float)rand() / float(RAND_MAX), (float)rand() / float(RAND_MAX),
			 1.0f,  1.0f,  1.0f,  (float)rand() / float(RAND_MAX), (float)rand() / float(RAND_MAX), (float)rand() / float(RAND_MAX),
			 1.0f, -1.0f,  1.0f,  (float)rand() / float(RAND_MAX), (float)rand() / float(RAND_MAX), (float)rand() / float(RAND_MAX),

		};

		unsigned int indices[] = {
			0,1,2,2,3,0, //bottom
			4,5,6,6,7,4, //top
			0,1,4,1,4,5, //side
			1,2,5,2,5,6, //side
			2,3,6,3,6,7, //side
			0,3,4,4,7,3  //side
		};

		proj = glm::perspective(glm::radians(90.0f),4.0f/3.0f, 0.1f, 10.0f);
		view = glm::lookAt(
			glm::vec3(5, 0, 0),
			glm::vec3(0, 0, 0),
			glm::vec3(0, 0, 1)
		);
		model = glm::scale(
			glm::mat4(1.0f),
			glm::vec3(1.0f)
		) * glm::rotate(
			glm::mat4(1.0f),
			glm::radians(0.0f),
			glm::vec3(0, 0, 1)
		);

		va = std::make_unique<VertexArray>();
		vb = std::make_unique<VertexBuffer>(vertexdata, 8 * 6 * sizeof(float));
		ib = std::make_unique<IndexBuffer>(indices, 6 * 6 );
		layout.Push<float>(3);
		layout.Push<float>(3);
		va->AddBuffer(*vb, layout);

		shader = std::make_unique<Shader>("res/Shaders/SimpleCubeRenderer.shader");
	}

	test::TestCubeRenderer::~TestCubeRenderer()
	{
	}

	void test::TestCubeRenderer::OnUpdate(float deltatime)
	{
		model = glm::scale(
			glm::mat4(1.0f),
			glm::vec3(scalefactor)
		) * glm::rotate(
			glm::mat4(1.0f),
			glm::radians(rotationX),
			glm::vec3(1, 0, 0)
		) * glm::rotate(
			glm::mat4(1.0f),
			glm::radians(rotationY),
			glm::vec3(0, 1, 0)
		) * glm::rotate(
			glm::mat4(1.0f),
			glm::radians(rotationZ),
			glm::vec3(0, 0, 1)
		);
	}

	void test::TestCubeRenderer::OnRender()
	{
		GLCall(glEnable(GL_DEPTH_TEST));
		GLCall(glDepthFunc(GL_LESS));
		glm::mat4 MVP = proj * view * model;
		shader->Bind();
		shader->SetUniformMat4("MVP", MVP);
		renderer.draw(*va, *ib, *shader);
		GLCall(glDisable(GL_DEPTH_TEST));
	}

	void test::TestCubeRenderer::OnImGui()
	{
		ImGui::SliderFloat("Scale", &scalefactor, 0.0f, 5.0f);
		ImGui::Text("Rotation Editor");
		ImGui::SliderFloat("X Dir", &rotationX, 0.0, 360.0);
		ImGui::SliderFloat("Y Dir", &rotationY, 0.0, 360.0);
		ImGui::SliderFloat("Z Dir", &rotationZ, 0.0, 360.0);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}