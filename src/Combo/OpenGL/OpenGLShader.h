#pragma once

#include "Combo/Renderer/Shader.h"
#include <glm/glm.hpp>

typedef unsigned int GLenum;

namespace Combo
{
    class OpenGLShader : public Shader
    {
        public:
            OpenGLShader(const std::string& filepath);
            OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
            virtual ~OpenGLShader();

            virtual void Bind() const override;
            virtual void Unbind() const override;

            virtual const std::string& GetShaderName() const override { return m_Name; }

            virtual void SetInt(const std::string& name, int value) override;
            virtual void SetFloat3(const std::string& name, const glm::vec3& value) override;
            virtual void SetFloat4(const std::string& name, const glm::vec4& value) override;
            virtual void SetMat4(const std::string& name, const glm::mat4& value) override;

            void UploadUniformFloat(const std::string& name, float value);
            void UploadUniformFloat2(const std::string& name, const glm::vec2& values);
            void UploadUniformFloat3(const std::string& name, const glm::vec3& values);
            void UploadUniformFloat4(const std::string& name, const glm::vec4& values);
            void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
            void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
            void UploadUniformInt(const std::string& name, int value);

        private:
            //Functions
            std::string ReadFile(const std::string& filepath);
            std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
            void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

            //Data
            uint32_t m_RendererID;
            std::string m_Name;
    };
}