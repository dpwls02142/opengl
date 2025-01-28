#include "context.h"

ContextUPtr Context::Create() {
    auto context = ContextUPtr(new Context());
    if (!context->Init())
        return nullptr;
    return std::move(context);
}

bool Context::Init() {

    float vertices[] = {
         0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // top right, red
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right, green
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom left, blue
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f,  // top left, yellow
    };
 
    uint32_t indices[] = { // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3, // second triangle
    };

    // vertex array object를 생성한 후에
    m_vertexLayout = VertexLayout::Create();
    // vertex buffer object를 만듦
    m_vertexBuffer = Buffer::CreateWithData(GL_ARRAY_BUFFER, GL_STATIC_DRAW, vertices, sizeof(float) * 24);
    // 그 담에 vertex attributes를 설정
    m_vertexLayout->SetAttrib(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0); // 한 점의 길이가 6개니까 *6
    m_vertexLayout->SetAttrib(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, sizeof(float) * 3);
    // index buffer 생성
    m_indexBuffer = Buffer::CreateWithData(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, indices, sizeof(uint32_t) * 6);

    // shader load
    // 기존엔 auto로 선언했기에 shader의 unique pointer 값 (==스마트 포인터)이 들어갔었는데,
    // Create 안에 들어가야하는 인자의 타입은 그냥 shader pointer 값이 들어가야함.
    ShaderPtr vertShader = Shader::CreateFromFile("./shader/per_vertex_color.vs", GL_VERTEX_SHADER);
    ShaderPtr fragShader = Shader::CreateFromFile("./shader/per_vertex_color.fs", GL_FRAGMENT_SHADER);
    if (!vertShader || !fragShader){
        return false;
    }
    SPDLOG_INFO("vertex shader id: {}", vertShader->Get());
    SPDLOG_INFO("fragment shader id: {}", fragShader->Get());

    m_program = Program::Create({fragShader, vertShader});
    if (!m_program){
        return false;
    }
    SPDLOG_INFO("program id: {}", m_program->Get());

    // uniform 값 입력
    // auto loc = glGetUniformLocation(m_program->Get(), "color");
    // m_program->Use();
    // glUniform4f(loc, 1.0f, 1.0f, 1.0f, 1.0f);

    return true;
}

void Context::Render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(10.0f); 
    m_program->Use();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // static float time = 0.0f;
    // float t = sinf(time) * 0.5f + 0.5f;
    // auto loc = glGetUniformLocation(m_program->Get(), "color");
    // m_program->Use();
    // glUniform4f(loc, t*t, 2.0f*t*(1.0f-t), (1.0f-t)*(1.0f-t), 1.0f);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // time += 0.016f;
}