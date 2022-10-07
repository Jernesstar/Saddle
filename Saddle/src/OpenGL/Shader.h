#pragma once

#include <string>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <glm/mat2x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

#include "Saddle/Core/Utils.h"

namespace Saddle {

enum class ShaderType { VertexShader, FragmentShader };

class Shader {
private:
    struct ShaderFile {
        const ShaderType Type;
        const std::string Path;
        const std::string Source;

        ShaderFile(ShaderType type, const std::string& path)
            : Type(type), Path(path), Source(Utils::LoadFile(path)) { }
    };

public:
    ShaderFile VertexShader;
    ShaderFile FragmentShader;

public:
    Shader(const std::string& vertex_shader_path, const std::string& fragment_shader_path);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    void SetUniformInt(const std::string& name, int _int);
    void SetUniformFloat(const std::string& name, float _float);

    void SetUniformVec2(const std::string& name, const glm::vec2& vec);
    void SetUniformVec3(const std::string& name, const glm::vec3& vec);
    void SetUniformVec4(const std::string& name, const glm::vec4& vec);

    void SetUniformMatrix2(const std::string& name, const glm::mat2& matrix);
    void SetUniformMatrix3(const std::string& name, const glm::mat3& matrix);
    void SetUniformMatrix4(const std::string& name, const glm::mat4& matrix);

    operator int() const { return m_ProgramID; } 

private:
    unsigned int m_ProgramID;

private:
    static unsigned int CreateShader(const ShaderFile& shader_file);
    static unsigned int CreateProgram(unsigned int vertex_shader, unsigned int fragment_shader);
};

}