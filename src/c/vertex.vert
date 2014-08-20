#version 110

attribute vec2 vertPos;

void main() {
     gl_Position = vec4(vertPos, 0, 1);
}