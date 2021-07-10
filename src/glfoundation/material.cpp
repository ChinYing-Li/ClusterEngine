#include <iostream>
#include <fstream>
#include <sstream>

#include "glfoundation/material.h"
#include "glfoundation/shader.h"
#include "glfoundation/texturemanager.h"

namespace Cluster
{
extern objl::Loader g_obj_loader;
const unsigned int N_MapType = Material::BUMP - Material::K_AMBIENT + 1;

Material::
Material(objl::Material& objl_material, fs::path obj_root_dir):
  m_objl_material(objl_material),
  m_textures(N_MapType, TextureManager::generate_ldr_texture(0, 0))
{
  fs::path texture_path;
  if (!m_objl_material.map_Ka.empty())
  {
    texture_path = obj_root_dir / m_objl_material.map_Ka;
    m_textures[K_AMBIENT] = TextureManager::load_texture2d_from_file(texture_path, Texture::LDR);
  }

  if (!m_objl_material.map_Kd.empty())
  {
    texture_path = obj_root_dir / m_objl_material.map_Kd;
    m_textures[K_DIFFUSE] = TextureManager::load_texture2d_from_file(texture_path, Texture::LDR);
  }

  if (!m_objl_material.map_Ks.empty())
  {
    texture_path = obj_root_dir / m_objl_material.map_Ks;
    m_textures[K_SPECULAR] = TextureManager::load_texture2d_from_file(texture_path, Texture::LDR);
  }

  if (!m_objl_material.map_Ns.empty())
  {
    texture_path = obj_root_dir / m_objl_material.map_Ns;
    m_textures[N_SPECULAR] = TextureManager::load_texture2d_from_file(texture_path, Texture::LDR);
  }

  if (!m_objl_material.map_d.empty())
  {
    texture_path = obj_root_dir / m_objl_material.map_d;
    m_textures[ALPHA] = TextureManager::load_texture2d_from_file(texture_path, Texture::LDR);
  }

  if (!m_objl_material.map_bump.empty())
  {
    texture_path = obj_root_dir / m_objl_material.map_bump;
    m_textures[BUMP] = TextureManager::load_texture2d_from_file(texture_path, Texture::LDR);
  }
}

void Material::bind(const Shader& shader)
{
  if(m_textures[K_AMBIENT].is_initialized()) {
    m_textures[K_AMBIENT].bind(Texture::ALBEDO);
  }
}

void Material::set_uniform(const Shader& shader) const
{
  shader.set_uniform3f("u_material.ambient_color",
                       m_objl_material.Ka.X, m_objl_material.Ka.Y, m_objl_material.Ka.Z);
  shader.set_uniform3f("u_material.diffuse_color",
                       m_objl_material.Kd.X, m_objl_material.Kd.Y, m_objl_material.Kd.Z);
  shader.set_uniform3f("u_material.specular_color",
                       m_objl_material.Ks.X, m_objl_material.Ks.Y, m_objl_material.Ks.Z);
  shader.set_uniform1f("u_material.shininess",
                       m_objl_material.Ns);
  return;
}
}
