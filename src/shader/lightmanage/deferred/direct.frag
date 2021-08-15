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
in vec2 i_texcoord;

out vec4 frag_color;

// The texture maps from the GBuffer
uniform sampler2D u_albedo_map;
uniform sampler2D u_normal_map;
uniform sampler2D u_position_map;
uniform sampler2D u_emission_map;

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

uniform int u_num_light;
uniform vec3 u_eye_position;

uniform Material u_material;
uniform Light u_lights[MAX_LIGHT];

vec4 sample_tiled(sampler2D tex2D, vec2 tex_coords)
{
    return texture2D(tex2D, tex_coords * u_material.tiling);
}

vec3 to_linear(vec3 gamma_color)
{
    return pow(gamma_color, vec3(2.2));
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
    vec4 albedo = texture(u_albedo_map, i_texcoord);
    vec4 normal = texture(u_normal_map, i_texcoord);
    vec4 position = texture(u_position_map, i_texcoord);
    vec4 emission = texture(u_emission_map, i_texcoord);

    vec3 base_color = to_linear(albedo.rgb);
    float roughness = albedo.w;

    vec3 normal_vec = normalize(normal.rgb * 2 - 1.0);
    float metalness = normal.w;

    vec3 position_vec = position.rgb;
    vec3 eye_vec = normalize(u_eye_position - position_vec);
    vec3 reflect_vec = normalize(reflect(-eye_vec, normal_vec));


    for(int i = 0; i < u_num_light; ++i)
    {
        if (!lights[i].is_enabled) return;

        switch(lights[i].)
        vec4 shadow_matrix = 0;
    }
}


