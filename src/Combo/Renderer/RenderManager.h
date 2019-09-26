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

            static void BeginScene(OrthographicCamera& camera);
            static void EndScene();

            static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform);

            inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
        private:
            struct SceneData
		    {
			    glm::mat4 ViewProjectionMatrix;
		    };

		    static SceneData* s_SceneData;
    };        
}