#include "../../foundation/texture.h"
#include "resourcemanager.h"

#include <iostream>
ResourceManager::ResourceManager()
{
    //load textures
    std::vector<std::string> files = {
        "right.jpg", "left.jpg",
        "bottom.jpg", "top.jpg",
        "front.jpg", "back.jpg"
    };
    std::string n = "skybox";
    m_texmap[n] = std::dynamic_pointer_cast<Texture>(std::make_shared<TextureCubemap>(n, files));
    files = {"bricks2.jpg"};
    n = "brick";
    m_texmap[n] = std::dynamic_pointer_cast<Texture>(std::make_shared<Texture2D>(n, files));
    std::cout << "properly constructed" << std::endl;
}

bool ResourceManager::texture_exists(const std::string texname)
{
    return true;
}

std::shared_ptr<Texture> ResourceManager::retrieve_texture(const std::string texname)
{
    auto it = m_texmap.find(texname);
    if(it == m_texmap.end())
    {
        write_error_log(texname);
        return nullptr;
    }
        
    std::cout << texname << std::endl;
    return m_texmap[texname];
    
}

void ResourceManager::write_error_log(const std::string resourcename)
{
    std::cout << "Failed to retrive " << resourcename << "..." << std::endl;
    return;
}
/*
bool ResourceManager::shader_exists(const std::string shadername)
{
    auto it = m_shadermap.find(shadername);
    if(it == m_shadermap.end()) return false;
    return true;
}

std::shared_ptr<ShaderProgram> ResourceManager::retrieve_shader(const std::string shadername)
{
    if(shader_exists(shadername)) return m_shadermap[shadername];
    return nullptr;
}
*/
