#include "Combo/combopch.h"

#include "VertexArray.h"
#include "RenderManager.h"
#include "Combo/OpenGL/OpenGLVertexArray.h"

namespace Combo
{
    std::shared_ptr<VertexArray>  VertexArray::Create()
    {
        switch(RenderManager::GetAPI())
        {
            case RendererAPI::API::NONE: COMBO_ERROR_LOG("RendererAPI is not supported!"); return nullptr;
            case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexArray>();
            default: COMBO_ERROR_LOG("Unknown RenderAPI!"); return nullptr;
        }
        COMBO_ERROR_LOG("Unknown RenderAPI!");
        return nullptr;
    }
}