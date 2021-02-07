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
    void virtual render_scene(const Shader& shader, const Scene& scene);
    void virtual render_objects(const Shader& shader, const Scene& scene);
    void virtual update_frame(const Scene& scene);

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
    // TODO: Camera should be a member of the Scene class
    Camera m_camera;

    // buffers to store transforms loaded by RenderPasses
    glm::mat4 m_project_transform;
    glm::mat4 m_view_transform;
    glm::mat4 m_model_transform;
    std::vector<Renderable*> m_objects;

    FrameBuffer m_hdr_framebuffer;
    FrameBuffer m_ldr_framebuffer;

    // We don't have to use smart pointers as there's no ownership involved
    std::vector<FrameBuffer> m_hdr_back_buffers;
    std::vector<FrameBuffer> m_ldr_back_buffers;
    std::map<Shader::Usage, std::unique_ptr<Shader>> m_shaders;

    std::vector<std::shared_ptr<RenderPass>> m_hdr_passes;
    std::vector<std::shared_ptr<RenderPass>> m_ldr_passes;
    std::shared_ptr<TonemapPass> m_tonemap_pass;

    void set_pass(const std::shared_ptr<RenderPass> pass, std::vector<std::shared_ptr<RenderPass>>& passes, const int index = -1);
    void print_info(const std::vector<std::shared_ptr<RenderPass>>& passes) const noexcept; // TODO: What's the point of this?
    void reset_backbuffer(std::vector<FrameBuffer*>& back_buffer);
    bool shaders_init_success();
    void render_object(Shader& shader, Renderable& object);
};
}
