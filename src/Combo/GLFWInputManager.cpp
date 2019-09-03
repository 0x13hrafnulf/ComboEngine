#include "combopch.h"
#include "GLFWInputManager.h"

#include "Engine.h"
#include <GLFW/glfw3.h>


namespace Combo {
    
    bool GLFWInputManager::IsKeyPressedImpl(int key)
    {
        auto window = static_cast<GLFWwindow*>(Engine::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, key);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
    }
    
        
    bool GLFWInputManager::IsMouseButtonPressedImpl(int button)
    {
        auto window = static_cast<GLFWwindow*>(Engine::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
    }
    std::pair<float, float> GLFWInputManager::GetMousePositionImpl()
    {
        auto window = static_cast<GLFWwindow*>(Engine::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
    }
    float GLFWInputManager::GetMouseXImpl()
    {
        return GetMousePositionImpl().first;
    }
    float GLFWInputManager::GetMouseYImpl()
    {
        return GetMousePositionImpl().second;
    }
}