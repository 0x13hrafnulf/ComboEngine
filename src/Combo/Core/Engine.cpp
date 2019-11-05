#include "Combo/combopch.h"

#include "Engine.h"
#include "LogManager.h"
#include "InputManager/EventManager.h"
#include "InputManager/InputManager.h"
#include <GLFW/glfw3.h>

#include "Combo/Renderer/RenderManager.h"


namespace Combo
{

//Need to find a lambda way to do it
#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

    Engine* Engine::s_Instance = nullptr;



    Engine::Engine()
    {
        if(s_Instance)COMBO_ERROR_LOG("Application already exists!");
		s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(Engine::OnEvent));
        
        RenderManager::Init();

        m_ImGuiLayer = new ImGuiLayer();
        PushOverLay(m_ImGuiLayer);

    }

    void Engine::OnEvent(Event& e)
    {
        EventManager dispatcher(e);

		dispatcher.DispatchEvent<WindowCloseEvent>(BIND_EVENT_FN(Engine::WindowClose));
		dispatcher.DispatchEvent<WindowResizeEvent>(BIND_EVENT_FN(Engine::WindowResize));

        for(auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
        {
            (*--it)->OnEvent(e);
            if(e.Handled)
                break;
        }

    }


    void Engine::Run()
    {

        while(m_Running)
        {
            float time = (float)glfwGetTime();
            Timestep ts = time - m_LastFrame;
            m_LastFrame = time;

            if(!m_Minimized)
            {
                for(Layer* layer : m_LayerStack)
                {
                    layer->Update(ts);
                }
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
        m_LayerStack.PushOverLay(layer);
    }

    bool Engine::WindowClose(WindowCloseEvent& event)
    {
        m_Running = false;
        return true;
    }
    bool Engine::WindowResize(WindowResizeEvent& event)
    {
       if(event.GetWidth() == 0 || event.GetHeight() == 0)
       {
           m_Minimized = true;
           return false;
       }

        m_Minimized = false;
        RenderManager::WindowResize(event.GetWidth(), event.GetHeight());


       return false;
    }
}