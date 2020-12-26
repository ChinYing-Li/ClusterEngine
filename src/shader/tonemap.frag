#version 430 compatible

in vec3 i_coords;
out vec3 frag_color;

uniform int u_curve;
uniform float u_exposure;
uniform sampler2D u_input;

// Simple Reinhard tonemapping, nothing fancy
vec3 Reinhard(vec3 color)
{
    return color / (1.0 + color);
}

// Norkowicz, 2017
// Reference: https://knarkowicz.wordpress.com/2016/01/06/aces-filmic-tone-mapping-curve/
const float a = 2.51;
const float b = 0.03;
const float c = 2.43;
const float d = 0.59;
const float e = 0.14;

vec3 ACES(vec3 color)
{
    vec3 result = (a * color + b) * color;
    result /= (c * color + d) * color + e;
    return clamp(result, 0.0, 1.0);
}

// Hajime Uchimura, 2017, "HDR, Theory and Practice"
// Gran Turismo curve
vec3 Gran_Turismo(vec3 color)
{
    return color;
}

void main(void)
{
    vec3 sampled_color = texture2D(u_input, i_coords).rgb;
    switch (u_curve)
    {
        case 0:
            frag_color = Reinhard(sampled_color);
            return;
        case 1:
            frag_color = ACES(sampled_color);
            return;
        case 2:
            // TODO: implement Gran Turismo curve
            return;
    }

    ;
}
