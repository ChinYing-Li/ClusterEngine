#version 330 core

in vec2 TexCoords;
out vec4 FragColor;

struct Material
{
    vec3 ambient_color;
    vec3 diffuse_color;
    vec3 specular_color;

    bool use_map_Ambient;
    bool use_map_Diffuse;
    bool use_map_Specular;
    bool use_map_Stencil;
    bool use_map_Emission;
    bool use_map_Bump;

    sampler2D map_Ambient;
    sampler2D map_Diffuse;
    sampler2D map_Specular;
    sampler2D map_Stencil;
    sampler2D map_Emission;
    sampler2D map_Bump;
};

uniform Material material;

void main(void)
{
    gl_FragColor = texture2D(qt_Texture0, qt_TexCoord0.st);
}
