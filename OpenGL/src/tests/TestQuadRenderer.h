#pragma once

#include"tests/test.h"
#include<glm/glm.hpp>

#include"VertexArray.h"
#include"IndexBuffer.h"
#include"Shader.h"
#include"Renderer.h"

#include <memory>

namespace test {
	class TestQuadRenderer : public test::Test
	{
	public:
		TestQuadRenderer();
		~TestQuadRenderer();

		void OnUpdate(float deltatime) override;
		void OnRender() override;
		void OnImGui() override;
	
	private:
		glm::vec3 translate;
		glm::mat4 proj, view, model;
		std::unique_ptr<VertexArray> va;
		std::unique_ptr<VertexBuffer> vb;
		std::unique_ptr<IndexBuffer> ib;
		std::unique_ptr<Shader> shader;
		VertexBufferLayout layout;
		Renderer renderer;
	};
}

