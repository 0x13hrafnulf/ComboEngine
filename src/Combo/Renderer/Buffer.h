#pragma once

namespace Combo
{
    enum class ShaderDataType
    {
        None,
        Float,
        Float2,
        Float3,
        Float4,
        Mat3, //Matrix 3x3
        Mat4, //Matrix 4x4
        Int,
        Int2,
        Int3,
        Int4,
        Bool
    };

    static uint32_t GetShaderDataTypeSize(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float:  return 4 * 4;
            case ShaderDataType::Float2: return 4 * 4;
            case ShaderDataType::Float3: return 4 * 4;
            case ShaderDataType::Float4: return 4 * 4;
            case ShaderDataType::Mat3:   return 4 * 3 * 3;
            case ShaderDataType::Mat4:   return 4 * 4 * 4;
            case ShaderDataType::Int:    return 4;
            case ShaderDataType::Int2:   return 4 * 2;
            case ShaderDataType::Int3:   return 4 * 3;
            case ShaderDataType::Int4:   return 4 * 4;  
            case ShaderDataType::Bool:   return 1;  
            default: return 0;
        }
        return 0;
    }   


    struct BufferElement
    {
        //Data
        std::string m_Name;
        ShaderDataType m_Type;
        uint32_t m_Size;
        uint32_t m_Offset;
        bool m_Normalized;
        //
        BufferElement() {}

        BufferElement(ShaderDataType type, std::string name, bool normalized)

        : m_Name(name),
          m_Type(type),
          m_Size(GetShaderDataTypeSize(type)),
          m_Offset(0),
          m_Normalized(normalized) 
        {

        }
        
        uint32_t GetCount() const
        {
            switch (m_Type)
            {
                case ShaderDataType::Float:  return  1;
                case ShaderDataType::Float2: return  2;
                case ShaderDataType::Float3: return  3;
                case ShaderDataType::Float4: return  4;
                case ShaderDataType::Mat3:   return  3 * 3;
                case ShaderDataType::Mat4:   return  4 * 4;
                case ShaderDataType::Int:    return  1;
                case ShaderDataType::Int2:   return  2;
                case ShaderDataType::Int3:   return  3;
                case ShaderDataType::Int4:   return  4;  
                case ShaderDataType::Bool:   return  1;  
                default: return 0;
            }
            return 0;
        }
    };

    class BufferLayout
    {
        public:
            BufferLayout();

            BufferLayout(const std::initializer_list<BufferElement>& elements)
            :m_BufferElements(elements)
            {
                CalculateStrideAndOffset();
            }

            inline uint32_t GetStride() const { return m_Stride; }
            inline const std::vector<BufferElement>& GetBufferElements() const { return m_BufferElements; }

            std::vector<BufferElement>::iterator begin() { return m_BufferElements.begin(); }
            std::vector<BufferElement>::iterator end() { return m_BufferElements.end(); }
            std::vector<BufferElement>::const_iterator begin() const { return m_BufferElements.begin(); }
            std::vector<BufferElement>::const_iterator end() const { return m_BufferElements.end(); }

        private:

            std::vector<BufferElement> m_BufferElements;
            uint32_t m_Stride = 0;

            void CalculateStrideAndOffset()
            {
                uint32_t offset = 0;
                m_Stride = 0;

                for (auto& element : m_BufferElements)
                {
                    element.m_Offset = offset;
                    offset += element.m_Size;
                    m_Stride += element.m_Size;
                }
                
            }

    };

    class VertexBuffer
    {
        virtual ~VertexBuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

        static VertexBuffer* Create(float* vertices, uint32_t size); 
    };

    class IndexBuffer
    {
        virtual ~IndexBuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        virtual uint32_t GetCount() const = 0;

        static IndexBuffer* Create(float* indices, uint32_t size); 
   

    };
}