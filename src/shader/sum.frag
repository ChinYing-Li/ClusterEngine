#version 430 compatible

uniform int u_num_textures;
uniform sampler2D u_textures[10];
uniform float u_weights[10];

in vec3 i_position;
in vec2 i_tex_coords;

out vec4 frag_color;

void main(void)
{
    vec3 color = vec3(0.0);

    for (int i = 0; i < u_num_textures; ++i)
    {
        color += texture2D(u_textures[i], i_position).rgb * u_weights[i];
    }

    frag_color = vec4(color, 1.0);
}
