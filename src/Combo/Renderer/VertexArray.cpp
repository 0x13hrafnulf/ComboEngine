#include "../combopch.h"

#include "VertexArray.h"
#include "RenderManager.h"
#include "../OpenGL/OpenGLVertexArray.h"

namespace Combo
{
    VertexArray* VertexArray::Create()
    {
        switch(RenderManager::GetAPI())
        {
            case RendererAPI::API::NONE: COMBO_ERROR_LOG("RendererAPI is not supported!"); return nullptr;
            case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
            default: COMBO_ERROR_LOG("Unknown RenderAPI!"); return nullptr;
        }
        COMBO_ERROR_LOG("Unknown RenderAPI!");
        return nullptr;
    }
}