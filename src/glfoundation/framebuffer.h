#pragma once

#include "glincludes.h"

class FrameBuffer
{
public:
    FrameBuffer() = default;
    ~FrameBuffer() = default;

private:
    GLuint m_FBO;
    void init();
};
