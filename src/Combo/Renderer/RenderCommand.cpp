#include "combopch.h"
#include "RenderCommand.h"

#include "../OpenGL/OpenGLRenderer.h"

namespace Combo
{
    std::unique_ptr<RendererAPI> RenderCommand::s_RendererAPI = std::make_unique<OpenGLRenderer>();
}