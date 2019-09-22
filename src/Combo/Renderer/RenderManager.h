#pragma once

#include "RenderCommand.h"
#include "Shader.h"


namespace Combo
{
    class RenderManager
    {
        public:
            static void Init();

            static void BeginScene();
            static void EndScene();

            static void Submit();

            inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
        private:
            
    };        
}