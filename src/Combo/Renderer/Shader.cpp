#include "combopch.h"
#include "Shader.h"
#include "RenderManager.h"
#include "../OpenGL/OpenGLShader.h"

namespace Combo
{
    std::shared_ptr<Shader> Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch(RenderManager::GetAPI())
        {
            case RendererAPI::API::NONE: COMBO_ERROR_LOG("RendererAPI is not supported!"); return nullptr;
            case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(vertexSrc, fragmentSrc);
            default: COMBO_ERROR_LOG("Unknown RenderAPI!"); return nullptr;
        }
        COMBO_ERROR_LOG("Unknown RenderAPI!");
        return nullptr;
    }
    
}