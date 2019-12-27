#include "Combo/combopch.h"

#include "GraphicsContext.h"
#include "Renderer.h"
#include "OpenGL/OpenGLContext.h"

namespace Combo {

	std::unique_ptr<GraphicsContext> GraphicsContext::Create(void* window)
	{
        switch(RenderManager::GetAPI())
        {
            case RendererAPI::API::NONE: COMBO_ERROR_LOG("RendererAPI is not supported!"); return nullptr;
            case RendererAPI::API::OpenGL: return std::make_unique<OpenGLContext>(static_cast<GLFWwindow*>(window))
            default: COMBO_ERROR_LOG("Unknown RenderAPI!"); return nullptr;
        }
        COMBO_ERROR_LOG("Unknown RenderAPI!");
        return nullptr;
    }

} 