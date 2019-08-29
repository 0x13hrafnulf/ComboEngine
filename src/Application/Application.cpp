#include "Combo/Combo.h"

class SandboxLayer : public Combo::Layer
{
    public:
        SandboxLayer()
            : Layer("Sandbox")
        {

        }
        void Update() override
        {
            COMBO_INFO_LOG("Sandbox::Update");
        }
        void OnEvent(Combo::Event& event) override
        {
            COMBO_TRACE_LOG("{0}", event);
        }
};


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