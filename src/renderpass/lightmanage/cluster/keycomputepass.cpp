#include <experimental/filesystem>

#include "keycomputepass.h"

namespace Cluster
{
    const std::string KeyComputePass::m_pass_name = "keycompute";

KeyComputePass::
KeyComputePass(const unsigned int tile_width, const unsigned int tile_height):
RenderPass(m_pass_name),
m_tile_width(tile_width),
m_tile_height(tile_height),
m_n_tile_x(0),
m_n_tile_y(0),
m_shader("", "", "", RenderPass::SHADER_ROOT / "lightmanage" / "keycompute.glsl")
{

}

void KeyComputePass::
resize(const unsigned int win_width, const unsigned int win_height)
{
    m_n_tile_x = win_width / m_tile_width;
    m_n_tile_y = win_height / m_tile_height;
}

void KeyComputePass::
render(RenderState& r_state, const Scene& scene)
{

    m_shader.use();
    m_shader.set_uniform1i("");
}
}