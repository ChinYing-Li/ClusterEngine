#include "skyboxpass.h"

SkyBoxPass::
SkyBoxPass()
{

}

void SkyBoxPass::setup()
{
    m_skybox_shader = Shader("", "", "", "skybox");

}
