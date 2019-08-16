#pragma once

namespace Combo
{
   
   class Engine
   {
       public:

       Engine();
       virtual ~Engine() = default;

       void Run();
       int Init();
       int Shutdown();

       private:
       
       static Engine s_Instance;

   };

    Engine* CreateApplication();

}

