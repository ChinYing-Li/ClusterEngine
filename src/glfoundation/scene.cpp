#include "scene.h"
namespace Cluster{
Scene::Scene():
  m_skybox(nullptr),
  m_lights(0, nullptr)
{

}

void Scene::
set_skybox(std::shared_ptr<Skybox> skybox,
           bool override)
{
  if (m_skybox != nullptr && !override)
  {
    return;
  }

  m_skybox = skybox;
}

void Scene::
add_light(std::shared_ptr<Light> light, int index = -1)
{
  // If the provided index is negative, append light to m_lights
  if ( index < 0 || index >= m_lights.size() ) {
    m_lights.push_back(light);
  }
  else // Otherwise, override
  {
    m_lights[index] = light;
  }
}


const std::vector<std::shared_ptr<Light>>& Scene::
get_all_lights() const
{
  return m_lights;
}

} // namespace Cluster

