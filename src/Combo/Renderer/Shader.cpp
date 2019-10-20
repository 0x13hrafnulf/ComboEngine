#include "combopch.h"
#include "Shader.h"
#include "RenderManager.h"
#include "../OpenGL/OpenGLShader.h"

namespace Combo
{
    std::shared_ptr<Shader> Shader::Create(const std::string& filepath)
    {
        switch(RenderManager::GetAPI())
        {
            case RendererAPI::API::NONE: COMBO_ERROR_LOG("RendererAPI is not supported!"); return nullptr;
            case RendererAPI::API::OpenGL: return new OpenGLShader(filepath);
            default: COMBO_ERROR_LOG("Unknown RenderAPI!"); return nullptr;
        }
        COMBO_ERROR_LOG("Unknown RenderAPI!");
        return nullptr;
    }
    std::shared_ptr<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch(RenderManager::GetAPI())
        {
            case RendererAPI::API::NONE: COMBO_ERROR_LOG("RendererAPI is not supported!"); return nullptr;
            case RendererAPI::API::OpenGL: return new OpenGLShader(name, vertexSrc, fragmentSrc);
            default: COMBO_ERROR_LOG("Unknown RenderAPI!"); return nullptr;
        }
        COMBO_ERROR_LOG("Unknown RenderAPI!");
        return nullptr;
    }

    void ShaderLibrary::Add(const std::string& name, const std::shared_ptr<Shader>& shader)
    {
        if(!Exists(name)) COMBO_ERROR_LOG("Shader already exists!");
        m_Shaders[name] = shader;
    }
    void ShaderLibrary::Add(const std::shared_ptr<Shader>& shader)
    {
        auto& name = shader->GetShaderName();
        Add(name, shader);
    }

    std::shared_ptr<Shader> ShaderLibrary::Load(const std::string& filepath)
    {
        auto shader = Shader::Create(filepath);
        Add(shader);
        return shader;
    }     
    std::shared_ptr<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
    {
        auto shader = Shader::Create(filepath);
        Add(name, shader);
        return shader;
    }        

    std::shared_ptr<Shader> ShaderLibrary::Get(const std::string& name)
    {
        if(!Exists(name)) COMBO_ERROR_LOG("Shader does not exist!");
        return m_Shaders[name];
    }          

    bool ShaderLibrary::Exists(const std::string& name) const
    {
        return m_Shaders.find(name) != m_Shaders.end();
    }

}