#pragma once

#include "renderpass/renderpass.h"

namespace Cluster
{
class ClusterPass : public RenderPass
{
public:
  ClusterPass();
  static const std::string m_pass_name;
};
}
