#include <spdlog/spdlog.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// glfw callbacks
void OnFramebufferSizeChange(GLFWwindow* window, int width, int height) {
    SPDLOG_INFO("framebuffer size changed: ({} x {})", width, height);
    glViewport(0, 0, width, height); // opengl이 그림을 그릴 화면의 위치 및 크기 설정
}

// 키보드 입력 콜백
void OnKeyEvent(GLFWwindow* window,
    int key, int scancode, int action, int mods) {
    SPDLOG_INFO("key: {}, scancode: {}, action: {}, mods: {}{}{}",
        key, scancode,
        action == GLFW_PRESS ? "Pressed" :
        action == GLFW_RELEASE ? "Released" :
        action == GLFW_REPEAT ? "Repeat" : "Unknown",
        mods & GLFW_MOD_CONTROL ? "C" : "-",
        mods & GLFW_MOD_SHIFT ? "S" : "-",
        mods & GLFW_MOD_ALT ? "A" : "-");
    // escape key를 누르면 윈도우 창 종료
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main(int argc, const char** argv){

    // console에 log 찍기
    SPDLOG_INFO("start program");

    // glfw 라이브러리 초기화, 실패하면 에러 출력후 종료
    SPDLOG_INFO("Initialize glfw");
    if (!glfwInit()) {
        const char* description = nullptr;
        glfwGetError(&description);
        SPDLOG_ERROR("failed to initialize glfw: {}", description);
        return -1; // 실행 종료
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw 윈도우 생성, 실패하면 에러 출력후 종료
    SPDLOG_INFO("Create glfw window");

    // auto(변수 타입을 자동으로 지정할 때 사용) == GLFWwindow*
    auto window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, nullptr, nullptr);

    if (!window) {
        SPDLOG_ERROR("failed to create glfw window");
        glfwTerminate();
        return -1;
    }

	glfwMakeContextCurrent(window);

    // glad를 활용한 OpenGL 함수 로딩
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        SPDLOG_ERROR("failed to initialize glad");
        glfwTerminate();
        return -1;
    }
    auto glVersion = glGetString(GL_VERSION);
    SPDLOG_INFO("OpenGL context version: {}", reinterpret_cast<const char*>(glVersion)); // 드라이브 버전 출력

    // window 생성 직후에는 OnFramebufferSizeChange가 호출되지 않기때문에 첫 호출은 수동으로 생성
    OnFramebufferSizeChange(window, WINDOW_WIDTH, WINDOW_HEIGHT);
    // window frame 크기가 변경되면 OnFramebufferSizeChange 호출
    glfwSetFramebufferSizeCallback(window, OnFramebufferSizeChange);
    // 키보드 이벤트 발생시 OnKeyEvent 호출
    glfwSetKeyCallback(window, OnKeyEvent);

    // glfw 루프 실행, 윈도우 close 버튼을 누르면 정상 종료
    SPDLOG_INFO("Start main loop");
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // state-setting
        glClearColor(1.0f, 0.6f, 0.8f, 1.0f); // window 배경색을 뭘로 clear 할 지
        
        // state-using -> 앞서 설정한 state를 이용
        glClear(GL_COLOR_BUFFER_BIT); 

        // swap 호출
        // frame buffer swap -> 화면에 그림을 그리는 과정
        // 1. back에 그림을 그리고
        // 2. front와 back을 바꿔서 
        // => 그림이 그려지는 과정이 window에서 안 보이도록 
        glfwSwapBuffers(window);
    }

    glfwTerminate();    

    return 0;
}