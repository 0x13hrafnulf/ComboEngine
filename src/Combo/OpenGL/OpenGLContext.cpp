#include "Combo/combopch.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace Combo
{

    OpenGLContext::OpenGLContext(GLFWwindow* window)
    : m_WindowHandler(window)
    {
        if(!window) COMBO_ERROR_LOG("Window handling failed!");
    }

    void OpenGLContext::Init() 
    {
        glfwMakeContextCurrent(m_WindowHandler);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        if(!status)
        {
            COMBO_ERROR_LOG("Failed to initialize GLAD!");
            exit(1);
        }
        COMBO_INFO_LOG("   Vendor: {0}", glGetString(GL_VENDOR));
        COMBO_INFO_LOG("   Renderer: {0}", glGetString(GL_RENDERER));
        COMBO_INFO_LOG("   Version: {0}", glGetString(GL_VERSION));
        
    }
    void OpenGLContext::SwapBuffers() 
    {
        glfwSwapBuffers(m_WindowHandler);
    }
  
}