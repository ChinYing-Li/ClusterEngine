in vec2 i_texcoords;

struct Material
{
    vec3 ambient_color;
    vec3 diffuse_color;
    vec3 specular_color;

    float shininess;

    bool use_map_ambient;
    bool use_map_diffuse;
    bool use_map_specular;
    bool use_map_stencil;
    bool use_map_emission;
    bool use_map_bump;

    sampler2D map_ambient;
    sampler2D map_diffuse;
    sampler2D map_specular;
    sampler2D map_stencil;
    sampler2D map_emission;
    sampler2D map_bump;

    vec2 tiling;
};

uniform Material u_material;

vec4 sample_tiled(sampler2D tex2D, vec2 tex_coords)
{
    return texture(tex2D, tex_coords * u_material.tiling);
}

void main()
{
    if (u_material.use_map_stencil) {
        float sampled_stencil = sample_tiled(u_material.map_stencil, i_texcoords).r;
        if (sampled_stencil <= 0.5) {
            discard;
        }
    }
}
