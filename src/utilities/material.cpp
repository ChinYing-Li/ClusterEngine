#include <iostream>
#include <fstream>
#include <sstream>

#include "material.h"
#include "src/glfoundation/shader.h"
#include "src/glfoundation/texturegenerator.h"

namespace Cluster
{
extern objl::Loader g_obj_loader;
const unsigned int N_MapType = Material::BUMP - Material::K_AMBIENT + 1;

Material::
Material(objl::Material& objl_material, fs::path obj_root_dir):
  m_objl_material(objl_material),
  m_map_ptr(N_MapType, nullptr)
{
  fs::path texture_path;
  if (!m_objl_material.map_Ka.empty())
  {
    texture_path = obj_root_dir / m_objl_material.map_Ka;
    m_map_ptr[K_AMBIENT] = load_texture_from_file(texture_path, Texture::LDR);
  }

  if (!m_objl_material.map_Kd.empty())
  {
    texture_path = obj_root_dir / m_objl_material.map_Kd;
    m_map_ptr[K_DIFFUSE] = load_texture_from_file(texture_path, Texture::LDR);
  }

  if (!m_objl_material.map_Ks.empty())
  {
    texture_path = obj_root_dir / m_objl_material.map_Ks;
    m_map_ptr[K_SPECULAR] = load_texture_from_file(texture_path, Texture::LDR);
  }

  if (!m_objl_material.map_Ns.empty())
  {
    texture_path = obj_root_dir / m_objl_material.map_Ns;
    m_map_ptr[N_SPECULAR] = load_texture_from_file(texture_path, Texture::LDR);
  }

  if (!m_objl_material.map_d.empty())
  {
    texture_path = obj_root_dir / m_objl_material.map_d;
    m_map_ptr[ALPHA] = load_texture_from_file(texture_path, Texture::LDR);
  }

  if (!m_objl_material.map_bump.empty())
  {
    texture_path = obj_root_dir / m_objl_material.map_bump;
    m_map_ptr[BUMP] = load_texture_from_file(texture_path, Texture::LDR);
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
