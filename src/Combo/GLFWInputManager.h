#pragma once
#include "InputManager/InputManager.h"

namespace Combo {
    class GLFWInputManager : public InputManager
    {
        public:

        virtual bool IsKeyPressedImpl(int key) override;
        // virtual bool IsKeyReleasedImpl(KeyboardKey key);
        // virtual bool IsKeyDownImpl(KeyboardKey key);
        
        virtual bool IsMouseButtonPressedImpl(int button) override;
        virtual std::pair<float, float> GetMousePositionImpl() override;
        virtual float GetMouseXImpl() override;
        virtual float GetMouseYImpl() override;


    };
}