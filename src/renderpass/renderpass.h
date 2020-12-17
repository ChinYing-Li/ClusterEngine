#pragma once

#include <map>

#include "glincludes.h"
#include "pipelinebase.h"

namespace Cluster
{
class RenderPass
{
public:
    RenderPass();

    void virtual resize() = 0;
    void virtual render() = 0;

    void set_clear_color(const glm::vec3 new_clear_color) noexcept;

    void load_project_transform(glm::mat4& mat) noexcept;
    void load_view_transform(glm::mat4& mat) noexcept;
    void load_model_transform(glm::mat4& mat) noexcept;

    enum GL_SETTING
    {
        BLEND = GL_BLEND,
        CULL_FACE = GL_CULL_FACE,
        DEPTH_TEST = GL_DEPTH_TEST,
        STENCIL_TEST = GL_STENCIL_TEST,
        POLYGON_OFFSET_FILL = GL_POLYGON_OFFSET_FILL
    };

    void enable(GL_SETTING setting);
    void disable(GL_SETTING setting);

protected:
    glm::vec3 m_clear_color;

    glm::mat4 m_project_transform;
    glm::mat4 m_view_transform;
    glm::mat4 m_model_transform;

    std::map<GL_SETTING, bool> m_gl_settings;
};

}
