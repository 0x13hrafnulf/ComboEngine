#pragma once

#include "../Renderer/Buffer.h"

namespace Combo
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
        public:

            OpenGLVertexBuffer(float* vertices, uint32_t size);
            virtual ~OpenGLVertexBuffer();

            virtual void Bind() const override;
            virtual void Unbind() const override;

            inline const BufferLayout& GetLayout() const override { return m_Layout;}
            inline void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }  
        private:
            uint32_t m_RendererID;
		    BufferLayout m_Layout;
    };

    class OpenGLIndexBuffer : public IndexBuffer
    {
        public:
            OpenGLIndexBuffer(float* indices, uint32_t count);
            virtual ~OpenGLIndexBuffer();

            virtual void Bind() const override;
            virtual void Unbind() const override;
            inline uint32_t GetCount() const override { return m_Count;}
   
        private:
            uint32_t m_RendererID;
		    uint32_t m_Count;
    };
}