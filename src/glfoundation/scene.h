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
  Scene();
  ~Scene();
  Scene(fs::path& scene_path);

  bool create_skybox(std::vector<fs::path>& texture_path);
  void add_light(std::shared_ptr<Light> light, int index);
  void add_object(std::shared_ptr<Renderable> object, int index);
  Cubemap* get_skybox();
  unsigned int light_count() const;
  unsigned int object_count() const;
  std::shared_ptr<Light> get_light(const unsigned int index);
    std::shared_ptr<Renderable> get_object(const unsigned int index);

private:
    std::vector<std::shared_ptr<Light>> m_lights;
    std::vector<std::shared_ptr<Renderable>> m_objects;
  Cubemap* m_skybox;

};
} // namespace Cluster

