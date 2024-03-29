	#pragma once

#include "RenderCommand.h"
#include "Shader.h"
#include "OrthographicCamera.h"

namespace Combo
{
    class RenderManager
    {
        public:
            static void Init();
            static void Shutdown();
            static void WindowResize(uint32_t width, uint32_t height);
            static void BeginScene(OrthographicCamera& camera);
            static void EndScene();

            static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

            inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
        private:
            struct SceneData
		    {
			    glm::mat4 ViewProjectionMatrix;
		    };

		    static std::unique_ptr<SceneData> s_SceneData;
    };        
}