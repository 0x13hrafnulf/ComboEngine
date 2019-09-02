
#include "InputManager.h"

namespace Combo {
    class SDLInputManager : public InputManager
    {
        public:

        virtual bool IsKeyPressedImpl(KeyboardKey key) override;
        // virtual bool IsKeyReleasedImpl(KeyboardKey key);
        // virtual bool IsKeyDownImpl(KeyboardKey key);
        
        virtual bool IsMouseButtonPressedImpl(MouseButton button) override;
        virtual std::pair<float, float> GetMousePositionImpl() override;
        virtual float GetMouseXImpl() override;
        virtual float GetMouseYImpl() override;


    };
}