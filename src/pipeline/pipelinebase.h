#pragma once

#include <memory>

#include "camera.h"
#include "framebuffer.h"
#include "textureregistry.h"

class PipelineBase
{
public:
    PipelineBase();
    ~PipelineBase();

    std::shared_ptr<FrameBuffer> get_current_framebuffer();

    TextureRegistry m_texture_registry;

private:
    std::shared_ptr<FrameBuffer> m_current_frambuffer_ptr;
    Camera m_cam;
};
