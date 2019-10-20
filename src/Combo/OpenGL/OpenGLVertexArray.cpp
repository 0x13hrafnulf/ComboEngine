#include "combopch.h"
#include "OpenGLVertexArray.h"

#include "glad/glad.h"

namespace Combo
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Combo::ShaderDataType::Float:    return GL_FLOAT;
		case Combo::ShaderDataType::Float2:   return GL_FLOAT;
		case Combo::ShaderDataType::Float3:   return GL_FLOAT;
		case Combo::ShaderDataType::Float4:   return GL_FLOAT;
		case Combo::ShaderDataType::Mat3:     return GL_FLOAT;
		case Combo::ShaderDataType::Mat4:     return GL_FLOAT;
		case Combo::ShaderDataType::Int:      return GL_INT;
		case Combo::ShaderDataType::Int2:     return GL_INT;
		case Combo::ShaderDataType::Int3:     return GL_INT;
		case Combo::ShaderDataType::Int4:     return GL_INT;
		case Combo::ShaderDataType::Bool:     return GL_BOOL;
		default: COMBO_ERROR_LOG("Unknown ShaderDataType!"); return 0;
		}
		return 0;
	}
    OpenGLVertexArray::OpenGLVertexArray()
    {
        glCreateVertexArrays(1, &m_RendererID);
    }
    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_RendererID);
    }
    void OpenGLVertexArray::Bind() const 
    {
        glBindVertexArray(m_RendererID);
    }
    void OpenGLVertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }
    void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
    {
        if(!vertexBuffer->GetLayout().GetBufferElements().size()) 
            COMBO_ERROR_LOG("Vertex buffer has no layout!");

        glBindVertexArray(m_RendererID);
        vertexBuffer->Bind();

        const auto& layout = vertexBuffer->GetLayout();

        for(const auto& element : layout)
        {
			glEnableVertexAttribArray(m_VertexBufferIndex);
            glVertexAttribPointer(m_VertexBufferIndex, 
								  element.GetCount(), 
                                  ShaderDataTypeToOpenGLBaseType(element.m_Type), 
				                  element.m_Normalized ? GL_TRUE : GL_FALSE, 
                                  layout.GetStride(), 
								  (const void*)(intptr_t)element.m_Offset);
            ++m_VertexBufferIndex;
        }

        m_VertexBuffers.push_back(vertexBuffer);

    }
    void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
    {
        glBindVertexArray(m_RendererID);
        indexBuffer->Bind();

        m_IndexBuffer = indexBuffer;
    }

    
}