#pragma once

#include <memory>
#include <nvToolsExt.h>

#include "glincludes.h"
#include "renderstate.h"

namespace Cluster
{
class Scene;

class RenderPass
{
public:
    RenderPass(const std::string& passname);

    void virtual resize(const unsigned int win_width, const unsigned int win_height) = 0;
    void virtual render(RenderState& r_state, const Scene& scene) = 0;

    void enable() noexcept;
    void disable() noexcept;
    bool is_enabled() const noexcept;
    std::string get_pass_name() const noexcept;

    void set_render_target(Texture2D* target);

protected:
    const std::string m_pass_name;
    Texture2D* m_render_target;
    GL_Capabilities m_capabilities;
private:
    RenderPass() {};
    bool m_enabled; // RenderPass is disabled by default
};
}
