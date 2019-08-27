#pragma once

#include "combopch.h"
#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "LogManager.h"
#include "WindowBase.h"

namespace Combo
{  

    class SDLWindow : public Window
    {
        public:

        SDLWindow(const WindowAttributes& attribs);
        ~SDLWindow();

        void Update() override;

        void SetVsync(bool enabled) override;
        bool IsVsync() const override;

        int GetWindowWidth();
        int GetWindowHeight();
        const std::string& GetWindowTitle();
        SDL_Window* GetWindowPointer();

        
        unsigned int GetWindowWidth() const override { return m_Properties.Width; }
        unsigned int GetWindowHeight() const override { return m_Properties.Height; }
        void* GetNativeWindow() const { return m_Window;}
        
        void SetEventCallback(const EventCallbackFunction& callback) override { m_Properties.EventCallback = callback;};


        private:
        //Functions
        void Init(const WindowAttributes& attribs);
        void Shutdown();

        //Data
        SDL_Window* m_Window;
        SDL_GLContext m_Context;

        struct WindowProperties
        {
            std::string Title;
            unsigned int Width;
            unsigned int Height;
            bool Vsync;

            EventCallbackFunction EventCallback;
        };

        WindowProperties m_Properties;


    };

}