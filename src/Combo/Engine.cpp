#include "Engine.h"
#include "LogManager.h"


namespace Combo
{

    Engine::Engine()
    {
        m_Window = std::unique_ptr<Window>(Window::CreateWindow());
    }


    void Engine::Run()
    {

        while(m_Running)
        {
            m_Window->Update();
        }

    }

}