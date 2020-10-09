in vec2 texcoords;

struct Material
{
    vec3 ambient_color;
    vec3 diffuse_color;
    vec3 specular_color;

    float shininess;

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

    vec2 tiling;
};

uniform Material material;

vec4 sample_tiled(vec2 _texture_coordinates, sampler2D _texture)
{
    return texture(_texture, _texture_coordinates * material,tiling);
}

void main()
{
    if (material.use_map_Stencil) {
        float _sample = sample_tiled(material.map_Stencil, texcoords).r;
        if (_sample != 1) {
            discard;
        }
    }
}
