#pragma once

#include "Combo/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Combo
{
    class OpenGLContext : public GraphicsContext
    {
        public:
            OpenGLContext(GLFWwindow* window);

            virtual void Init() override;
            virtual void SwapBuffers() override;
        private:
            GLFWwindow* m_WindowHandler;

    };
}