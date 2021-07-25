#version 430 compatible

const float PI = 3.14159265359;
const float PI_INV = 0.31830988618;

in vec2 i_tex_coords;

out vec4 frag_color;

uniform sampler2D u_texture;
uniform vec2 u_tex_dim_inv;
uniform int u_kernel_size;
uniform float u_sigma;
uniform bool u_horizontal;

// Taking reference from https://github.com/cansik/processing-bloom-filter
void main(void)
{
    float kernel_radius = u_kernel_size / 2.0;
    vec2 blur_direction = (u_horizontal) ? vec2(1.0, 0.0) : vec2(0.0, 1.0);

    // Incremental Gaussian Coefficent Calculation (reference: GPU Gems 3 pp. 877 - 889)
    vec3 incremental_gaussian;
    incremental_gaussian.x = 1.0 / (sqrt(2 * PI) * u_sigma);
    incremental_gaussian.y = exp(-0.5 / (u_sigma * u_sigma);
    incremental_gaussian.z = incremental_gaussian.y * incremental_gaussian.y;

    vec4 average = vec4(0.0);
    float coefficient_sum = 0.0;

    // First, sample the center
    average += texture2D(u_texture, i_tex_coords) * incremental_gaussian.x;
    coefficient_sum += incremental_gaussian.x;
    incremental_gaussian.xy *= incremental_gaussian.yz;

    // Second, sample
    for (float i = 1.0; i <= u_kernel_size; i += 1.0)
    {
        average += texture2D(u_texture, i_tex_coords - i * u_tex_dim_inv * blur_direction) * incremental_gaussian.x;
        average += texture2D(u_texture, i_tex_coords + i * u_tex_dim_inv * blur_direction) * incremental_gaussian.x;
        coefficient_sum += 2.0 * incremental_gaussian.x;
        incremental_gaussian.xy *= incremental_gaussian.yz;
    }

    frag_color = average / coefficient_sum;
}
