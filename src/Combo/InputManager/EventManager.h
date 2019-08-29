#pragma once

#include "Event.h"
#include "combopch.h"

namespace Combo
{

    class EventManager//To be modified as Singleton to manage all events as the system
    {

        public:
            EventManager(Event& event) : 
                m_Event(event)
            {
            }

            template<typename T>
            bool DispatchEvent(std::function<bool(T&)> func)//
            {
                if(m_Event.GetEventType() == T::GetStaticEventType())
                {
                    m_Event.Handled = func(*(T*)&m_Event);//Takes address of event -> casts it to specified "T" pointer ->
                                                            //then dereferences it to fit std::function<bool(T&)>, which takes reference to T
                    return true;
                }
                return false;
            }

        private:
            Event& m_Event;

    };
 
}