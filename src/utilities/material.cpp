#include <iostream>
#include <fstream>
#include <sstream>

#include "material.h"
#include "src/glfoundation/shader.h"

namespace Cluster
{
extern objl::Loader g_obj_loader;
const unsigned int N_MapType = Material::BUMP - Material::K_AMBIENT + 1;

Material::Material(objl::Material& objl_material):
  m_objl_material(objl_material),
  m_use_texture_map(N_MapType, 0),
  m_map_ptr(N_MapType, nullptr)
{

}

void Material::set_uniform(const Shader& shader)
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
