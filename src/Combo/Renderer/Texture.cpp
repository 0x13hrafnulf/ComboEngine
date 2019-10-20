#include "combopch.h"
#include "Texture.h"


#include "RenderManager.h"
#include "../OpenGL/OpenGLTexture.h"

namespace Combo
{

    std::shared_ptr<Texture2D> Texture2D::Create(const std::string& filepath)
    {
    switch(RenderManager::GetAPI())
        {
            case RendererAPI::API::NONE: COMBO_ERROR_LOG("RendererAPI is not supported!"); return nullptr;
            case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(filepath);
            default: COMBO_ERROR_LOG("Unknown RenderAPI!"); return nullptr;
        }
        COMBO_ERROR_LOG("Unknown RenderAPI!");
        return nullptr;


    }


}