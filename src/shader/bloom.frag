#version 430 core

in vec2 i_tex_coords;
in vec3 i_position;

out vec4 o_frag_color;

uniform sampler2D u_texture;
uniform float u_threshold;

const vec3 radiance2luminance = vec3(0.299, 0.587, 0.114);

void main(void)
{
    vec3 radiance = textureLod(u_texture, i_tex_coords, 1).rgb;
    float luminance = dot(radiance2luminance, radiance);
    o_frag_color = (luminance > u_threshold) ? vec4(radiance, 1.0) : vec4(0.0, 0.0, 0.0, 1.0);
}
