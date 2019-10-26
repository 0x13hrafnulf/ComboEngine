#pragma once

#include "WindowBase.h"
#include "InputManager/Event.h"
#include "InputManager/WindowEvent.h"
#include "LayerStack.h"
#include "UI/ImGuiLayer.h"
#include "Timestep.h"

namespace Combo
{
   
   class Engine
   {
       public:
            Engine();
            virtual ~Engine() = default;

            void Run();
            void OnEvent(Event& event);

            void PushLayer(Layer* layer);
            void PushOverLay(Layer* layer);


            inline Window& GetWindow() {return *m_Window; }
            inline bool IsRunning() { return m_Running; }

            inline static Engine& Get() { return *s_Instance; }

       private:
            bool WindowClose(WindowCloseEvent& event);
            bool WindowResize(WindowResizeEvent& event);

            bool m_Running = true;
            bool m_Minimized = false;
            std::unique_ptr<Window> m_Window;
            LayerStack m_LayerStack;
            ImGuiLayer* m_ImGuiLayer;   
            Timestep m_LastFrame = 0.0f;
       
            static Engine* s_Instance;
   };

    Engine* CreateApplication();

}

