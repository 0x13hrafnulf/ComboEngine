#pragma once

#include "OrthographicCamera.h"

#include "Combo/Core/Timestep.h"
#include "Combo/Core/InputManager/WindowEvent.h"
#include "Combo/Core/InputManager/MouseEvent.h"


namespace Combo
{
    class OrthographicCameraController
    {
        public:
            OrthographicCameraController(float aspectRatio, bool rotate = false);

            void Update(Timestep ts);
            void OnEvent(Event& e);

            OrthographicCamera& GetCamera() { return m_Camera; }
            const OrthographicCamera& GetCamera() const { return m_Camera; }

            float GetZoomLevel() const { return m_ZoomLevel; }
            void SetZoomLevel(float zoomLevel) { m_ZoomLevel = zoomLevel; }
        private:

            float m_AspectRatio;
            float m_ZoomLevel = 1.0f;
            OrthographicCamera m_Camera;
            bool m_Rotation;

            glm::vec3 m_CameraPosition = {0.0f, 0.0f, 0.0f};
            float m_CameraRotation = 0.0f;
            float m_CameraTranslationSpeed = 5.0f;
            float m_CameraRotationSpeed = 180.0f;

            bool MouseControl(MouseScrolledEvent& event);
            bool WindowResize(WindowResizeEvent& event);

    };
}