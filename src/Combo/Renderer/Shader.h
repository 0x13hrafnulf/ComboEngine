#pragma once 
#include <string>
#include <unordered_map>
#include <memory>



namespace Combo
{
    
    class Shader
    {
        public:

            virtual ~Shader() = default;

            virtual void Bind() const = 0;
            virtual void Unbind() const = 0;

          
            static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
          
            
        private:

    };
}