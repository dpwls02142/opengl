#version 330 core
uniform vec4 color; // uniform == shader에 적용하는 global value
out vec4 fragColor;

void main() {
    fragColor = color;
}