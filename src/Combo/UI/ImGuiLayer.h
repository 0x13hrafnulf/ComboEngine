#pragma once

#include "Layer.h"

namespace Combo
{
    class ImGuiLayer : public Layer
    {
        public:
            ImGuiLayer();
            ~ImGuiLayer() = default;

            virtual void Attach() override;
            virtual void Detach() override;
            virtual void Update() override;
            virtual void ImGuiRender() override;
            


            void Start();
            void Shutdown();
        private:

    };

} 
