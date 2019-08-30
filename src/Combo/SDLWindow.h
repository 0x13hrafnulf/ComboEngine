#pragma once

#include "combopch.h"
#include <SDL2/SDL.h>

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

         //Event Filters
        int WindowCloseFilter(void* data, SDL_Event* e);
        int WindowEventFilter(void* data, SDL_Event* e);
        int KeyDownEventFilter(void* data, SDL_Event* e);
        int KeyUpEventFilter(void* data, SDL_Event* e);
        int KeyboardTextInputEventFilter(void* data, SDL_Event* e);
        int KeyboardTextEditEventFilter(void* data, SDL_Event* e);
        int MouseMovedEventFilter(void* data, SDL_Event* e);
        int MouseScrolledEventFilter(void* data, SDL_Event* e);
        int MouseButtonUpEventFilter(void* data, SDL_Event* e);
        int MouseButtonDownEventFilter(void* data, SDL_Event* e);

        
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