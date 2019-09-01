#pragma once

#include "Event.h"

namespace Combo
{
    class WindowResizeEvent : public Event
    {
        public:
            WindowResizeEvent(unsigned int width, unsigned int height)
            : m_Width(width), m_Height(height)
            {

            }

            inline unsigned int GetWidth() const { return m_Width; }
            inline unsigned int GetHeight() const { return m_Height; }
            
            std::string ToString() const override
            {
                std::stringstream ss;
                ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
                return ss.str();
            }



            static EventType GetStaticEventType() { return EventType::WINDOW_Resize; }
            virtual EventType GetEventType() const override { return GetStaticEventType(); }
            virtual const char* GetEventName() const override { return "WINDOW_Resize";}

            virtual int GetEventCategory() const override { return WINDOW_EventCategory; }


        private:
            
            unsigned int m_Width, m_Height;

    };
    class WindowCloseEvent : public Event
    {
        public:
            WindowCloseEvent(){}

             std::string ToString() const override
            {
                std::stringstream ss;
                ss << "WindowCloseEvent: Application is closing!";
                return ss.str();
            }

            static EventType GetStaticEventType() { return EventType::WINDOW_Close; }
            virtual EventType GetEventType() const override { return GetStaticEventType(); }
            virtual const char* GetEventName() const override { return "WINDOW_Close";}

            virtual int GetEventCategory() const override { return WINDOW_EventCategory; }

    };
}