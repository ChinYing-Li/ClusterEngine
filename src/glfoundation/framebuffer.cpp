#include "src/glfoundation/framebuffer.h"

void FrameBuffer::init()
{
    glGenFramebuffers(1, &m_FBO);
}
