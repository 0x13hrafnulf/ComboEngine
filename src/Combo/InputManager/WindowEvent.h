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

            unsigned int GetWidth() const { return m_Width; }
            unsigned int GetHeight() const { return m_Height; }


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

            static EventType GetStaticEventType() { return EventType::WINDOW_Close; }
            virtual EventType GetEventType() const override { return GetStaticEventType(); }
            virtual const char* GetEventName() const override { return "WINDOW_Close";}

            virtual int GetEventCategory() const override { return WINDOW_EventCategory; }

    };
}