#pragma once

#include "glfoundation/framebuffer.h"
#include "gbuffer.h"
#include "pipelinebase.h"
#include "renderstate.h"
#include "shader.h"

namespace Cluster
{

class Scene;

/**
 * @brief The Forward Renderer class
 */
class Forward : public PipelineBase
{
public:
    Forward() = delete ;
    Forward(const Scene& scene);
    ~Forward();

    void virtual setup(unsigned int width, unsigned int height, Scene& scene) override;
    void virtual resize(unsigned int width, unsigned int height) override;
    void virtual render_scene(const Shader& shader, const Scene& scene) override;
    void virtual render_objects(const Shader& shader, const Scene& scene) override;
    void virtual update_frame(const Scene& scene) override;

    void apply_direct_lighting(const Scene& scene);
    void post_processing(const Scene& scene);
    const static glm::vec4 M_CLEAR_COLOR;

protected:
  void virtual render_framebuffer(const FrameBuffer& framebuffer);
  void render_skybox(const Scene& scene, Camera& cam);

  FrameBuffer m_framebuffer;
};

}
