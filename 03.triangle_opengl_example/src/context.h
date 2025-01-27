#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include "buffer.h"
#include "common.h"
#include "shader.h"
#include "program.h"
#include "vertex_layout.h"

CLASS_PTR(Context)

class Context {
public:
    static ContextUPtr Create();
    void Render();    
private:
    Context() {}
    bool Init();
    ProgramUPtr m_program;

    VertexLayoutUPtr m_vertexLayout;
    // rectangle을 그릴 때 삼각형 2개를 붙이면 되는데,
    // 이렇게 하면 맞닿은 정점이 생기기에 낭비가 되니까 indexBuffer를 활용
    BufferUPtr m_vertexBuffer;
    BufferUPtr m_indexBuffer;
};

#endif // __CONTEXT_H__