#ifndef SDL_HANDLER_H
#define SDL_HANDLER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include "imgui/imgui.h"
#include <string>
#include "Attributes.h"

class SDL_handler{

private:
    SDL_Window* m_window;
    SDL_GLContext m_context;

public:

    IMGUI_IMPL_API bool     ImGui_ImplSDL2_InitForOpenGL(SDL_Window* window, void* sdl_gl_context);
    IMGUI_IMPL_API void     ImGui_ImplSDL2_Shutdown();
    IMGUI_IMPL_API void     ImGui_ImplSDL2_NewFrame(SDL_Window* window);
    IMGUI_IMPL_API bool     ImGui_ImplSDL2_ProcessEvent(const SDL_Event* event);

    SDL_handler(const std::string& title, Attributes* attributes);
    ~SDL_handler();

    void SwapWindow();



    SDL_Window* GetSDLWindow()
    {
        return m_window;
    }
};

#endif