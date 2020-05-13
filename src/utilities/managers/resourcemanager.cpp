#include "../../foundation/texture.h"
#include "resourcemanager.h"

ResourceManager::ResourceManager()
{
    //load textures
    std::vector<std::string> skybox_files = {
        "right.jpg", "left.jpg",
        "bottom.jpg", "top.jpg",
        "front.jpg", "back.jpg"
    };
    std::string n = "skybox";
    auto ptr = std::shared_ptr<TextureCubemap> (new TextureCubemap(n, skybox_files));
    m_texmap[n] = std::dynamic_pointer_cast<Texture>(ptr);;
}

bool ResourceManager::texture_exists(const std::string texname)
{
    auto it = m_texmap.find(texname);
    if(it == m_texmap.end()) return false;
    return true;
}

std::shared_ptr<Texture> ResourceManager::retrieve_texture(const std::string texname)
{
    if(texture_exists(texname)) return m_texmap[texname];
    return nullptr;
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
