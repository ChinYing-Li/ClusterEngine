#include "includes/glfoundation/framebuffer.h"

void FrameBuffer::init()
{
    glGenFramebuffers(1, &m_frame_buffer);
}
