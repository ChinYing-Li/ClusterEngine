#include <memory>
#include "src/game.h"
/*
void print_mat4(glm::mat4& m)
{
    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            std::cout << m[i][j] << " ";
        }
        std::cout << "\n\n" << std::endl;
    }
    return;
}*/

int main(int argc, char **argv)
{
    Game game;
    game.run();
    return 0;
}
