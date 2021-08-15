#include <experimental/filesystem>

#include "directpass.h"

namespace Cluster
{
    namespace LightForward
    {
        const std::string LightingPass::m_pass_name = "lighting";

        LightingPass::LightingPass() :
                RenderPass(m_pass_name),
                m_shader(RenderPass::SHADER_ROOT / "quad.vert", RenderPass::SHADER_ROOT / "direct.frag")
        {
        }

        void LightingPass::
        resize(const unsigned int width, const unsigned int height)
        {
            RenderPass::resize(width, height);
        }

        void LightingPass::
        render(RenderState& r_state, const Scene& scene)
        {

        }

        void LightingPass::set_gbuffer(std::shared_ptr<GBuffer> gbuffer)
        {
            m_gbuffer_ptr = gbuffer;
        }
    } // namespace LightForward
} // namespace Cluster
