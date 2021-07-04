#pragma once

#include <vector>

#include "light.h"
#include "skybox.h"

namespace Cluster
{
class Forward;
class Deferred;

/**
 * @brief This class contains static object that are to be rendered.
 */
class Scene
{
public:
  Scene();

  void set_skybox(std::shared_ptr<Skybox> skybox, bool override);
  void add_light(std::shared_ptr<Light> light, int index);
  void add_object(std::shared_ptr<Renderable> object, int index);
  const Skybox* get_skybox() const;
  const std::vector<std::shared_ptr<Light>>& get_light_vec() const;
  const std::vector<std::shared_ptr<Renderable>>& get_object_vec() const;

private:
  std::shared_ptr<Skybox> m_skybox;
  std::vector<std::shared_ptr<Light>> m_lights;
  std::vector<std::shared_ptr<Renderable>> m_objects;
};
} // namespace Cluster

