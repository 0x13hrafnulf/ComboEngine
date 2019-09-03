#pragma once

#include "WindowBase.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace Combo
{  

    class GLFWWindow : public Window
    {
        public:

        GLFWWindow(const WindowAttributes& attribs);
        ~GLFWWindow();

        void Update() override;

        void SetVsync(bool enabled) override;
        bool IsVsync() const override;

        int GetWindowWidth();
        int GetWindowHeight();
        const std::string& GetWindowTitle();
        GLFWwindow* GetWindowPointer();

        
        inline unsigned int GetWindowWidth() const override { return m_Properties.Width; }
        inline unsigned int GetWindowHeight() const override { return m_Properties.Height; }
        inline void* GetNativeWindow() const { return m_Window;}
        inline void SetEventCallback(const EventCallbackFunction& callback) override { m_Properties.EventCallback = callback;};

        
        private:
        //Functions
        void Init(const WindowAttributes& attribs);
        void Shutdown();

        //Data
        GLFWwindow* m_Window;

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