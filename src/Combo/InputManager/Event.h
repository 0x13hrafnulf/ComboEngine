#pragma once

#define BIT(x) (1 << x)

namespace Combo
{

    enum class EventType
    {
        None = 0,

        WINDOW_Close, 
        WINDOW_Resize, 
        WINDOW_Move,
        WINDOW_Focus, 
        WINDOW_FocusLost,

        KEY_Pressed, 
        KEY_Released,
        KEY_Typed,

        MOUSE_ButtonPressed, 
        MOUSE_ButtonReleased, 
        MOUSE_Moved, 
        MOUSE_Scrolled
        
    };
    enum EventCategory
    {
        None                      = 0,
        WINDOW_EventCategory      = BIT(0),
        INPUT_EventCategory       = BIT(1),
        KEYBOARD_EventCategory    = BIT(2),
        MOUSE_EventCategory       = BIT(3),
        MOUSEBUTTON_EventCategory = BIT(4)

    };
    
    //Base class for all Events; To be modified to support buffered queue
    class Event
    {
        public:
            virtual EventType GetEventType() const = 0;
            virtual int GetEventCategory() const = 0;
            virtual const char* GetEventName() const = 0;

            bool IsEventInCategory(EventCategory category) { return GetEventCategory() & category;} //Check if Event belongs to certain category

            bool Handled = false;
    };

}