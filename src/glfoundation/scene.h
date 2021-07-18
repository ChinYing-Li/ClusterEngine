#pragma once

#include <vector>

#include "glfoundation/light.h"
#include "glfoundation/cubemap.h"

namespace fs = std::experimental::filesystem;

namespace Cluster
{
/**
 * @brief This class contains static object that are to be rendered.
 */
class Scene
{
public:
  Scene() = default;
  ~Scene();
  Scene(fs::path& scene_path);

  bool create_skybox(std::vector<fs::path>& texture_path);
  void add_light(std::shared_ptr<Light> light, int index);
  void add_object(std::shared_ptr<Renderable> object, int index);
  const Cubemap& get_skybox_ref() const;
  const std::vector<std::shared_ptr<Light>>& get_light_vec() const;
  const std::vector<std::shared_ptr<Renderable>>& get_object_vec() const;

private:
  std::unique_ptr<Cubemap> m_skybox = nullptr;
  std::vector<std::shared_ptr<Light>> m_lights;
  std::vector<std::shared_ptr<Renderable>> m_objects;
};
} // namespace Cluster

