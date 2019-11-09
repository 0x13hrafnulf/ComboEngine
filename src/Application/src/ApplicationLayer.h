#pragma once

#include <Combo/Combo.h>


class ApplicationLayer : public Combo::Layer
{
    public:

        ApplicationLayer();
        virtual ~ApplicationLayer() = default;

        virtual void Attach() override;
        virtual void Detach() override;

        virtual void Update(Combo::Timestep tstep) override;
        virtual void OnEvent(Combo::Event& event) override;
        virtual void ImGuiRender() override;


    private:
    	Combo::OrthographicCameraController m_CameraController;
	
	// Temp
    	std::shared_ptr<Combo::VertexArray> m_SquareVA;
    	std::shared_ptr<Combo::Shader> m_FlatColorShader;
        std::shared_ptr<Combo::Texture2D> m_GridTexture;


	    glm::vec4 m_GridColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};
