#version 330 core

in vec2 i_tex_coords;
in vec3 i_position;
in vec3 i_worldposition;
in vec3 i_normal;
in vec3 i_tangent;

out vec4 frag_color;
out vec4 frag_position;
out vec4 frag_normal;
out vec4 frag_emission;

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

vec4
vec3 calc_frag_normal(vec2 normalmap_texcoord,
                      vec3 normal,
                      vec3 tangent)
{

}

void main(void)
{
    gl_FragColor = texture2D(qt_Texture0, qt_TexCoord0.st);
}
