#pragma once

#include <memory>
#include <vector>

#include "camera.h"
#include "framebuffer.h"
#include "globject.h"
#include "Imanagers.h"
#include "renderpass.h"
#include "renderstate.h"
#include "shaderregistry.h"
#include "tonemappass.h"

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

    const FrameBuffer* get_current_framebuffer() const noexcept;

    void set_hdr_pass(const std::shared_ptr<RenderPass> pass, const int index = -1);
    void set_ldr_pass(const std::shared_ptr<RenderPass> pass, const int index = -1);
    void set_tonemap_pass();

    void print_hdr_pass_info() const noexcept;
    void print_ldr_pass_info() const noexcept;

protected:
    void virtual setup_backbuffers();

    RenderState m_renderstate;
    ShaderRegistry m_registry;

    // If either of resmanager_ptr or windowmanager_ptr is not present,
    // then the pipeline is not valid and should not be used.
    bool is_pipeline_valid = false;
    unsigned int m_width, m_height;
    Camera m_camera;

    // buffers to store transforms loaded by RenderPasses
    glm::mat4 m_project_transform;
    glm::mat4 m_view_transform;
    glm::mat4 m_model_transform;

    std::unique_ptr<ResourceManager> m_resmanager_ptr = nullptr;
    std::vector<GLObejct*> m_objects;

    FrameBuffer m_current_frambuffer;

    // We don't have to use smart pointers as there's no ownership involved
    std::vector<FrameBuffer*> m_hdr_back_buffers;
    std::vector<FrameBuffer*> m_ldr_back_buffers;

    std::vector<std::shared_ptr<RenderPass>> m_hdr_passes;
    std::vector<std::shared_ptr<RenderPass>> m_ldr_passes;
    std::shared_ptr<TonemapPass> m_tonemappass;

    void set_pass(const std::shared_ptr<RenderPass> pass, std::vector<std::shared_ptr<RenderPass>>& passes, const int index = -1);
    void print_info(const std::vector<std::shared_ptr<RenderPass>>& passes) const noexcept;
    void reset_backbuffer(std::vector<FrameBuffer*>& back_buffer);
};
}
