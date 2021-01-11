#pragma once

#include "framebuffer.h"
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
    void virtual render_scene() override;
    void virtual render_objects() override;

    void apply_direct_lighting(Scene& sc);
    void post_processing(Scene& sc);

protected:
  void virtual render_framebuffer(FrameBuffer& framebuffer);
  void render_skybox();

  FrameBuffer m_framebuffer;

};

}
