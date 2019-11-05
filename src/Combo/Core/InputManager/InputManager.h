#pragma once

#include "Combo/Core/InputCodes.h"

namespace Combo {


    class InputManager
    {
        public:
            InputManager(const InputManager&) = delete;
            InputManager& operator=(const InputManager&) = delete;

            inline static bool IsKeyPressed(KeyboardKey key) 
            {
                return s_Instance->IsKeyPressedImpl(key);
            }

            inline static bool IsMouseButtonPressed(MouseButton button)
            {
                return s_Instance->IsMouseButtonPressedImpl(button);
            }
            inline static std::pair<float, float> GetMousePosition()
            {
                return s_Instance->GetMousePositionImpl();
            }
            inline static float GetMouseX()
            {
                return s_Instance->GetMousePositionImpl().first;
            }
            inline static float GetMouseY()
            {
                 return s_Instance->GetMousePositionImpl().second;
            }

            // inline static bool IsKeyReleased(KeyboardKey key);
            // inline static bool IsKeyDown(KeyboardKey key);
        private:
            static std::unique_ptr<InputManager> s_Instance;
        protected:
            InputManager() = default;

            virtual bool IsKeyPressedImpl(KeyboardKey key) = 0;
           
            virtual bool IsMouseButtonPressedImpl(MouseButton button) = 0;
            virtual std::pair<float, float> GetMousePositionImpl() = 0;
            virtual float GetMouseXImpl() = 0;
            virtual float GetMouseYImpl() = 0;
            
            // virtual bool IsKeyReleasedImpl(KeyboardKey key);
            // virtual bool IsKeyDownImpl(KeyboardKey key);
    };
    
}