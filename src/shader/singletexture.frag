#version 330 core

in vec2 i_tex_coords;

out vec4 fragColor;
uniform sampler2D u_texture;

void main()
{
    frag_color = texture(u_texture, i_tex_coords);
}
