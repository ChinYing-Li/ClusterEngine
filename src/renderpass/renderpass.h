#pragma once

#include <memory>

#include "glincludes.h"
#include "pipelinebase.h"

namespace Cluster
{
class RenderPass
{
public:
    RenderPass(const std::string& passname);

    void virtual resize(const unsigned int win_width, const unsigned int win_height) = 0;
    void virtual render() = 0;

    void enable() noexcept;
    void disable() noexcept;
    bool is_enabled() const noexcept;
    std::string get_pass_name() const noexcept;

    void set_source();

protected:
    const std::string m_pass_name;
    std::unique_ptr<Texture2D> m_source;
private:
    RenderPass() {};

    bool m_enabled; // RenderPass is disabled by default
};

}
