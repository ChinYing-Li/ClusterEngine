#include <boost/program_options.hpp>
#include <memory>

#include "src/game/game.h"

namespace po = boost::program_options;

void create_options()
{
    bool use_deferred;

    po::options_description allowed_op_description("Allowed options");
    allowed_op_description.add_options()
            ("help", "")
            ("use_deferred", po::value<bool>(&use_deferred)->default_value(true), "whether to use deferred shading or not. If set to false, then forward shading will be used");
}

int main(int argc, char **argv)
{
    Game game;
    game.begin();
    return 0;
}
