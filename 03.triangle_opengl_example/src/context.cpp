#include "context.h"

ContextUPtr Context::Create() {
    auto context = ContextUPtr(new Context());
    if (!context->Init())
        return nullptr;
    return std::move(context);
}

bool Context::Init() {

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
    };

    // vertex array object를 생성한 후에
    glGenVertexArrays(1, &m_vertexArrayObject);
    glBindVertexArray(m_vertexArrayObject);
    // vertex buffer object를 만듦
    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9, vertices, GL_STATIC_DRAW);
    // 그 담에 vertex attributes를 설정
    glEnableVertexAttribArray(0); // shader/simple.vs의 location과 연결
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

    // shader load
    // 기존엔 auto로 선언했기에 shader의 unique pointer 값 (==스마트 포인터)이 들어갔었는데,
    // Create 안에 들어가야하는 인자의 타입은 그냥 shader pointer 값이 들어가야함.
    ShaderPtr vertShader = Shader::CreateFromFile("./shader/simple.vs", GL_VERTEX_SHADER);
    ShaderPtr fragShader = Shader::CreateFromFile("./shader/simple.fs", GL_FRAGMENT_SHADER);
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

    // state-setting
    glClearColor(1.0f, 0.6f, 0.8f, 1.0f); // window 배경색을 뭘로 clear 할 지
 
    return true;
}

void Context::Render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(m_program->Get());
    glPointSize(10.0f); 
    // primitive: 그리고자하는 타입, offset: 첫 정점 idx, count: 정점 개수
    glDrawArrays(GL_LINE_STRIP, 0, 3); // draw array
}