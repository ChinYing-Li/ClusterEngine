#pragma once

#include <memory>
#include <vector>

#include "camera.h"
#include "framebuffer.h"
#include "globject.h"
#include "Imanagers.h"
#include "renderpass.h"
#include "renderstate.h"
#include "textureregistry.h"

namespace Cluster
{
class Scene;

class PipelineBase
{
public:
    PipelineBase();
    ~PipelineBase();

    void virtual setup(unsigned int width, unsigned int height, Scene& scene) = 0;
    void virtual resize(unsigned int width, unsigned int height);
    void virtual render_scene();
    void virtual render_objects();

    void set_resource_mng(std::unique_ptr<ResourceManager> resource_mng);

    std::unique_ptr<ResourceManager> return_resource_mng() noexcept;
    std::shared_ptr<FrameBuffer> get_current_framebuffer() noexcept;

    void add_pass(std::shared_ptr<RenderPass> pass) noexcept;

    TextureRegistry m_texture_registry;

protected:
    void virtual setup_backbuffers();

    RenderState m_renderstate;

    // If either of resmanager_ptr or windowmanager_ptr is not present,
    // then the pipeline is not valid and should not be used.
    bool is_pipeline_valid = false;
    unsigned int m_win_width, m_win_height;

    // buffers to store transforms loaded by RenderPasses
    glm::mat4 m_project_transform;
    glm::mat4 m_view_transform;
    glm::mat4 m_model_transform;

    std::unique_ptr<ResourceManager> m_resmanager_ptr = nullptr;

    std::vector<std::shared_ptr<GLObejct>> m_objects;
    std::shared_ptr<FrameBuffer> m_current_frambuffer_ptr;
    std::vector<std::shared_ptr<FrameBuffer>> m_back_buffers;
    std::vector<std::shared_ptr<RenderPass>> m_passes;
    Camera m_camera;
};
}
