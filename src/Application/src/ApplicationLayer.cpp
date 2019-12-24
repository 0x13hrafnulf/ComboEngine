
#include "ApplicationLayer.h"

#include <imgui/imgui.h>
#include "Combo/UI/ImGuiLayer.h"
#include <imgui/imgui_internal.h>
#include <Combo/OpenGL/OpenGLShader.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

static void ImGuiShowHelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}


ApplicationLayer::ApplicationLayer()
: Layer("Sandbox"), m_CameraController(1280.0f / 720.0f)
{
}

void ApplicationLayer::Attach()
{
	m_GridTexture = Combo::Texture2D::Create("assets/textures/Checkerboard.png");
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

	float xoffset, yoffset = 0;
	for (int y = 0; y < 30; y++)
	{
		for (int x = 0; x < 30; x++)
		{
			glm::vec3 pos(x * 0.11f, y * 0.11f, -0.1f);
			Combo::Renderer2D::DrawQuad(pos, {1.0f/10.0f, 1.0f/10.0f}, m_GridColor);
		}
	}

	
	Combo::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Combo::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
	Combo::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_GridTexture);
	Combo::Renderer2D::EndScene();
}
void ApplicationLayer::ImGuiRender() 
{
	
    ImGui::Begin("Settings");
    ImGui::ColorEdit3("Grid Color", glm::value_ptr(m_GridColor));
    ImGui::End();


}
void ApplicationLayer::OnEvent(Combo::Event& e)
{
    m_CameraController.OnEvent(e);
}