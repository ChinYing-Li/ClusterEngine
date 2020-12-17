
#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

struct Material
{
    float shininess;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    //vec3 emission;
    bool use_map_Ka;
    bool use_map_Kd;
    bool use_map_Ks;
    bool use_map_Ns;
    bool use_map_d;
    bool use_map_bump;
};

uniform sampler2D map_Ka;
uniform sampler2D map_Kd;
uniform sampler2D map_Ks;
uniform sampler2D map_Ns;
uniform sampler2D map_d;
uniform sampler2D map_bump;
uniform Material material;

void main()
{
    FragColor = texture(map_Kd, TexCoords);
}
