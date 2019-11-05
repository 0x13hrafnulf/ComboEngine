#pragma once

#include "Combo/Core/Layer.h"



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
    };

} 
