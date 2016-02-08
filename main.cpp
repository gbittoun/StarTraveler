#include "SDLApplication.h"

/* screen width, height, and bit depth */
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 800
#define SCREEN_BPP     16

#ifndef UNITTEST

int main( int argc, char **argv )
{
    SDLApplication app(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP);
    app.init();
    app.mainLoop();

    return 0;
}

#else

#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/MemoryLeakWarningPlugin.h>

int main(int ac, char ** av)
{
    MemoryLeakWarningPlugin::turnOffNewDeleteOverloads();
    return CommandLineTestRunner::RunAllTests(ac, av);
}

#endif
