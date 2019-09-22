#pragma once

#include "RendererAPI.h"


namespace Combo
{
    class RenderCommand
    {
        public:
            inline static void Init()
            {
                s_RendererAPI->Init();
            }
            inline void SetClearColor(const glm::vec4& color)
            {
                s_RendererAPI->SetClearColor(color);
            }
            inline void Clear()
            {
                s_RendererAPI->Clear();
            }
            inline void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
            {
                s_RendererAPI->DrawIndexed(vertexArray);
            }
        private:
            static RendererAPI* s_RendererAPI;

    };
}