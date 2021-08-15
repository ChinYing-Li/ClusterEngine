#pragma once

#include "glfoundation/shader.h"
#include "glfoundation/texture.h"
#include "renderpass/renderpass.h"

namespace Cluster
{
    class KeyComputePass: public RenderPass
    {
    public:
        KeyComputePass(const unsigned int tile_width = 100, const unsigned int tile_height = 100);
        ~KeyComputePass() = default;

        void resize(const unsigned int win_width, const unsigned int win_height) override;
        void render(RenderState& r_state, const Scene& scene) override;

    private:
        static const std::string m_pass_name;

        unsigned int m_tile_width;
        unsigned int m_tile_height;
        unsigned int m_n_tile_x;
        unsigned int m_n_tile_y;
        Texture2D m_texture;
        Shader m_shader;

    };
}
