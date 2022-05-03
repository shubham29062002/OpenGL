#pragma once

#include"tests/test.h"
#include<glm/glm.hpp>

#include"VertexArray.h"
#include"IndexBuffer.h"
#include"Shader.h"
#include"Texture.h"
#include"Renderer.h"

#include <memory>

namespace test {
	class TestTexture2D : public test::Test
	{
	public:
		TestTexture2D();
		~TestTexture2D();

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
		std::unique_ptr<Texture> texture;
		VertexBufferLayout layout;
		Renderer renderer;
	};
}

