#pragma once

#include "renderpass/renderpass.h"

namespace Cluster
{
    // forward declaration
    class GBuffer;

    namespace LightDeferred
    {
        class IndirectPass : public RenderPass
        {
        public:
            IndirectPass();
            ~IndirectPass();

            void resize(const unsigned int win_width, const unsigned int win_height) override;
            void render(RenderState& r_state, const Scene& scene) override;
            void set_gbuffer(GBuffer* gbuffer_ptr);

        private:
            static const std::string m_pass_name;
            const glm::vec4 m_clear_color;
            Shader m_shader;
            GBuffer* m_gbuffer_ptr;
        };
    } // namespace LightDeferred
} // namespace Cluster
