#pragma once

extern Combo::Engine* Combo::CreateApplication();

int main(int argc, char** argv)
{
    Combo::LogManager::Init(); // initialize core
    COMBO_WARN_LOG("Initialization!"); 

    auto app = Combo::CreateApplication();
    if(!app) COMBO_WARN_LOG("Failed to initialize application!"); 
    app->Run();
    delete app;
    //Shutdown core
    return 0;
}
