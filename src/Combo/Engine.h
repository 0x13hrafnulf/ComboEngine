#pragma once

#include "WindowBase.h"

namespace Combo
{
   
   class Engine
   {
       public:

       Engine();
       virtual ~Engine() = default;

       void Run();

       Window& GetWindow() {return *m_Window; }
       bool IsRunning() { return m_Running; }

       static Engine& Get() { return s_Instance; }

       private:
       bool m_Running = true;
       std::unique_ptr<Window> m_Window;
       
       
       
       
       static Engine s_Instance;
   };

    Engine* CreateApplication();

}

