#pragma once

#include "glincludes.h"

class RenderPass
{
public:
    RenderPass();

    void virtual resize() = 0;
    void virtual render() = 0;

    glm::mat4 m_project_transform;
    glm::mat4 m_view_transform;
    glm::mat4 m_model_transform;

protected:
};
