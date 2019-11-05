#include <Combo/Combo.h>
//**********************ENTRY POINT**********************
#include <Combo/EntryPoint.h>
//*******************************************************
#include "ApplicationLayer.h"

class Application : public Combo::Engine
{
    public:

    Application()
    {
        PushLayer(new ApplicationLayer());
    }
    ~Application()
    {

    }
};

Combo::Engine* Combo::CreateApplication()
{
    return new Application();
}