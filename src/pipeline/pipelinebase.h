#pragma once

#include <memory>
#include <vector>

#include "glfoundation/camera.h"
#include "glfoundation/framebuffer.h"
#include "glfoundation/renderable.h"
#include "glfoundation/renderstate.h"
#include "glfoundation/shaderregistry.h"
#include "renderpass/renderpass.h"
// Do we really need this?
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
    void virtual render_scene(const Shader& shader, const Scene& scene) = 0;
    void virtual render_objects(const Shader& shader, const Scene& scene);
    void virtual render_skybox(const Shader& shader, const Scene& scene) = 0;
    void virtual update_frame(const Scene& scene);

    void set_hdr_pass(const std::shared_ptr<RenderPass> pass, const int index = -1);
    void set_ldr_pass(const std::shared_ptr<RenderPass> pass, const int index = -1);
    void set_tonemap_pass();   

    void print_hdr_pass_info() const noexcept;
    void print_ldr_pass_info() const noexcept;

protected:
    void virtual setup_backbuffers();
    unsigned int m_width, m_height;
    glm::mat4 m_project_mat;
    glm::mat4 m_view_mat;
    glm::mat4 m_model_mat;
    RenderState m_renderstate;

    std::vector<Renderable*> m_objects; // Should be within the Scene class
    std::map<Shader::Usage, std::unique_ptr<Shader>> m_shaders;

    FrameBuffer m_hdr_framebuffer;
    FrameBuffer m_ldr_framebuffer;
    std::vector<FrameBuffer> m_hdr_back_buffers;
    std::vector<FrameBuffer> m_ldr_back_buffers;
    std::vector<std::shared_ptr<RenderPass>> m_hdr_passes;
    std::vector<std::shared_ptr<RenderPass>> m_ldr_passes;
    std::shared_ptr<TonemapPass> m_tonemap_pass;

    void set_pass(const std::shared_ptr<RenderPass> pass, std::vector<std::shared_ptr<RenderPass>>& passes, const int index = -1);
    void set_camera_uniform(Shader& shader);
    void print_info(const std::vector<std::shared_ptr<RenderPass>>& passes) const noexcept; // TODO: What's the point of this?
    void reset_backbuffer(std::vector<FrameBuffer*>& back_buffer);
    bool shaders_init_success();
    void render_object(Shader& shader, Renderable& object);

private:

};
}
