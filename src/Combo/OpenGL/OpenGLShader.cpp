#include "../combopch.h"

#include "OpenGLShader.h"

#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

namespace Combo
{
    OpenGLShader::OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource)
    {
        //Vertex Shader Handler
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        const GLchar* source = vertexSource.c_str();
        glShaderSource(vertexShader, 1, &source, 0);
        glCompileShader(vertexShader);
        
        GLint compiled = 0;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compiled);
        if (compiled == GL_FALSE)
        {
            GLint maximumLength = 0;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maximumLength);

            std::vector<GLchar> infoLog(maximumLength);
            glGetShaderInfoLog(vertexShader, maximumLength, &maximumLength, &infoLog[0]);

            glDeleteShader(vertexShader);

            COMBO_ERROR_LOG("{0}", infoLog.data());
            COMBO_ERROR_LOG("Vertex shader failed to compile!");
            return;
        }
        

        //Fragment Shader Handler
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        source = fragmentSource.c_str();
        glShaderSource(fragmentShader, 1, &source, 0);
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compiled);
        if (compiled == GL_FALSE)
        {
            GLint maximumLength = 0;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maximumLength);

            std::vector<GLchar> infoLog(maximumLength);
            glGetShaderInfoLog(fragmentShader, maximumLength, &maximumLength, &infoLog[0]);

            glDeleteShader(fragmentShader);
            glDeleteShader(vertexShader);

            COMBO_ERROR_LOG("{0}", infoLog.data());
            COMBO_ERROR_LOG("Fragment shader failed to compile!");
            return;
        }

        m_RendererID = glCreateProgram();
        GLint program = m_RendererID;

        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);

        glLinkProgram(program);

        GLint linked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &linked);
        if(linked == GL_FALSE)
        {
            GLint maximumLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maximumLength);

            std::vector<GLchar> infoLog(maximumLength);
            glGetProgramInfoLog(program, maximumLength, &maximumLength, &infoLog[0]);

            glDeleteProgram(program);
            glDeleteShader(fragmentShader);
            glDeleteShader(vertexShader);

            COMBO_ERROR_LOG("{0}", infoLog.data());
            COMBO_ERROR_LOG("Shader Program failed to link!");
            return;
        }
        glDetachShader(program, vertexShader);
        glDetachShader(program, fragmentShader);
    }
    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_RendererID);
    }
    void OpenGLShader::Bind() const
    {
        glUseProgram(m_RendererID);
    }
    void OpenGLShader::Unbind() const
    {
        glUseProgram(0);
    }
    void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1f(location, value);
    }
    void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& values)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform2f(location, values.x, values.y);
    }
    void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& values)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform3f(location, values.x, values.y, values.z);
    }
    void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& values)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform4f(location, values.x, values.y, values.z, values.w);
    }
    void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }
    void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix) 
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }
    void OpenGLShader::UploadUniformInt(const std::string& name, int value)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1i(location, value);
    }
}