#version 330 core

/* The shader for shading GBuffer's content. */

in vec3 i_position;
in vec3 i_worldposition;
in vec2 i_tex_coords;
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

    bool use_map_ambient;
    bool use_map_diffuse;
    bool use_map_specular;
    bool use_map_normal;
    bool use_map_stencil;
    bool use_map_emission;
    bool use_map_bump;

    sampler2D map_ambient;
    sampler2D map_diffuse;
    sampler2D map_specular;
    sampler2D map_normal;
    sampler2D map_stencil;
    sampler2D map_emission;
    sampler2D map_bump;

    vec2 tiling;
};

uniform vec3 u_eye_position;
uniform mat4 u_model_matrix;
uniform Material u_material;

vec4 sample_tiled(sampler2D tex2D, vec2 tex_coords)
{
    return texture(tex2D, tex_coords * u_material.tiling);
}

vec3 calc_frag_normal(vec2 normalmap_texcoord,
                      vec3 normal,
                      vec3 tangent)
{
    vec3 bitangent = cross(normal, tangent);
    vec3 sampled_normal = sample_tiled(u_material.map_normal, normalmap_texcoord).rgb * 2.0 - 1.0;
    mat3 TBN = mat3(tangent, bitangent, normal);
    return normalize(TBN * sampled_normal);
}

void main(void)
{
    if (u_material.use_map_stencil)
    {
        float sampled_stencil = sample_tiled(u_material.map_stencil, i_tex_coords).r;
        if (sampled_stencil <= 0.5)
        {
            discard;
        }
    }

    vec3 worldposition = i_worldposition;
    vec3 norm = i_normal;

    if (u_material.use_map_normal)
    {
        norm = calc_frag_normal(norm, i_tangent, i_tex_coords);
    }

    norm = normalize(u_model_matriz * vec4(norm, 0.0)).xyz;
    vec3 eye_direction = normalize(u_eye_position - i_worldposition);
    vec3 reflect_direction = normalize(reflect(-eye_direction, norm));

    float specular = 0.0;
    if (u_material.use_map_specular)
    {
        specular = sample_tiled(u_material.map_specular, i_tex_coords).r;
    }

    float bumpness = 1.0;
    if (u_material.use_map_bump)
    {
        bumpness = sample_tiled(u_material.map_bump, i_tex_coords).r;
    }

    // Diffuse
    vec3 color = vec3(1.0);
    if (u_material.use_map_diffuse)
    {
        color = sample_tiled(u_material.map_diffuse, i_tex_coords).rgb;
    }

    vec3 emission = vec3(0.0);
    if (u_material.use_map_emission)
    {
        emission = sample_tiled(u_material.map_emission, i_tex_coords).rgb;
    }

    frag_color = vec4(color, bumpness);
    frag_normal = vec4(norm * 0.5 + 0.5, specular);
    frag_position = vec4(worldposition, 0.0);
    frag_emission = vec4(emission, 0.0);
}
