#pragma once

#include "includes/GLincludes.h"

class FrameBuffer
{
public:
    FrameBuffer() = default;
    ~FrameBuffer() = default;

private:
    GLuint m_frame_buffer;
    void init();
};
