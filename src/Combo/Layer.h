#pragma once


#include "InputManager/Event.h"


namespace Combo
{
    class Layer
    {
        public:

            Layer(const std::string& name);
            virtual ~Layer() = default;

            virtual void Attach(){}
            virtual void Detach(){}
            virtual void Update(){}
            virtual void OnEvent(Event& event){}
            virtual void ImGuiRender() {}
            
            inline const std::string GetName() const { return m_Name; }
        protected:
            std::string m_Name;
            bool m_Enabled = true;

    };

}