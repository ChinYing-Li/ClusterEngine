#version 330 core

in vec3 i_position;
out vec4 frag_color;

uniform samplerCube skybox;

void main()
{
    gl_FragDepth = 1;
    frag_color = texture(skybox, i_position);
}
