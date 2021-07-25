#include "skyboxpass.h"

namespace Cluster
{
std::string SkyBoxPass::m_pass_name = "skybox";

SkyBoxPass::
SkyBoxPass() :
  RenderPass(m_pass_name),
  m_skybox_shader(RenderPass::SHADER_ROOT / "skybox.vert", RenderPass::SHADER_ROOT / "skybox.frag"),
  m_texture_shader(RenderPass::SHADER_ROOT / "quad.vert", RenderPass::SHADER_ROOT / "singletexture.frag")
{

}
} // namespace Cluster
