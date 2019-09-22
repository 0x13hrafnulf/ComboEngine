#include "../combopch.h"
#include "Buffer.h"
#include "RenderManager.h"
#include "../OpenGL/OpenGLBuffer.h"

namespace Combo
{
    VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
    {
       switch(RenderManager::GetAPI())
        {
            case RendererAPI::API::NONE: COMBO_ERROR_LOG("RendererAPI is not supported!"); return nullptr;
            case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(vertices, size);
            default: COMBO_ERROR_LOG("Unknown RenderAPI!"); return nullptr;
        }
        COMBO_ERROR_LOG("Unknown RenderAPI!");
        return nullptr;
    }


    IndexBuffer* IndexBuffer::Create(float* indices, uint32_t size)
    {
        switch(RenderManager::GetAPI())
        {
            case RendererAPI::API::NONE: COMBO_ERROR_LOG("RendererAPI is not supported!"); return nullptr;
            case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indices, size);
            default: COMBO_ERROR_LOG("Unknown RenderAPI!"); return nullptr;
        }
        COMBO_ERROR_LOG("Unknown RenderAPI!");
        return nullptr;
        
    }



}