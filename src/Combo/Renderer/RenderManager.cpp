#include "combopch.h"
#include "RenderManager.h"

#include "../OpenGL/OpenGLShader.h"

namespace Combo
{
    RenderManager::SceneData* RenderManager::s_SceneData = new RenderManager::SceneData;
    void RenderManager::Init()
    {
        RenderCommand::Init();
    }
    void RenderManager::BeginScene(OrthographicCamera& camera)
    {
        s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }
    void RenderManager::EndScene()
    {

    }
    void RenderManager::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f))
    {
        shader->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

        vertexArray->Bind();

        RenderCommand::DrawIndexed(vertexArray);
    }
}