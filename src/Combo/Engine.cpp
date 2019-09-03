#include "combopch.h"

#include "Engine.h"
#include "LogManager.h"
#include "InputManager/EventManager.h"

namespace Combo
{
    Engine* Engine::s_Instance = nullptr;

    //Need to find a lambda way to do it
    #define BIND_FN(x) std::bind(&Engine::x, this, std::placeholders::_1)

    Engine::Engine()
    {
        if(s_Instance)COMBO_ERROR_LOG("Application already exists!");

        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::CreateWindow());
        m_Window->SetEventCallback(BIND_FN(OnEvent));

        m_ImGuiLayer = new ImGuiLayer();
        PushOverLay(m_ImGuiLayer);

    }

    void Engine::OnEvent(Event& event)
    {
        EventManager dispatcher(event);

        dispatcher.DispatchEvent<WindowCloseEvent>([this](WindowCloseEvent& e)
        {
            return this->WindowClose(e);
        });

        for(auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
        {
            (*--it)->OnEvent(event);
            if(event.Handled)
                break;
        }

    }


    void Engine::Run()
    {

        while(m_Running)
        {
            for(Layer* layer : m_LayerStack)
            {
                layer->Update();
            }

            m_ImGuiLayer->Start();
            for(Layer* layer : m_LayerStack)
            {
                layer->ImGuiRender();
            }
            m_ImGuiLayer->Stop();
            m_Window->Update();
        }

    }



    void Engine::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
    }
    void Engine::PushOverLay(Layer* layer)
    {
        m_LayerStack.PopLayer(layer);
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