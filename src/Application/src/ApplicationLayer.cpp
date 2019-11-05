
#include "ApplicationLayer.h"
#include <imgui/imgui.h>

#include <Combo/OpenGL/OpenGLShader.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



ApplicationLayer::ApplicationLayer()
: Layer("Sandbox"), m_CameraController(1280.0f / 720.0f)
{
}

void ApplicationLayer::Attach()
{

}
void ApplicationLayer::Detach()
{

}

void ApplicationLayer::Update(Combo::Timestep ts)
{
    m_CameraController.Update(ts);
	// Render
	Combo::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Combo::RenderCommand::Clear();

	Combo::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Combo::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Combo::Renderer2D::EndScene();
}
void ApplicationLayer::ImGuiRender() 
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}
void ApplicationLayer::OnEvent(Combo::Event& e)
{
    m_CameraController.OnEvent(e);
}