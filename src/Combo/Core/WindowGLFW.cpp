#include "combopch.h"
#include "WindowGLFW.h"

#include "InputManager/WindowEvent.h"
#include "InputManager/KeyboardEvent.h"
#include "InputManager/MouseEvent.h"

#include "OpenGL/OpenGLContext.h"

namespace Combo {

    static bool s_GLFWInitialized = false;

	static void ErrorCallback(int error, const char* info)
    {
        COMBO_ERROR_LOG("GLFWError[{0}]: {1}", error, info);
    }

    Window* Window::Create(const WindowAttributes& attribs)
    {
        return new WindowGLFW(attribs);
    }

    WindowGLFW::WindowGLFW(const WindowAttributes& attribs)
    {
        Init(attribs);
    }

    WindowGLFW::~WindowGLFW()
    {
        Shutdown();
    }
    
    void WindowGLFW::Init(const WindowAttributes& attribs)
    {
        m_Properties.Width = attribs.Width;
        m_Properties.Height = attribs.Height;
        m_Properties.Title = attribs.Title;

        COMBO_INFO_LOG("Window: {0} [{1}, {2}] created", attribs.Title, attribs.Width, attribs.Height);


        // Setup GLFW
        if(!s_GLFWInitialized)
        {
            int success = glfwInit();
            if(!success) 
            {
                COMBO_ERROR_LOG("GLFW initialization failed!");
                glfwSetErrorCallback(ErrorCallback);
            }
            s_GLFWInitialized = true;
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Create window with graphics context
        m_Window = glfwCreateWindow((int)attribs.Width, (int)attribs.Height, attribs.Title.c_str(), nullptr, nullptr);
		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();
		glfwSetWindowUserPointer(m_Window, &m_Properties);		
        SetVsync(true);
		
        //Create glfw callbacks
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowProperties& data = *(WindowProperties*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowProperties& data = *(WindowProperties*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowProperties& data = *(WindowProperties*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
		{
			WindowProperties& data = *(WindowProperties*)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(keycode);
			data.EventCallback(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowProperties& data = *(WindowProperties*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowProperties& data = *(WindowProperties*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowProperties& data = *(WindowProperties*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});



        
    }
    
    void WindowGLFW::Update()
    {
       glfwPollEvents();
       m_Context->SwapBuffers();
    }
    
    
    void WindowGLFW::Shutdown()
    {
        glfwDestroyWindow(m_Window);
    }

    void WindowGLFW::SetVsync(bool enabled)
    {
        if(enabled) glfwSwapInterval(1);
        else glfwSwapInterval(0);

        m_Properties.Vsync = enabled;
    }

    bool WindowGLFW::IsVsync() const
    {
        return m_Properties.Vsync;
    }

    
}
