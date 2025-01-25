#ifndef __SHADER_H__
#define __SHADER_H__

#include "common.h"

// 클래스에 대한 스마트 포인터를 생성하는 매크로.
CLASS_PTR(Shader);

class Shader {
public:
    static ShaderUPtr CreateFromFile(const std::string& filename, GLenum shaderType);
    ~Shader();
    uint32_t Get() const { return m_shader; }  // shader 오브젝트 생성은 shader 내부에서만 하기 위해서 Get()만 선언.  
private:
    Shader() {} // 생성자를 private으로 선언했기에 외부에서 직접 생성 불가능. 객체를 생성하려면 반드시 CreateFromFile 메서드를 사용해야함.
    bool LoadFile(const std::string& filename, GLenum shaderType);
    uint32_t m_shader { 0 };
};

#endif // __SHADER_H__