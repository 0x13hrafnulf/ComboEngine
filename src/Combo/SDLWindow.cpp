#include "SDLWindow.h"

#include "InputManager/WindowEvent.h"
#include "InputManager/KeyboardEvent.h"
#include "InputManager/MouseEvent.h"

#include "glad/glad.h"

namespace Combo {

    static bool s_SDLInitialized = false;


    Window* Window::CreateWindow(const WindowAttributes& attribs)
    {
        return new SDLWindow(attribs);
    }

    SDLWindow::SDLWindow(const WindowAttributes& attribs)
    {
        Init(attribs);
    }

    SDLWindow::~SDLWindow()
    {
        Shutdown();
    }
    
    void SDLWindow::Init(const WindowAttributes& attribs)
    {
        Uint32 flags = SDL_INIT_VIDEO;
        SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
        m_Properties.Width = attribs.Width;
        m_Properties.Height = attribs.Height;
        m_Properties.Title = attribs.Title;

        // Setup SDL
        if (!s_SDLInitialized)
        {
            int init = SDL_Init(flags);
            if(init != 0) 
            {
                COMBO_ERROR_LOG(SDL_GetError());
            }
            s_SDLInitialized = true;
        }
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

        // Create window with graphics context
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

        m_Window = SDL_CreateWindow(m_Properties.Title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,  (int)m_Properties.Width, (int)m_Properties.Height, window_flags);

        if(m_Window == nullptr)
        {
            COMBO_ERROR_LOG(SDL_GetError());
            SDL_Quit();
        }

        m_Context = SDL_GL_CreateContext(m_Window);

        if(m_Context == nullptr)
        {
            COMBO_ERROR_LOG(SDL_GetError());
            exit(1);
        }

        int status = gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

        if(!status)
        {
            COMBO_ERROR_LOG("Failed to initialize GLAD!");
            exit(1);
        }

        COMBO_INFO_LOG("   Vendor: {0}", glGetString(GL_VENDOR));
        COMBO_INFO_LOG("   Renderer: {0}", glGetString(GL_RENDERER));
        COMBO_INFO_LOG("   Version: {0}", glGetString(GL_VERSION));

        

        SetVsync(true);

        //Close Window callback
        //SDL_AddEventWatch(WindowCloseFilter, &m_Properties);
        

        glClearColor(0.0f,0.0f,1.0f,1.0f);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


        
    }
    
    void SDLWindow::Update()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                WindowCloseFilter(&m_Properties, &event);
                COMBO_INFO_LOG("Closing!");
                break;
            case SDL_WINDOWEVENT:
                WindowEventFilter(&m_Properties, &event);
                COMBO_TRACE_LOG("WINDOW EVENT!");
            case SDL_MOUSEMOTION:
                MouseMovedEventFilter(&m_Properties, &event);
                break;
            case SDL_MOUSEWHEEL:
                MouseScrolledEventFilter(&m_Properties, &event);
                break;
            case SDL_MOUSEBUTTONDOWN:
                MouseButtonDownEventFilter(&m_Properties, &event);
                break;
            case SDL_MOUSEBUTTONUP:
                MouseButtonUpEventFilter(&m_Properties, &event);
                break;
            case SDL_KEYDOWN:
                KeyDownEventFilter(&m_Properties, &event);
                break;
            case SDL_KEYUP:
                KeyUpEventFilter(&m_Properties, &event);
                break;
            }
        }
        SDL_GL_SwapWindow(m_Window);
    }
    
    
    void SDLWindow::Shutdown()
    {
        SDL_GL_DeleteContext(m_Context);
        SDL_DestroyWindow(m_Window);
        SDL_Quit();
    }

    void SDLWindow::SetVsync(bool enabled)
    {
        if(enabled) SDL_GL_SetSwapInterval(1);
        else SDL_GL_SetSwapInterval(0);

        m_Properties.Vsync = enabled;
    }

    bool SDLWindow::IsVsync() const
    {
        return m_Properties.Vsync;
    }

    int SDLWindow::WindowCloseFilter(void* data, SDL_Event* e)
    {
        WindowProperties& properties = *(WindowProperties*)data;
        WindowCloseEvent event;

        properties.EventCallback(event);
        return 0;
    }

    int SDLWindow::WindowEventFilter(void* data, SDL_Event* e)
    {
        
        WindowProperties& properties = *(WindowProperties*)data;
        properties.Width = e->window.data1;
        properties.Height = e->window.data2;
        
        WindowResizeEvent event(properties.Width, properties.Height);

        properties.EventCallback(event);
        return 0;
    }
    int SDLWindow::KeyDownEventFilter(void* data, SDL_Event* e)
    {
        WindowProperties& properties = *(WindowProperties*)data;

        int key = e->key.keysym.sym;
        int count = e->key.repeat;
        KeyPressedEvent event(key, count);
        properties.EventCallback(event);

        return 0;

    }
    int SDLWindow::KeyUpEventFilter(void* data, SDL_Event* e)
    {
        WindowProperties& properties = *(WindowProperties*)data;

        int key = e->key.keysym.sym;
        KeyReleasedEvent event(key);
        properties.EventCallback(event);

        return 0;

    }

    int SDLWindow::MouseMovedEventFilter(void* data, SDL_Event* e)
    {
        WindowProperties& properties = *(WindowProperties*)data;

        float xPos = e->motion.x;
        float yPos = e->motion.y;
            
        MouseMovedEvent event(xPos, yPos);

        properties.EventCallback(event);
        return 0;
    }
    int SDLWindow::MouseScrolledEventFilter(void* data, SDL_Event* e)
    {
        WindowProperties& properties = *(WindowProperties*)data;
       
        float xOffset = e->wheel.x;
        float yOffset = e->wheel.y;
        
        MouseScrolledEvent event(properties.Width, properties.Height);

        properties.EventCallback(event);
        return 0;
    }
    int SDLWindow::MouseButtonDownEventFilter(void* data, SDL_Event* e)
    {
        WindowProperties& properties = *(WindowProperties*)data;
       
        //float xPos = e->button.x;
        //float yPos = e->button.y;
        int key = e->button.button;
        MouseButtonPressedEvent event(key);
        properties.EventCallback(event);

        return 0;
    }
    int SDLWindow::MouseButtonUpEventFilter(void* data, SDL_Event* e)
    {
        WindowProperties& properties = *(WindowProperties*)data;
       
        //float xPos = e->button.x;
        //float yPos = e->button.y;
        int key = e->button.button;
        MouseButtonReleasedEvent event(key);
        properties.EventCallback(event);

        return 0;
    }
    int SDLWindow::KeyboardTextInputEventFilter(void* data, SDL_Event* e)
    {
       return 0;
    }
    int SDLWindow::KeyboardTextEditEventFilter(void* data, SDL_Event* e)
    {
       return 0;

    }
}
