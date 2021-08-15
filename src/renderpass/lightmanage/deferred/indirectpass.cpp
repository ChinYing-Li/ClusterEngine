#include <experimental/filesystem>

#include "glfoundation/gbuffer.h"
#include "indirectpass.h"

namespace Cluster
{
    namespace LightDeferred
    {
        const std::string IndirectPass::m_pass_name = "deferred_indiect";

        IndirectPass::
        IndirectPass():
        RenderPass(m_pass_name),
        m_shader(RenderPass::SHADER_ROOT / "quad.vert", RenderPass::SHADER_ROOT / "deferred" / "indirect.frag", "", ""),
        m_clear_color(0.0, 0.0, 0.0, 1.0)
        {
            m_capabilities[STENCIL_TEST] = true;
            m_capabilities[DEPTH_TEST] = true;
        }

        void IndirectPass::
        set_gbuffer(GBuffer* gbuffer)
        {
            m_gbuffer_ptr = gbuffer;
        }

        void IndirectPass::
        render(RenderState& r_state, const Scene& scene)
        {
            r_state.gl_change_settings(m_capabilities);
            r_state.set_clear_color(m_clear_color);
            glClear(GL_COLOR_BUFFER_BIT);
            glStencilFunc(GL_EQUAL, 1, 0xFF);

            nvtxRangePushA(m_pass_name.c_str());
            m_shader.bind();

            m_gbuffer_ptr->
        }
    } // namespace LightDeferred
} // namespace Cluster