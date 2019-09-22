#pragma once

#include <memory>

#include "Buffer.h"

namespace Combo
{
    class VertexArray
    {
        public:

        virtual ~VertexArray() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void AddVertexBuffer() = 0;
        virtual void SetIndexBuffer() = 0;

        virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffer() const = 0;
        virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;



        static VertexArray* Create();

    };
}