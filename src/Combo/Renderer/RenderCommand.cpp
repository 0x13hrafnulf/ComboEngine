#include "combopch.h"
#include "RenderCommand.h"

#include "../OpenGL/OpenGLRenderer.h"

namespace Combo
{
    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRenderer();
}