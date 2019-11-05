#include "Combo/combopch.h"

#include "OpenGLShader.h"
#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Combo
{
    static GLenum ShaderTypeFromString(const std::string& type)
    {
        if(type == "vertex")
            return GL_VERTEX_SHADER;
        if(type == "fragment" || type == "pixel")
            return GL_FRAGMENT_SHADER;

        COMBO_ERROR_LOG("Unknown Shader type!");
        return 0;
    }

    OpenGLShader::OpenGLShader(const std::string& filepath)
    {
       std::string source = ReadFile(filepath);
       auto shaderSource = PreProcess(source);
       Compile(shaderSource);

       //parsing shader name from filepath

        auto lastSlash = filepath.find_last_of("/\\");
        lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
        auto lastDot = filepath.rfind('.');
        auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
        m_Name = filepath.substr(lastSlash, count);

    }
    OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
    : m_Name(name)
    {
        std::unordered_map<GLenum, std::string> sources;
        sources[GL_VERTEX_SHADER] = vertexSrc;
        sources[GL_FRAGMENT_SHADER] = fragmentSrc;
        Compile(sources);
    }
    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_RendererID);
    }
    std::string OpenGLShader::ReadFile(const std::string& filepath)
    {
        std::string result; 
        std::ifstream in(filepath, std::ios::in | std::ios::binary);
        if(in)
        {
            in.seekg(0, std::ios::end);
            result.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&result[0], result.size());
            in.close();
        }
        else
        {
            COMBO_ERROR_LOG("Cannot open file '{0}'!", filepath);
        }
        return result;

    }
    std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
    {
        std::unordered_map<GLenum, std::string> shaderSources;
        
        const char* typeToken = "#type";
        size_t typeTokenLength = strlen(typeToken);
        size_t position = source.find(typeToken, 0);

        while(position != std::string::npos)
        {
            size_t endOfLine = source.find_first_of("\r\n", position);
            if(endOfLine == std::string::npos) COMBO_ERROR_LOG("Syntax error!");
            size_t begin = position + typeTokenLength + 1;
            std::string type = source.substr(begin, endOfLine - begin);
            if(ShaderTypeFromString(type)) COMBO_ERROR_LOG("Invalid Shader type!");

            size_t nextLinePos = source.find_first_not_of("\r\n", endOfLine);
            if(nextLinePos == std::string::npos) COMBO_ERROR_LOG("Syntax Error!");

            position = source.find(typeToken, nextLinePos);
            shaderSources[ShaderTypeFromString(type)] = 
                            source.substr(nextLinePos, position - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
        }

        return shaderSources;
    }
    void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
    {
        GLuint program = glCreateProgram();
        if(shaderSources.size() <= 2) COMBO_ERROR_LOG("Only 2 shaders supported for now!");
        std::array<GLenum, 2> glShaderIDs;
        int glShaderIDIndex = 0;
        
        for(auto& keyValue : shaderSources)
        {
            GLenum type = keyValue.first;
            const std::string& source = keyValue.second;

            GLuint shader = glCreateShader(type);

            const GLchar* sourceCstr = source.c_str();
            glShaderSource(shader, 1, &sourceCstr, 0);

            glCompileShader(shader);

            GLint isCompiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
            if(isCompiled == GL_FALSE)
            {
                GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

                COMBO_ERROR_LOG("{0}", infoLog.data());
                COMBO_ERROR_LOG("Shader compilation failure!");

				break;
            }

            glAttachShader(program, shader);
			glShaderIDs[glShaderIDIndex++] = shader;
        }
        m_RendererID = program;

        glLinkProgram(program);

        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
        if(isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);
			
			for (auto id : glShaderIDs)
				glDeleteShader(id);

            COMBO_ERROR_LOG("{0}", infoLog.data());
            COMBO_ERROR_LOG("Shader link failure!");

			return;
        }

        for(auto id : glShaderIDs)
        {
            glDetachShader(program, id);
            glDeleteShader(id);
        }
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