#include "combopch.h"
#include "GLFWWindow.h"

#include "InputManager/WindowEvent.h"
#include "InputManager/KeyboardEvent.h"
#include "InputManager/MouseEvent.h"

namespace Combo {

    static bool s_GLFWInitialized = false;

	static void ErrorCallback(int error, const char* info)
    {
        COMBO_ERROR_LOG("GLFWError[{0}]: {1}", error, info);
    }

    Window* Window::CreateWindow(const WindowAttributes& attribs)
    {
        return new GLFWWindow(attribs);
    }

    GLFWWindow::GLFWWindow(const WindowAttributes& attribs)
    {
        Init(attribs);
    }

    GLFWWindow::~GLFWWindow()
    {
        Shutdown();
    }
    
    void GLFWWindow::Init(const WindowAttributes& attribs)
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
        glfwMakeContextCurrent(m_Window);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		glfwSetWindowUserPointer(m_Window, &m_Properties);
        if(!status)
        {
            COMBO_ERROR_LOG("Failed to initialize GLAD!");
            exit(1);
        }
        COMBO_INFO_LOG("   Vendor: {0}", glGetString(GL_VENDOR));
        COMBO_INFO_LOG("   Renderer: {0}", glGetString(GL_RENDERER));
        COMBO_INFO_LOG("   Version: {0}", glGetString(GL_VERSION));
		
				
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
    
    void GLFWWindow::Update()
    {
       glfwPollEvents();
       glfwSwapBuffers(m_Window);
    }
    
    
    void GLFWWindow::Shutdown()
    {
        glfwDestroyWindow(m_Window);
    }

    void GLFWWindow::SetVsync(bool enabled)
    {
        if(enabled) glfwSwapInterval(1);
        else glfwSwapInterval(0);

        m_Properties.Vsync = enabled;
    }

    bool GLFWWindow::IsVsync() const
    {
        return m_Properties.Vsync;
    }

    
}
