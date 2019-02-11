#include "SDLWindow.h"

SDLWindow::SDLWindow()
{

}

SDLWindow::~SDLWindow()
{
    DestroyWindow();
}


void SDLWindow::CreateWindow(int width, int height, const std::string& title)
{
    Uint32 window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_RESIZABLE;
    m_width = width;
    m_height = height;
    m_title = title;

    m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, window_flags);
}
void SDLWindow::DestroyWindow()
{
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}
void SDLWindow::SwapBuffers()
{
    SDL_GL_SwapWindow(m_window);
}

int SDLWindow::GetWindowWidth()
{
    return m_width;
}   
int SDLWindow::GetWindowHeight()
{
    return m_height;
}
const std::string& SDLWindow::GetWindowTitle()
{
    return m_title;
}
SDL_Window* SDLWindow::GetWindowPointer()
{
    return m_window;
}
