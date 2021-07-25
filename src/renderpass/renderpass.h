#pragma once

#include <experimental/filesystem>
#include <memory>
#include <nvToolsExt.h>

#include "glfoundation/glincludes.h"
#include "glfoundation/renderstate.h"

namespace fs = std::experimental::filesystem;

namespace Cluster
{
class Scene;

class RenderPass
{
public:
  RenderPass() = delete;
    RenderPass(const std::string& passname);
    ~RenderPass();

    void init(); // Need to call this in the constructor of all derived class.
    void virtual resize(const unsigned int width, const unsigned int height);
    void virtual render(RenderState& r_state, const Scene& scene) = 0;

    const static fs::path SHADER_ROOT;
    void enable() noexcept;
    void disable() noexcept;
    bool is_enabled() const noexcept;
    std::string get_pass_name() const noexcept;

    void set_render_target(Texture2D* target);

protected:
    unsigned int m_width;
    unsigned int m_height;
    const std::string m_pass_name;
    Texture2D* m_render_target_ptr;
    GL_Capabilities m_capabilities;

private:
    bool m_enabled; // RenderPass is disabled by default
};
}
