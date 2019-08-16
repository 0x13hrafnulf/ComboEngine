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

    if(m_window == nullptr)
    {
        printf("Could not create window: %s\n", SDL_GetError());//change to std::cout
    }

    SDL_GLContext glcontext = SDL_GL_CreateContext(m_window);

    GLenum error = glewInit();

    glClearColor(0.0f,0.0f,1.0f,1.0f);

    SDL_GL_SetSwapInterval(0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
