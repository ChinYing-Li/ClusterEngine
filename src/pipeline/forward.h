#pragma once

#include "glfoundation/framebuffer.h"
#include "glfoundation/gbuffer.h"
#include "glfoundation/renderstate.h"
#include "glfoundation/shader.h"
#include "glfoundation/texturemanager.h"

#include "pipelinebase.h"

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
    ~Forward(){};

    void setup(unsigned int width, unsigned int height, Scene& scene) override;
    void resize(unsigned int width, unsigned int height) override;
    void render_scene(const Shader& shader, Scene& scene) override;
    void render_objects(const Shader& shader, const Scene& scene) override;
    void render_skybox(Scene& scene) override;
    void update_frame(Scene& scene) override;

    void apply_direct_lighting(Scene& scene);
    void post_processing(const Scene& scene);
    const static glm::vec4 M_CLEAR_COLOR;

protected:
  void render_framebuffer(FrameBuffer& framebuffer);
  FrameBuffer m_framebuffer;
};

}
