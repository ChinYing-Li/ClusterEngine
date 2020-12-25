#include "bloompass.h"

namespace Cluster
{
const std::string BloomPass::m_pass_name = "bloom";

BloomPass::
BloomPass():
  RenderPass(m_pass_name)
{

}
}
