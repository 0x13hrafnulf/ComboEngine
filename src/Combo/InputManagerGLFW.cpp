#include "combopch.h"
#include "InputManagerGLFW.h"

#include "Engine.h"
#include <GLFW/glfw3.h>


namespace Combo {
    
    InputManager* InputManager::s_Instance = new InputManagerGLFW();

    bool InputManagerGLFW::IsKeyPressedImpl(int key)
    {
        auto window = static_cast<GLFWwindow*>(Engine::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, key);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
    }
    
        
    bool InputManagerGLFW::IsMouseButtonPressedImpl(int button)
    {
        auto window = static_cast<GLFWwindow*>(Engine::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
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