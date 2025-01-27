#include "context.h"

ContextUPtr Context::Create() {
    auto context = ContextUPtr(new Context());
    if (!context->Init())
        return nullptr;
    return std::move(context);
}

bool Context::Init() {

    float vertices[] = {
        0.5f, 0.5f, 0.0f, // top right
        0.5f, -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f, // top left
    };
    uint32_t indices[] = { // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3, // second triangle
    };

    // vertex array object를 생성한 후에
    m_vertexLayout = VertexLayout::Create();
    // vertex buffer object를 만듦
    m_vertexBuffer = Buffer::CreateWithData(GL_ARRAY_BUFFER, GL_STATIC_DRAW, vertices, sizeof(float) * 12);
    // 그 담에 vertex attributes를 설정
    m_vertexLayout->SetAttrib(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
	// index buffer 생성
    m_indexBuffer = Buffer::CreateWithData(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, indices, sizeof(uint32_t) * 6);

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
    m_program->Use();
    glPointSize(10.0f); 
    // primitive: 그리고자하는 타입, offset: 첫 정점 idx, count: 정점 개수
    // glDrawArrays(GL_TRIANGLES, 0, 6); // draw array
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}