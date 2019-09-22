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

            virtual const std::string& GetShaderName() const = 0;

            static std::shared_ptr<Shader> Create(const std::string& filepath);
            static std::shared_ptr<Shader> Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);

            
        private:

    };
}