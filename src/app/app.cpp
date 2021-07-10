#include <boost/log/trivial.hpp>
#include <iostream>
#include <memory>

#include "app/app.h"
#include "utilities/Imanager.h"

namespace fs = std::experimental::filesystem;
namespace po = boost::program_options;

App::
App():
m_window_manager(800, 600),
m_texture_manager()
{}

bool App::
begin(int argc, char **argv)
{
    glfwSetErrorCallback(WindowManager::error_callback);
    if(!glfwInit())
    {
        BOOST_LOG_TRIVIAL(fatal) << "failed to initialize GLFW library";
        return false;
    }
    std::cout << "GLFW library initialized, ready to start the application." << std::endl;
    get_command(args, argv);
    create_pipeline();
    return true;
}

void App::
loop()
{
    int count = 0;
    while(!glfwWindowShouldClose(m_window_manager.window_ptr))
    {
        if (m_timer.processTick())
        {
            std::cout << count << std::endl;
            ++count;
            glfwSwapBuffers(data->inputmanager_ptr->window_ptr);
            glfwPollEvents();
        }
    }
}

void App::
get_command(int argc, char **argv)
{
    po::options_description allowed_op_description("Allowed options");
    allowed_op_description.add_options()
            ("help,h", "Use deferred rendering pipeline if this flag is set")
            ("use_deferred,d", po::bool_switch(&m_use_deferred), "Set this flag to use deferred shading. If set to false, then forward shading will be used")
            ("cluster,c", po::bool_switch(&m_use_cluster), "Set this flag to use cluster rendering.")
            ("scene,s", "The absolute path to the scene file.");
    po::command_line_parser(args, argv).options(allowed_op_description).run();
}

void App::
load_scene(fs::path& scene_path)
{
    // TODO:
}

void App::
create_pipeline()
{

}
