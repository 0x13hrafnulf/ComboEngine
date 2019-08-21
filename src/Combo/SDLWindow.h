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
        virtual ~SDLWindow();

        void Update() override;

        void SetVsync(bool enabled) override;
        bool IsVsync() const override;

        int GetWindowWidth();
        int GetWindowHeight();
        const std::string& GetWindowTitle();
        SDL_Window* GetWindowPointer();

        
        unsigned int GetWindowWidth() const override { return m_Properties.Width; }
        unsigned int GetWindowHeight() const override { return m_Properties.Height; }
        virtual void* GetNativeWindow() const { return m_Window;}
        
        /*
        void SetEventCallback(const EventCallbackFn& callback) = 0;
        void SetVsync(bool enabled) = 0;
        bool IsVsync() = 0;
         */ 
        


        private:
        //Functions
        virtual void Init(const WindowAttributes& attribs);
        virtual void Shutdown();

        //Data
        SDL_Window* m_Window;
        SDL_GLContext m_Context;

        struct WindowProperties
        {
            std::string Title;
            unsigned int Width;
            unsigned int Height;
            bool Vsync;

            //EventCallbackFn EventCallback
        };

        WindowProperties m_Properties;


    };

}