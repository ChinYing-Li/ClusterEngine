#pragma once
#include <map>
#include <memory>
#include <string>

// forward declaration
class ShaderProgram;
class Texture;

class ResourceManager
{
public:
    ResourceManager();
    ~ResourceManager() = default;
    
    bool texture_exists(const std::string name);
    std::shared_ptr<Texture> retrieve_texture(const std::string name); // might return nullptr
    //void load_texture(const std::string path_to_file);
    /*
    bool shader_exists(const std::string name);
    std::shared_ptr<ShaderProgram> retrieve_shader(const std::string name);
    */
private:
    std::map<std::string, std::shared_ptr<Texture>> m_texmap;
    /*std::map<std::string, std::shared_ptr<ShaderProgram>> m_shadermap;*/
};
