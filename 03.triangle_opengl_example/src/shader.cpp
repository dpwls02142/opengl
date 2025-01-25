#include "shader.h"

ShaderUPtr Shader::CreateFromFile(const std::string& filename, GLenum shaderType) {
    auto shader = std::unique_ptr<Shader>(new Shader());
    if (!shader->LoadFile(filename, shaderType))
        return nullptr;
    return std::move(shader);
}

Shader::~Shader() {
  if (m_shader) {
    glDeleteShader(m_shader);
  }
}

bool Shader::LoadFile(const std::string& filename, GLenum shaderType) {
    auto result = LoadTextFile(filename);
    if (!result.has_value())
        return false;

    auto& code = result.value();
    const char* codePtr = code.c_str();
    int32_t codeLength = (int32_t)code.length();

    /*
    uint8_t = unsigned char
    int8_t = char
    uint16_t = unsigned short
    int16_t = short
    uint32_t = unsigned int
    int32_t = int
    uint64_t = unsigned long long
    int64_t = long long

    unsigned 자료형은 항상 양수만 저장함. 
    singed == 부호, 즉 부호가 없다는 의미이니 양수형 자료만 저장하는 것.
    */

    // create and compile shader
    m_shader = glCreateShader(shaderType); // shader 생성.
    glShaderSource(m_shader, 1, (const GLchar* const*)&codePtr, &codeLength);
    glCompileShader(m_shader);

    // check compile error
    int success = 0;
    glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success); // shader compile 성공 유무.
    if (!success) {
        char infoLog[1024];
        glGetShaderInfoLog(m_shader, 1024, nullptr, infoLog);
        SPDLOG_ERROR("failed to compile shader: \"{}\"", filename);
        SPDLOG_ERROR("reason: {}", infoLog);
        return false;
    }
    return true;
}