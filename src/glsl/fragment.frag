#version 110

uniform vec4 color;
uniform sampler2D diffuse;

varying vec2 fragTexCoord;


void main() {
    gl_FragColor = color * texture2D(diffuse, fragTexCoord);
}