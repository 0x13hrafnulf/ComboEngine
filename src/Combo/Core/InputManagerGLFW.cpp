#include "Combo/combopch.h"
#include "InputManagerGLFW.h"
#include "Engine.h"

#include <GLFW/glfw3.h>


namespace Combo {
    
    std::unique_ptr<InputManager> InputManager::s_Instance = std::make_unique<InputManagerGLFW>();

    bool InputManagerGLFW::IsKeyPressedImpl(KeyboardKey key)
    {
        auto window = static_cast<GLFWwindow*>(Engine::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, (int)key);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
    }
    
        
    bool InputManagerGLFW::IsMouseButtonPressedImpl(MouseButton button)
    {
        auto window = static_cast<GLFWwindow*>(Engine::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, (int)button);
		return state == GLFW_PRESS;
    }
    std::pair<float, float> InputManagerGLFW::GetMousePositionImpl()
    {
        auto window = static_cast<GLFWwindow*>(Engine::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
    }
    float InputManagerGLFW::GetMouseXImpl()
    {
        return GetMousePositionImpl().first;
    }
    float InputManagerGLFW::GetMouseYImpl()
    {
        return GetMousePositionImpl().second;
    }
}