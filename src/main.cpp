#include <memory>

#include "app/app.h"

int main(int argc, char **argv)
{
    App application;
    bool init_success = application.begin(argc, argv);
    if(!init_success) return 1;

    application.loop();
    return 0;
}
