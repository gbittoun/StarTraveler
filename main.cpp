#include "SDLApplication.h"

/* screen width, height, and bit depth */
#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP     16

int main( int argc, char **argv )
{
    SDLApplication app(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP);
    app.init();
    app.mainLoop();

    return 0;
}