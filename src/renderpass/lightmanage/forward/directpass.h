#pragma once

#include <memory>

#include "glfoundation/gbuffer.h"
#include "glfoundation/shader.h"
#include "renderpass/renderpass.h"

namespace Cluster
{
    namespace LightForward
    {
        class LightingPass final : public RenderPass
        {
        public:
            LightingPass();
            ~LightingPass() = default;

            void resize(const unsigned int win_width, const unsigned int win_height) override;
            void render(RenderState& r_state, const Scene& scene) override;


        private:
            static const std::string m_pass_name;
            Shader m_shader;
            Texture2D m_light_texture;
        };
    } // namespace LightForward
} // namespace Cluster
