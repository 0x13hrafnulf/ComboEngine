#include "combopch.h"

#include "OrthographicCameraControl.h"
#include "Combo/InputManager/InputManager.h"
#include "Combo/Core/InputCodes.h"


namespace Combo
{
    OrthographicCameraControl::OrthographicCameraControl(float aspectRatio, bool rotate = false)
    : m_AspectRatio(aspectRatio), m_Camera()
    {

    }

    void OrthographicCameraControl::Update(Timestep ts)
    {
         if (Combo::InputManagerGLFW::IsKeyPressed(Combo::KeyboardKey::KEY_LEFT))
				m_CameraPosition.x -= m_CameraMoveSpeed * tstep;
			else if (Combo::InputManagerGLFW::IsKeyPressed(Combo::KeyboardKey::KEY_RIGHT))
				m_CameraPosition.x += m_CameraMoveSpeed * tstep;

			if (Combo::InputManagerGLFW::IsKeyPressed(Combo::KeyboardKey::KEY_UP))
				m_CameraPosition.y += m_CameraMoveSpeed * tstep;
			else if (Combo::InputManagerGLFW::IsKeyPressed(Combo::KeyboardKey::KEY_DOWN))
				m_CameraPosition.y -= m_CameraMoveSpeed * tstep;

        if(m_Rotation)
        {
            if (Combo::InputManagerGLFW::IsKeyPressed(Combo::KeyboardKey::KEY_Q))
				m_CameraRotation += m_CameraRotationSpeed * tstep;
			if (Combo::InputManagerGLFW::IsKeyPressed(Combo::KeyboardKey::KEY_E))
				m_CameraRotation -= m_CameraRotationSpeed * tstep;

            m_Camera.SetRotation(m_CameraRotation);
        }
        
        m_Camera.SetPosition(m_CameraPosition);
        m_CameraTranslationSpeed = m_ZoomLevel;
			
    }
    void OrthographicCameraControl::OnEvent(Event& e)
    {
        EventManager dispatcher;
        dispatcher.DispatchEvent<MouseScrolledEvent>([this](MouseScrolledEvent& e)
        {
            return this->MouseControl(e);
        });
        dispatcher.DispatchEvent<WindowResizeEvent>([this](WindowResizeEvent& e)
        {
            return this->WindowResize(e);
        });

        //dispatcher.DispatchEvent<MouseScrolledEvent>([this](WindowResizeEvent& e);
        //dispatcher.DispatchEvent<WindowResizeEvent>([this](WindowResizeEvent& e);
    }

    bool OrthographicCameraControl::MouseControl(MouseScrolledEvent& event)
    {
        m_ZoomLevel -= event.GetYOffset() * 0.25f;
        m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel,
                                m_AspectRatio * m_ZoomLevel,
                                -m_ZoomLevel,
                                m_ZoomLevel);
        return false;
    }

     bool OrthographicCameraControl::WindowResize(WindowResizeEvent& event)
     {
        m_AspectRatio = (float)event.GetWidth() / (float)event.GetHeight();
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel,
                                m_AspectRatio * m_ZoomLevel,
                                -m_ZoomLevel,
                                m_ZoomLevel);

        return false;
     }
}   