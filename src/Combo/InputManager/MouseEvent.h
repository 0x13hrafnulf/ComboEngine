#pragma once

#include "Event.h"

namespace Combo
{
    class MouseButtonEvent : public Event
    {
        public:
            
            int GetMouseButton() const { return m_Button; }

            virtual int GetEventCategory() const override { return INPUT_EventCategory | MOUSE_EventCategory; }
        protected:
            MouseButtonEvent(int button)
            : m_Button(button)
            {

            }

            int m_Button;
    };
    
    class MouseButtonPressedEvent : public MouseButtonEvent
    {
        public:
            MouseButtonPressedEvent(int button)
            : MouseButtonEvent(button)
            {

            }

            std::string ToString() const override
            {
                std::stringstream ss;
                ss << "MouseButtonPressedEvent: " << m_Button;
                return ss.str();
            }


            static EventType GetStaticEventType() { return EventType::MOUSE_ButtonPressed; }
            virtual EventType GetEventType() const override { return GetStaticEventType(); }
            virtual const char* GetEventName() const override { return "MOUSE_ButtonPressed";}

    };
    class MouseButtonReleasedEvent : public MouseButtonEvent
    {
        public:
            MouseButtonReleasedEvent(int button)
                : MouseButtonEvent(button)
                {

                }

                std::string ToString() const override
                {
                    std::stringstream ss;
                    ss << "MouseButtonReleasedEvent: " << m_Button;
                    return ss.str();
                }


                static EventType GetStaticEventType() { return EventType::MOUSE_ButtonReleased; }
                virtual EventType GetEventType() const override { return GetStaticEventType(); }
                virtual const char* GetEventName() const override { return "MOUSE_ButtonReleased";}
    };
    class MouseScrolledEvent : public Event
    {
        public:

            MouseScrolledEvent(float x, float y)
            : m_Xoffset(x), m_Yoffset(y)
            {

            }

            float GetXOffset() const { return m_Xoffset;}
            float GetYOffset() const { return m_Yoffset;}

            std::string ToString() const override
            {
                std::stringstream ss;
                ss << "MouseMovedEvent: " << m_Xoffset << ", " << m_Yoffset;
                return ss.str();
            }


            static EventType GetStaticEventType() { return EventType::MOUSE_Scrolled; }
            virtual EventType GetEventType() const override { return GetStaticEventType(); }
            virtual const char* GetEventName() const override { return "MOUSE_Scrolled";}

            virtual int GetEventCategory() const override { return INPUT_EventCategory | MOUSE_EventCategory; }

        private:
            float m_Xoffset;
            float m_Yoffset;


    };
    class MouseMovedEvent : public Event
    {
        public:
            MouseMovedEvent(float x, float y)
            : m_X(x), m_Y(y)
            {

            }
            float GetX() const {return m_X;}
            float GetY() const {return m_Y;}

            std::string ToString() const override
            {
                std::stringstream ss;
                ss << "MouseMovedEvent: " << m_X << ", " << m_Y;
                return ss.str();
            }

            static EventType GetStaticEventType() { return EventType::MOUSE_Moved; }
            virtual EventType GetEventType() const override { return GetStaticEventType(); }
            virtual const char* GetEventName() const override { return "MOUSE_Moved";}

            virtual int GetEventCategory() const override { return INPUT_EventCategory | MOUSE_EventCategory; }

        private:
            float m_X;
            float m_Y;
    };
}