#pragma once

#include <memory>
#include <vector>

#include "camera.h"
#include "framebuffer.h"
#include "Imanagers.h"
#include "renderpass.h"
#include "textureregistry.h"

namespace Cluster
{
class PipelineBase
{
public:
    PipelineBase();
    ~PipelineBase();

    void set_window_size(glm::vec2 window_size);
    void set_clear_color(glm::vec4 clear_color);

    void set_resource_mng(std::unique_ptr<ResourceManager> resource_mng);
    std::unique_ptr<ResourceManager> return_resource_mng() noexcept;

    std::shared_ptr<FrameBuffer> get_current_framebuffer() noexcept;


    TextureRegistry m_texture_registry;

protected:
    // If either of resmanager_ptr or windowmanager_ptr is not present,
    // then the pipeline is not valid and should not be used.
    bool is_pipeline_valid = false;

    glm::vec2 m_window_size;

    // buffers to store transforms returned by RenderPasses
    glm::mat4 m_project_transform;
    glm::mat4 m_view_transform;
    glm::mat4 m_model_transform;

    std::unique_ptr<ResourceManager> m_resmanager_ptr = nullptr;

    std::shared_ptr<FrameBuffer> m_current_frambuffer_ptr;
    std::vector<std::shared_ptr<RenderPass>> m_passes;
    Camera m_cam;
};
}
