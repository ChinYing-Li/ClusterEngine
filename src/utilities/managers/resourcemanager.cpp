#include "includes/glfoundation/texture.h"
#include "includes/glfoundation/shader.h"
#include "src/utilities/managers/resourcemanager.h"

#include <iostream>
ResourceManager::ResourceManager()
{
    init_texture();
    init_shader();
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
        std::vector<std::string> temp_files = {texname};
        m_texmap[texname] = std::dynamic_pointer_cast<Texture>(std::make_shared<Texture2D>(texname, temp_files));
    }
        
    std::cout << texname << std::endl;
    return m_texmap[texname];
    
}

void ResourceManager::write_error_log(const std::string resourcename)
{
    std::cout << "Failed to retrive " << resourcename << "..." << std::endl;
    return;
}

bool ResourceManager::shader_exists(const std::string shadername)
{
    auto it = m_shadermap.find(shadername);
    if(it == m_shadermap.end()) return false;
    return true;
}

std::shared_ptr<Shader> ResourceManager::retrieve_shader(const std::string shadername)
{
    if(shader_exists(shadername)) return m_shadermap[shadername];
    return nullptr;
}

void ResourceManager::init_texture()
{
    //load textures
    std::vector<std::string> files = {
        "right.jpg", "left.jpg",
        "bottom.jpg", "top.jpg",
        "front.jpg", "back.jpg"
    };
    std::vector<std::string> n = {"skybox"};
    m_texmap[n[0]] = std::dynamic_pointer_cast<Texture>(std::make_shared<TextureCubemap>(n[0], files));
    std::vector<std::vector<std::string>> tex_files = {{"bricks2.jpg"}, {"rock_road.jpg"}, {"grass2.jpg"}};
    n = {"brick.jpg", "rock_road.jpg", "grass2.jpg"};
    assert(tex_files.size() == n.size());
    
    for(int i = 0; i < tex_files.size(); ++i)
    {
        m_texmap[n[i]] = std::dynamic_pointer_cast<Texture>(std::make_shared<Texture2D>(n[i], tex_files[i]));
    }
}

void ResourceManager::init_shader()
{
    std::vector<std::vector<std::string>> files = {
        {"monotone.vert", "monotone.frag", ""},
        {"skybox.vert", "skybox.frag", ""},
        {"singletex.vert", "singletex.frag", ""},
        {"model.vert", "model.frag", "" },
        {"multiple_lighting.vert", "multiple_lighting.frag", ""},
        {
            "instanced_w_lighting.vert", "instanced_w_lighting.frag", ""
        }
    };
    std::vector<std::string> name = {
        "monotone", "skybox", "texture", "model", "lighting", "instance_w_lighting"
    };
    assert(name.size() == files.size());
    for(int i = 0; i < files.size(); ++i)
    {
        m_shadermap[name[i]] = std::make_shared<Shader>(files[i][0], files[i][1], files[i][2], name[i]);
    }
    return;
}

