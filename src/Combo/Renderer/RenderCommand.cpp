#include "Combo/combopch.h"
#include "RenderCommand.h"


namespace Combo
{
    std::unique_ptr<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}