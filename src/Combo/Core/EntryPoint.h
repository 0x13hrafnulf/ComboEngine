#pragma once

extern Combo::Engine* Combo::CreateApplication();

int main(int argc, char** argv)
{
    Combo::LogManager::Init();
    COMBO_WARN_LOG("Initialization!"); 


    auto app = Combo::CreateApplication();
    app->Run();
    delete app;
    return 0;
}
