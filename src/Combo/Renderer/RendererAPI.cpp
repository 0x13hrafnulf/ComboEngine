#include "Combo/combopch.h"
#include "RendererAPI.h"
#include "OpenGL/OpenGLRenderer.h"

namespace Combo
{
    //Current API is OpenGL
    RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;
    std::unique_ptr<RendererAPI> RendererAPI::Create()
    {
        switch(s_API)
        {
            case RendererAPI::API::NONE: COMBO_ERROR_LOG("RendererAPI is not supported!"); return nullptr;
            case RendererAPI::API::OpenGL: return std::make_unique<OpenGLRenderer>();
            default: COMBO_ERROR_LOG("Unknown RenderAPI!"); return nullptr;
        }
        COMBO_ERROR_LOG("Unknown RenderAPI!");
        return nullptr;
        
    }
}