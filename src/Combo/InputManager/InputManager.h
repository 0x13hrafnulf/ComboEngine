#pragma once

#include <SDL2/SDL.h>
#include "InputCodes.h"

namespace Combo {

    
    class InputManager
    {
        public:
            InputManager(const InputManager&) = delete;
            InputManager& operator=(const InputManager&) = delete;

            inline static bool IsKeyPressed(KeyboardKey key);
            // inline static bool IsKeyReleased(KeyboardKey key);
            // inline static bool IsKeyDown(KeyboardKey key);

            inline static bool IsMouseButtonPressed(MouseButton button);
            inline static std::pair<float, float> GetMousePosition();
            inline static float GetMouseX();
            inline static float GetMouseY();
        private:
            static InputManager s_Instance;
        protected:
            InputManager() = default;

            bool IsKeyPressedImpl(KeyboardKey key);
            // bool IsKeyReleasedImpl(KeyboardKey key);
            // bool IsKeyDownImpl(KeyboardKey key);
           
            bool IsMouseButtonPressedImpl(MouseButton button);
            std::pair<float, float> GetMousePositionImpl();
            float GetMouseXImpl();
            float GetMouseYImpl();

    };
    
}