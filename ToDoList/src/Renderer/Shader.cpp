#include "Shader.h"

#include <iostream>

Shader::Shader(const std::string& filepath)
    : m_RendererID(0), m_Filepath(filepath)
{
    ShaderSource source = ParseShader(m_Filepath);
    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{

}

unsigned int Shader::CreateShader(const std::string& vertexSource, const std::string& fragmentSource)
{
    unsigned int id = glCreateProgram();

    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexSource);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);

    glAttachShader(id, vs);
    glAttachShader(id, fs);
    glLinkProgram(id);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return id;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    return shader;
}

void Shader::Bind() const
{
    glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

void Shader::MakeShader(const std::string& filepath)
{
    m_Filepath = filepath;
    ShaderSource source = ParseShader(m_Filepath);
    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

void Shader::SetUniform1i(const std::string& name, int value)
{
    glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform1f(const std::string& name, float value)
{
    glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    // 1 is count only 1 matrix we are passing in
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::SetUniformVec3(const std::string& name, const glm::vec3& vec3)
{
    glUniform3f(GetUniformLocation(name), vec3.x, vec3.y, vec3.z);
}

void Shader::SetUniformVec3(const std::string& name, const float& x, const float& y, const float& z)
{
    glUniform3f(GetUniformLocation(name), x, y, z);
}

void Shader::SetUniformVec4(const std::string& name, const glm::vec4& vec4)
{
    glUniform4f(GetUniformLocation(name), vec4.x, vec4.y, vec4.z, vec4.w);
}

unsigned int Shader::GetRendererID() const
{
    return m_RendererID;
}

int Shader::GetUniformLocation(const std::string& name)
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    int location = glGetUniformLocation(m_RendererID, name.c_str());
    if (location == -1)
        std::cout << "Warning: uniform " << name << " doesn't exist!\n";

    m_UniformLocationCache[name] = location;
    return location;
}

ShaderSource Shader::ParseShader(const std::string& filepath)
{
    // opening file
    std::ifstream stream(filepath);

    // init shaderTypes
    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    // init 2 stringstreams
    std::stringstream ss[2];
    // creating an instance of ShaderType with ShaderType None
    ShaderType type = ShaderType::NONE;
    std::string line;
    // getting lines from open file while there are lines left
    while (getline(stream, line))
    {
        // checking if #shader was found
        if (line.find("#shader") != std::string::npos)
        {
            // if #shader was found check if vertex or fragment and set type to vertex or fragment
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            // if a type is chosen the stringstream at the types position will be appended that line and a new line
            ss[(int)type] << line << "\n";
        }
    }
    // returning stringstream 0 and 1 which are vertex and fragment source
    return { ss[0].str(), ss[1].str() };
}