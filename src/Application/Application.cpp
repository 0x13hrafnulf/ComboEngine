#include "Combo/Combo.h"

class Application : public Combo::Engine
{
    public:

    Application()
    {

    }
    ~Application()
    {

    }
};

Combo::Engine* Combo::CreateApplication()
{
    return new Application();
}