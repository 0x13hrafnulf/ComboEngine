#include "Combo/combopch.h"
#include "RenderManager.h"
#include "Renderer2D.h"

#include "Combo/OpenGL/OpenGLShader.h"

namespace Combo
{
    std::unique_ptr<RenderManager::SceneData> RenderManager::s_SceneData = std::make_unique<RenderManager::SceneData>();

    void RenderManager::Init()
    {
        RenderCommand::Init();
        Renderer2D::Init();
    }
    void RenderManager::Shutdown()
    {
        Renderer2D::Shutdown();
    }
    void RenderManager::BeginScene(OrthographicCamera& camera)
    {
        s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }
      void RenderManager::WindowResize(uint32_t width, uint32_t height)
    {
        RenderCommand::SetViewport(0, 0, width, height);
    }
    void RenderManager::EndScene()
    {

    }
    void RenderManager::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
    {
        shader->Bind();
        shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		shader->SetMat4("u_Transform", transform);

        vertexArray->Bind();

        RenderCommand::DrawIndexed(vertexArray);
    }
}