#include"Renderer.h"

//Renderer::Renderer()
//{
//}

//Renderer::~Renderer()
//{
//}

void Renderer::clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT));
}

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
