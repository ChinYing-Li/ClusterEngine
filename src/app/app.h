#pragma once
#include <boost/program_options.hpp>
#include <memory>
#include <experimental/filesystem>

#include "camera.h"
#include "windowmanager.h"
#include "fpscounter.h"

namespace fs = std::experimental::filesystem;
namespace po = boost::program_options;

// forward declaration
class PipelineBase;
class Scene;

class App
{
public:
    App();
    ~App() = default;

    bool begin(int argc, char **argv);
    void loop();
    
private:
    void get_command(int argc, char **argv);
    void create_pipeline();
    void load_scene(fs::path& scene_path);

    WindowManager m_window_manager;
    TextureManager m_texture_manager;
    bool m_use_deferred;
    bool m_use_cluster;
    fs::path m_scene_path;

    std::unique_ptr<Scene> m_scene_ptr;
    std::unique_ptr<PipelineBase> m_render_pipeline;
    Camera m_camera;

    const float delta_t = 1.0f / 60.0f;
    Timer m_timer;
    float prev_time;
    float cur_time;
};
