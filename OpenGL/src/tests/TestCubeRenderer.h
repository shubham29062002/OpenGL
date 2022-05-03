#include"tests/test.h"
#include<glm/glm.hpp>

#include"VertexArray.h"
#include"IndexBuffer.h"
#include"Shader.h"
#include"Texture.h"
#include"Renderer.h"

#include<memory.h>

namespace test {
	class TestCubeRenderer : public test::Test {
	public:
		TestCubeRenderer();
		~TestCubeRenderer();


		void OnUpdate(float deltatime) override;
		void OnRender() override;
		void OnImGui() override;

	private:
		glm::mat4 proj, view, model;
		std::unique_ptr<VertexArray> va;
		std::unique_ptr<VertexBuffer> vb;
		std::unique_ptr<IndexBuffer> ib;
		std::unique_ptr<Shader> shader;
		VertexBufferLayout layout;
		Renderer renderer;

		float scalefactor = 1.0;
		float rotationX = 0.0;
		float rotationY = 0.0;
		float rotationZ = 0.0;
	};
}