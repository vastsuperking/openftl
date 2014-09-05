#version 110

attribute vec2 vertPos;
attribute vec2 texCoord;

varying vec2 fragTexCoord;

void main() {
     fragTexCoord = texCoord;
     gl_Position = vec4(vertPos, 0, 1);
}