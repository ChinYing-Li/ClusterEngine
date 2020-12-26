in vec2 i_tex_coords;

out vec4 frag_color;

uniform sampler2D u_texture;
uniform float u_gamma;
const vec3 gamma_inv = vec3(1.0 / u_gamma);

vec3 Gamma_Correction(vec3 color)
{
    return pow(color, gamma_inv);
}

void main(void)
{
    vec3 color = texture2D(u_texture, i_tex_coords);
    return vec4(Gamma_Correction(color), 1.0);
}
