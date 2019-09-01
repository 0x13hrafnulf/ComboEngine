#pragma once

#include "Event.h"
#include "InputCodes.h"

namespace Combo
{
    class KeyboardEvent : public Event
    {
        public:
            inline int GetKey() const { return m_Key; }

            virtual int GetEventCategory() const override { return INPUT_EventCategory | KEYBOARD_EventCategory; }

        protected:

            KeyboardEvent(int key)
            : m_Key(key)
            {

            }
            int m_Key;

    };

    class KeyPressedEvent : public KeyboardEvent
    {
        public:
            KeyPressedEvent(int key, int count)
            : KeyboardEvent(key), m_RepeatCount(count)
            {

            }

            inline int GetRepeatCount() const { return m_RepeatCount; }

            std::string ToString() const override
            {
                std::stringstream ss;
                ss << "KeyPressedEvent: " << m_Key << " [" << m_RepeatCount << " times]";
                return ss.str();
            }


            static EventType GetStaticEventType() { return EventType::KEY_Pressed; }
            virtual EventType GetEventType() const override { return GetStaticEventType(); }
            virtual const char* GetEventName() const override { return "KEY_Pressed";}

        private:

            int m_RepeatCount;
    };
    class KeyReleasedEvent : public KeyboardEvent
    {
         public:
            KeyReleasedEvent(int key)
            : KeyboardEvent(key)
            {

            }

            std::string ToString() const override
            {
                std::stringstream ss;
                ss << "KeyReleasedEvent: " << m_Key;
                return ss.str();
            }


            static EventType GetStaticEventType() { return EventType::KEY_Released; }
            virtual EventType GetEventType() const override { return GetStaticEventType(); }
            virtual const char* GetEventName() const override { return "KEY_Released";}

    };
    class KeyTypedEvent : public KeyboardEvent
    {
         public:
            KeyTypedEvent(int key)
            : KeyboardEvent(key)
            {

            }

            std::string ToString() const override
            {
                std::stringstream ss;
                ss << "KeyTypedEvent: " << m_Key;
                return ss.str();
            }


            static EventType GetStaticEventType() { return EventType::KEY_Typed; }
            virtual EventType GetEventType() const override { return GetStaticEventType(); }
            virtual const char* GetEventName() const override { return "KEY_Typed";}
    };
}