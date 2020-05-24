#pragma once
#include <map>
#include <memory>
#include <string>

// forward declaration
class Shader;
class Texture;

class ResourceManager
{
public:
    ResourceManager();
    ~ResourceManager() = default;
    
    bool texture_exists(const std::string name);
    std::shared_ptr<Texture> retrieve_texture(const std::string name); // might return nullptr

    
    bool shader_exists(const std::string name);
    std::shared_ptr<Shader> retrieve_shader(const std::string name);
    
private:
    void write_error_log(const std::string resourcename);
    void init_texture();
    void init_shader();
    
    std::map<std::string, std::shared_ptr<Texture>> m_texmap;
    std::map<std::string, std::shared_ptr<Shader>> m_shadermap;
};
