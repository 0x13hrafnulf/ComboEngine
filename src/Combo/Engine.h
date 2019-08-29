#pragma once

#include "WindowBase.h"
#include "InputManager/Event.h"
#include "InputManager/WindowEvent.h"
#include "LayerStack.h"


namespace Combo
{
   
   class Engine
   {
       public:
            Engine();
            virtual ~Engine() = default;

            void Run();
            void OnEvent(Event& event);
            bool WindowClose(WindowCloseEvent& event);
            bool WindowResize(WindowResizeEvent& event);
          

            void PushLayer(Layer* layer);
            void PushOverLay(Layer* layer);


            Window& GetWindow() {return *m_Window; }
            bool IsRunning() { return m_Running; }

            static Engine& Get() { return s_Instance; }

       private:
            bool m_Running = true;
            std::unique_ptr<Window> m_Window;
            LayerStack m_LayerStack;
       
       
       
            static Engine s_Instance;
   };

    Engine* CreateApplication();

}

