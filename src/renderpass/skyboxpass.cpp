#include "skyboxpass.h"

namespace Cluster
{
std::string SkyBoxPass::m_pass_name = "skybox";

SkyBoxPass::
SkyBoxPass() :
  RenderPass(m_pass_name)
{

}

void SkyBoxPass::setup()
{
    m_skybox_shader = Shader("", "", "", "skybox");

}
}
