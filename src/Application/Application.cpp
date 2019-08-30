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
            CLIENT_INFO_LOG("Sandbox::Update");
        }
        void OnEvent(Combo::Event& event) override
        {
            CLIENT_TRACE_LOG("{0}", event);
        }
};


class Application : public Combo::Engine
{
    public:

    Application()
    {
        PushLayer(new SandboxLayer());
    }
    ~Application()
    {

    }
};

Combo::Engine* Combo::CreateApplication()
{
    return new Application();
}