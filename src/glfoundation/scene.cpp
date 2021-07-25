#include <boost/log/trivial.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>

#include "scene.h"

namespace ptree = boost::property_tree;

namespace Cluster {
Scene::
Scene():
  m_skybox(nullptr),
  m_lights(0, nullptr)
{

}

Scene::
~Scene()
{

}

Scene::Scene(fs::path& scene_path)
{
  // BOOST_TRIVIAL_LOG(info) << "Loading scene from:" << scene_path;
  ptree::ptree root;
  try
  {
    ptree::read_json(scene_path, root);
  }
  catch (const ptree::ptree_error &e)
  {
    std::cerr << "Property tree error: " << e.what() << std::endl;
  }
}

bool Scene::
create_skybox(std::vector<fs::path>& texture_path)
{
  GLfloat skybox_vert_buf[] =
          { -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            -1.0f,  1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f,  1.0f
          };

  m_skybox = std::make_unique<Cubemap>(GL_TRIANGLES, 6 * 6, skybox_vert_buf);
  bool success = m_skybox->initialize_texture(texture_path);
}

void Scene::
add_light(std::shared_ptr<Light> light, int index = -1)
{
  // If the provided index is negative, append light to m_lights
  if (index >= m_lights.size() ) {
    m_lights.push_back(light);
  }
  else if (index >= 0) // Otherwise, override
  {
    m_lights[index] = light;
  }
}

Cubemap* Scene::
get_skybox() const
{
  return m_skybox.get();
}


const std::vector<std::shared_ptr<Light>>& Scene::
get_light_vec() const
{
  return m_lights;
}

const std::vector<std::shared_ptr<Renderable>>& Scene::
get_object_vec() const
{
  return m_objects;
}

} // namespace Cluster

