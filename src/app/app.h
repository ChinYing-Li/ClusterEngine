#pragma once
#include <boost/program_options.hpp>
#include <memory>
#include <experimental/filesystem>

#include "glfoundation/camera.h"
#include "glfoundation/scene.h"
#include "glfoundation/texturemanager.h"
#include "utilities/managers/windowmanager.h"
#include "utilities/fpscounter.h"

namespace fs = std::experimental::filesystem;
namespace po = boost::program_options;

// forward declaration
namespace Cluster
{
    class PipelineBase;
    class Scene;
}

class App
{
public:
    App();
    ~App() = default;

    bool begin(int argc, char **argv);
    void loop();
    void load_scene(fs::path& scene_path);
    
private:
    void get_command(int argc, char **argv);
    void create_pipeline();

    Cluster::WindowManager m_window_manager;
    Cluster::TextureManager m_texture_manager;
    bool m_use_deferred;
    bool m_use_cluster;
    fs::path m_scene_path;

    Cluster::Scene m_scene; // Cannot be none, so no need to be a pointer?
    std::unique_ptr<Cluster::PipelineBase> m_render_pipeline;
    Cluster::Camera m_camera;

    const float delta_t = 1.0f / 60.0f;
    Cluster::Timer m_timer;
    float prev_time;
    float cur_time;
};
