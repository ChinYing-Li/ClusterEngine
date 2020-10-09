#pragma once

#include<vector>

#include "light.h"
#include "skybox.h"

namespace Cluster{

/**
 * @brief This class contains static object that are to be rendered.
 */
class Scene
{
public:
  Scene();

  void set_skybox(std::shared_ptr<Skybox> skybox, bool override);
  void add_light(std::shared_ptr<Light> light, int index);
  const std::vector<std::shared_ptr<Light>>& get_all_lights() const;

private:
  std::shared_ptr<Skybox> m_skybox;
  std::vector<std::shared_ptr<Light>> m_lights;
};
} // namespace Cluster

