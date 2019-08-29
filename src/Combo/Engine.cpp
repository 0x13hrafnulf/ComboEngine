#include "combopch.h"

#include "Engine.h"
#include "LogManager.h"
#include "InputManager/EventManager.h"

namespace Combo
{
    //Need to find a lambda way to do it
    #define BIND_FN(x) std::bind(&Engine::x, this, std::placeholders::_1)

    Engine::Engine()
    {
        m_Window = std::unique_ptr<Window>(Window::CreateWindow());
        m_Window->SetEventCallback(BIND_FN(OnEvent));
    }

    void Engine::OnEvent(Event& event)
    {
        EventManager dispatcher(event);

        dispatcher.DispatchEvent<WindowCloseEvent>([this](WindowCloseEvent& e)
        {
            return this->WindowClose(e);
        });

    }


    void Engine::Run()
    {

        while(m_Running)
        {
            m_Window->Update();
        }

    }

    bool Engine::WindowClose(WindowCloseEvent& event)
    {
        m_Running = false;
        return true;
    }
    
    bool Engine::WindowResize(WindowResizeEvent& event)
    {
        //Change camera view after resizing
        //glviewport(0,0,width, height);

        return true;
    }

}