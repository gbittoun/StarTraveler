#include "OptionsParser.h"
#include "SDLApplication.h"

#ifndef UNITTEST

int main( int argc, char **argv )
{
    int screenWidth = 800;
    int screenHeight = 800;
    std::string fileName;

    OptionsParser opts(argc, argv);

    auto files = opts.getUnnamedArguments();
    if (!files.size())
    {
        std::cerr << "Please, provide at least one input file" << std::endl;
        return 1;
    }
    else
    {
        fileName = files[0];
    }

    opts.tryGetInt("width", screenWidth);
    opts.tryGetInt("height", screenHeight);

    SDLApplication app(screenWidth, screenHeight, fileName);
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
