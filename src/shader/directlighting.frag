#version 430 compatibility

/*
 *  The shader for direct lighting in forward shading.
 *  Implementation according to
 *  http://www.codinglabs.net/article_physically_based_rendering_cook_torrance.aspx
 */

#define MAX_LIGHT 200
const float PI = 3.14159265359;
const float PI_INV = 0.31830988618;

in vec3 i_position;
in vec3 i_normal;
in vec2 i_texcoord;

out vec4 frag_color;

// The material to be shadedS
struct Material
{
    vec3 ambient_color;
    vec3 diffuse_color;
    vec3 specular_color;

    float shininess;

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

uniform int num_light;
uniform vec3 eye_position;

uniform Material u_material;
uniform Light u_lights[MAX_LIGHT];

vec4 sample_tiled(sampler2D tex2D, vec2 tex_coords)
{
    return texture2D(tex2D, tex_coords * u_material.tiling);
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

float cos_positive(vec3 lhs, vec3 rhs)
{
    // The contribution
    return clamp(dot(lhs, rhs), 0.0, 1.0);
}


/*
 *  Distribution functions
 *      Phong
 *      Beckman
 *      GGX
 */

float Blinn_Phong(vec3 half_vector, vec3 normal, float roughness)
{
    float h_dot_n = dot(half_vector, normal);
    float roughness_squared = roughness * roughness;
    return pow(h_dot_n, roughness_squared) * PI_INV * 0.5 * (roughness_squared + 2.0);
}

float Beckmann(vec3 half_vector, vec3 normal, float roughness)
{
    float roughness_squared = roughness * roughness;
    float roughness_exp4 = roughness_squared * roughness_squared;
    float h_dot_n = dot(half_vector, normal);
    float r1 = 0.25 / roughness_exp4 / pow(h_dot_n, 4.0);

    float r2 = (h_dot_n * h_dot_n - 1.0) / roughness_exp4 / h_dot_n / h_dot_n;
    return r1 * exp(r2);
}

float GGX(vec3 half_vector, vec3 normal, vec3 direction, float roughness)
{
    float h_dot_n = dot(half_vector, normal);
    float roughness_exp4 = roughness * roughness * roughness * roughness;
    float h_dot_n_squared = h_dot_n * h_dot_n;
    float d = h_dot_n_squared * (roughness_exp4 - 1.0) + 1.0;
    float density = roughness_exp4 * PI_INV;
    return density / (d * d);
}


/*
 *  Fresnel functions
 *      Fresnel_Schlick: Schlick approximation to Fresnel function
 *
 */

vec3 Fresnel_Schlick(vec3 color, float specular, float cos_theta)
{
    float fresnel_0 = mix(vec3(0.04), color.rgb, specular); // Fresnel term at angle 0
    return fresnel_0 + (1.0 - fresnel_0) * pow(1.0 - cos_theta, 5.0);
}


/*
 *  Geometry terms
 *      Schlick
 *      Cook-Torance
 */
float Implicit(vec3 normal, vec3 half_vector, vec3 view_dir, vec3 light_dir)
{
    // half_vector is the half-vector between view_dir and light_dir

}

float Cook_Torrance()
{

}

float Smith()
{

}


/*
 *  Cook-Torrance shading model
 */
vec3 Cook_Torrance_Shading(vec3 normal,
                           vec3 half_vector,
                           vec3 view_dir,
                           vec3 light_dir,
                           vec3 color,
                           float specular,
                           float roughness)
{
    float norm_dot_half = max(0.0, dot(normal, half_vector));
}

void main()
{
    vec3 scattered = vec3(0.0);
    vec3 reflected = vec3(0.0);
    vec3 viewdirection = normalize(eye_position - i_position);

    for(int i = 0; i < num_light; ++i)
    {
        if (!lights[i].is_enabled) return;

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


