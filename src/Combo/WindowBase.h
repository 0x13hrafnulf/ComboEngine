#pragma once

#include "combopch.h"
#include "InputManager/Event.h"

namespace Combo
{
    struct WindowAttributes
    {
        WindowAttributes(const std::string& title = "Combo Engine", 
        unsigned int width = 860, 
        unsigned int height = 640)
        :Title(title),
         Width(width),
         Height(height)
        {

        }

        std::string Title;
        unsigned int Width;
        unsigned int Height;
    };
    


    class Window
    {
        public:

        using EventCallbackFunction = std::function<void(Event&)>;

        virtual ~Window() = default;

        virtual void Update() = 0;

        virtual void SetVsync(bool enabled) = 0;
        virtual bool IsVsync() const = 0;


        virtual unsigned int GetWindowWidth() const = 0;
        virtual unsigned int GetWindowHeight() const = 0;
        virtual void* GetNativeWindow() const = 0;
     
        static Window* CreateWindow(const WindowAttributes& attrib = WindowAttributes());
    

        virtual void SetEventCallback(const EventCallbackFunction& callback) = 0;

    
    
    };

}