#ifndef COMBO_SDLWINDOW_H
#define COMBO_SDLWINDOW_H

#include "../combopch.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>

class SDLWindow
{
    public:

    SDLWindow();
    ~SDLWindow();

    void CreateWindow(int width, int height, const std::string& title);
    void DestroyWindow();
    void SwapBuffers();


    int GetWindowWidth();
    int GetWindowHeight();
    const std::string& GetWindowTitle();
    SDL_Window* GetWindowPointer();

    
    
    
    private:
    SDL_Window* m_window;
    int m_width; 
    int m_height;
    std::string m_title;

};


#endif