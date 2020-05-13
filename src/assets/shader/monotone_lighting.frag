in vec3 pos;
in vec3 normal;
in vec3 color;

out vec4 fragcolor;

struct Material
{
    float shininess;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    //vec3 emission;
};

// to avoid switching shaders
struct Light
{
    bool is_enabled;
    bool is_local;
    bool is_spotlight;
    
    vec3 ambient_strength;
    vec3 diffuse_strength;
    vec3 specular_strength;
    
    vec3 color;
    vec3 position;
    
    // directional light property
    vec3 halfvec;
    
    // spotlight properties
    vec3 cone_direction;
    vec3 spot_cos_cutoff;
    vec3 exponent;
    
    vec3 constant_atten;
    vec3 linear_atten;
    vec3 quadratic_atten;
};

const int maxlight = 15;
uniform int numlight;
uniform vec3 eye_direction; // in eyespace, always (0, 0, -1), after using glm::lookat
uniform Material material;
uniform Light lights[maxlight]; // handle multiple light at once??

void main()
{
    vec3 scattered(0.0);
    vec3 reflected(0.0);
    
    for(int i = 0; i < numlight; ++i)
    {
        if(!lights[i].is_enabled) return;
        
        vec3 lightdirection;
        vec3 halfvec;
        float atten = 1.0;
        
        if(lights[i].is_local)
        {
            lightdirection = lights[i].position - pos; // pointing from frag to light
            float lightdis = length(lightdirection);
            lightdirection = normalize(lightdirection);
            float atten_denom = lights[i].constant_atten + lights[i].linear_atten * lightdis + lights[i].quadratic_atten * pow(lightdis, 2);
            atten /= stten_denom;
            
            if(lights[i].is_spotlight)
            {
                float spotcos = dot(lightdirection, light.cone_direction);
                atten *= (spotcos < lights[i].spot_cos_cutoff) ? 0.0 : pow(spotcos, lights[i].exponent);
            }
            
            halfvec = normalize(lightdirection + eye_direction);
        }
        else
        {
            halfvec = lights[i].halfvec;
        }
            
        float diffuse = max(0.0, dot(lightdirection, normal));
        float specular = max(0.0, dot(halfvec, normal));
        if(diffuse == 0.0) specular = 0.0;
        else specular = pow(specular, material.shininess) * material.specular_strength;
            
        scattered += lights[i].ambient_strength * atten;
        scattered += lights[i].color * atten * diffuse;
        reflected += lights[i].color * atten * specular;
    }
    
    vec3 rgb = min(color.rgb * scattered + reflected, vec3(1.0));
    fragcolor = vec4(rgb, 1.0);
    return;
}
