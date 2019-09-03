#pragma once

#include "../Layer.h"

#include <SDL2/SDL.h>


namespace Combo
{
    class ImGuiLayer : public Layer
    {
        public:
            ImGuiLayer();
            ~ImGuiLayer() = default;

            virtual void Attach() override;
            virtual void Detach() override;
            virtual void ImGuiRender() override;
            


            void Start();
            void Stop();
        private:
            SDL_Window* m_Window;
            SDL_GLContext m_Context; 
    };

} 
