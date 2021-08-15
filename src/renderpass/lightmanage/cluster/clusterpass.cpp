#include "clusterpass.h"

namespace Cluster
{
    const std::string ClusterPass::m_pass_name = "cluster";
    ClusterPass::ClusterPass():
    RenderPass(m_pass_name)
{

}
}
