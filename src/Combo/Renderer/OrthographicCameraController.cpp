#include "Combo/combopch.h"

#include "OrthographicCameraController.h"
#include "Combo/Core/InputManager/InputManager.h"
#include "Combo/Core/InputCodes.h"
#include "Combo/Core/InputManager/EventManager.h"

namespace Combo
{
#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

    OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotate)
    : m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotate)
    {

    }

	void OrthographicCameraController::Update(Timestep ts)
	{
		if (Combo::InputManager::IsKeyPressed(Combo::KeyboardKey::KEY_LEFT))
		{
			m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}
		else if (Combo::InputManager::IsKeyPressed(Combo::KeyboardKey::KEY_RIGHT)) 
		{
			m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}
		if (Combo::InputManager::IsKeyPressed(Combo::KeyboardKey::KEY_UP))
		{
			m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}
		else if (Combo::InputManager::IsKeyPressed(Combo::KeyboardKey::KEY_DOWN))
		{
			m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}


		if (m_Rotation)
		{
			if (Combo::InputManager::IsKeyPressed(Combo::KeyboardKey::KEY_Q))
				m_CameraRotation += m_CameraRotationSpeed * ts;
			if (Combo::InputManager::IsKeyPressed(Combo::KeyboardKey::KEY_E))
				m_CameraRotation -= m_CameraRotationSpeed * ts;

			if (m_CameraRotation > 180.0f)
				m_CameraRotation -= 360.0f;
			else if (m_CameraRotation <= -180.0f)
				m_CameraRotation += 360.0f;

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);

		m_CameraTranslationSpeed = m_ZoomLevel;
	}

    void OrthographicCameraController::OnEvent(Event& e)
    {
        EventManager dispatcher(e);
      
		dispatcher.DispatchEvent<MouseScrolledEvent>(BIND_EVENT_FN(OrthographicCameraController::MouseControl));
		dispatcher.DispatchEvent<WindowResizeEvent>(BIND_EVENT_FN(OrthographicCameraController::WindowResize));
    }

    bool OrthographicCameraController::MouseControl(MouseScrolledEvent& event)
    {
        m_ZoomLevel -= event.GetYOffset() * 0.25f;
        m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel,
                                m_AspectRatio * m_ZoomLevel,
                                -m_ZoomLevel,
                                m_ZoomLevel);
        return false;
    }

     bool OrthographicCameraController::WindowResize(WindowResizeEvent& event)
     {
        m_AspectRatio = (float)event.GetWidth() / (float)event.GetHeight();
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel,
                                m_AspectRatio * m_ZoomLevel,
                                -m_ZoomLevel,
                                m_ZoomLevel);

        return false;
     }
}   