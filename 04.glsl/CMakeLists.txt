# cmake build setting
# (vs code 기준) ctrl + shift + p 단축키를 누른 후
# build를 검색해서 바로 build 할 수도 있음. == F7
cmake_minimum_required(VERSION 3.14)

set(PROJECT_NAME glsl_opengl)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# glfw로 윈도우를 생성하기 위함.
set(WINDOW_NAME "GLSL example")
set(WINDOW_WIDTH 960)
set(WINDOW_HEIGHT 540)

project(${PROJECT_NAME})
# cmake로 파일들을 build하기 위해해
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/common.cpp src/common.h
    src/shader.cpp src/shader.h
    src/program.cpp src/program.h
    src/context.cpp src/context.h
    src/buffer.cpp src/buffer.h
    src/vertex_layout.cpp src/vertex_layout.h
)

# 라이브러리 관련 파일은 Dependency.cmake로 따로 관리하여 include.
include(Dependency.cmake)

# 우리 프로젝트에 include / lib 관련 옵션 추가
target_include_directories(${PROJECT_NAME} PUBLIC ${DEP_INCLUDE_DIR}) # 프로젝트에 dependency dir을 추가
target_link_directories(${PROJECT_NAME} PUBLIC ${DEP_LIB_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${DEP_LIBS})

# define으로 이름을 적는 것과 똑같은 효과.
target_compile_definitions(${PROJECT_NAME} PUBLIC
    WINDOW_NAME="${WINDOW_NAME}"
    WINDOW_WIDTH=${WINDOW_WIDTH}
    WINDOW_HEIGHT=${WINDOW_HEIGHT}
)

# Dependency들이 먼저 build 될 수 있게 관계 설정
add_dependencies(${PROJECT_NAME} ${DEP_LIST})

# utf-8 관련 오류 해결
target_compile_options(${PROJECT_NAME} PUBLIC "/utf-8")

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/04.glsl"
)