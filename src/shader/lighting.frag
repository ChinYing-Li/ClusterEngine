#version 330 core

in vec3 position;
in vec3 normal;
in vec2 texcoord;

out vec4 frag_color;

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

struct Light
{
    bool is_enabled;
    bool is_local;
    bool is_spotlight;

    vec3 ambient_strength;
    vec3 color;

    vec3 position;

    vec3 direction;

    vec3 cone_direction;
    float spot_cos_cutoff;
    float exponent;

    float constant_atten;
    float linear_atten;
    float quadratic_atten;
};

#define MAX_LIGHT 3
#define PI 3.14159265359

uniform int numlight;
uniform vec3 eye_position;

uniform Material material;
uniform Light lights[MAX_LIGHT];

//////////////////////////////
vec4 sample_tiled(vec2 _texture_coordinates, sampler2D _texture)
{
    return texture(_texture, _texture_coordinates * material,tiling);
}


void main()
{
    vec3 scattered = vec3(0.0);
    vec3 reflected = vec3(0.0);
    vec3 viewdirection = normalize(eye_position - position);

    for(int i = 0; i < numlight; ++i)
    {
        if(!lights[i].is_enabled) return;

        vec3 lightdirection;
        float atten = 1.0;

        if(lights[i].is_local)
        {
            lightdirection = normalize(lights[i].position - position); // pointing from frag to light
            float lightdis = length(lights[i].position - position);

            float atten_denom = lights[i].constant_atten + lights[i].linear_atten * lightdis + lights[i].quadratic_atten * lightdis * lightdis;
            atten /= atten_denom;

            if(lights[i].is_spotlight)
            {
                float spotcos = dot(lightdirection, lights[i].cone_direction);
                atten *= (spotcos < lights[i].spot_cos_cutoff) ? 0.0 : pow(spotcos, lights[i].exponent);
            }

        }
        else
        {
            lightdirection = -normalize(lights[i].direction);
        }

        float diffuse_weight = max(0.0, dot(lightdirection, normal));

        vec3 reflectdirection = normalize(reflect(-lightdirection, normal));
        float specular_weight = max(0.0, dot(reflectdirection, viewdirection));

        if(diffuse_weight == 0.0) specular_weight = 0.0;
        else specular_weight = pow(specular_weight, material.shininess);

        scattered += lights[i].ambient_strength * atten;

        if(material.use_map_Diffuse)
        {
            vec3 diff_buffer = vec3(texture(material.map_Diffuse, texcoords));
            scattered += lights[i].color * diff_buffer * atten * diffuse_weight;
        }
        else
        {
            scattered += lights[i].color * material.diffuse_color * atten * diffuse_weight;
        }

        if(material.use_map_Specular)
        {
            vec3 refl_buffer = vec3(texture(material.map_Specular, texcoord));
            reflected += lights[i].color * refl_buffer * atten * specular_weight;
        }
        else
        {
            reflected += lights[i].color * material.specular_color * atten * specular_weight;
        }
    }

    vec3 rgb = min(scattered + reflected, vec3(1.0));
    frag_color = vec4(rgb, 1.0);
    return;
}


