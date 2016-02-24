#include <cstring>
#include <vector>

#include "SDLApplication.h"
#include "StarField.h"

SDLApplication::SDLApplication(int width, int height, std::string fileName) :
	ErrorStateBase(),
	videoInfo(0),
	surface(0),
	width(width),
	height(height),
    fileName(fileName),
	glHandler(),
	keepRunning(true),
	videoFlags()
{
    glHandler.setCamera(&this->camera);
}

SDLApplication::~SDLApplication()
{
	SDL_Quit();
}

void SDLApplication::initSDL()
{
	if (checkState())
	{
		/* initialize SDL */
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			std::cerr << "Video initialization failed: " << SDL_GetError() << std::endl;
	        errorState = VIDEO_INITIALIZATION_FAILED;
	    }
	}
}

void SDLApplication::initVideoInfo()
{
	if (checkState())
	{
	    /* Fetch the video info */
	    videoInfo = SDL_GetVideoInfo();

	    if (!videoInfo)
	    {
			std::cerr << "Video query failed: " << SDL_GetError() << std::endl;
	        errorState =  VIDEO_QUERY_FAILED;
	    }
	}
}

void SDLApplication::createGLWindow()
{
    if (checkState())
    {
	    /* the flags to pass to SDL_SetVideoMode */
		videoFlags  = SDL_OPENGL;          /* Enable OpenGL in SDL */
	    videoFlags |= SDL_GL_DOUBLEBUFFER; /* Enable double buffering */
	    videoFlags |= SDL_HWPALETTE;       /* Store the palette in hardware */
	    videoFlags |= SDL_RESIZABLE;       /* Enable window resizing */

	    /* This checks to see if surfaces can be stored in memory */
	    if (videoInfo->hw_available)
	        videoFlags |= SDL_HWSURFACE;
	    else
	        videoFlags |= SDL_SWSURFACE;

	    /* This checks if hardware blits can be done */
	    if (videoInfo->blit_hw)
	        videoFlags |= SDL_HWACCEL;

	    /* Sets up OpenGL double buffering */
	    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	    /* get a SDL surface */
	    surface = SDL_SetVideoMode(width, height, 0, videoFlags);

	    /* Verify there is a surface */
	    if (!surface)
	    {
			std::cerr << "Video mode set failed: " << SDL_GetError() << std::endl;
	        errorState = VIDEO_MODE_SET_FAILED;
	    }
	}
}

void SDLApplication::initGL()
{
	if (checkState())
	{
		errorState = this->glHandler.initGL();
		glHandler.resizeWindow(width, height);
	}
}

void SDLApplication::initStarData()
{
    glHandler.setStarField(StarFieldBuilder().fromFile(fileName));
}

ErrorStateBase::ErrorCode SDLApplication::init()
{
    initSDL();
    initVideoInfo();
    createGLWindow();
    initStarData();
    initGL();

    return errorState;
}

void SDLApplication::handleKeyPress(SDL_keysym *keysym)
{
    switch ( keysym->sym )
    {
    case SDLK_ESCAPE:
        /* ESC key was pressed */
        keepRunning = false;
        break;
    case SDLK_F1:
        /* F1 key was pressed
         * this toggles fullscreen mode
         */
        SDL_WM_ToggleFullScreen( surface );
        break;
    default:
        break;
    }
}

void SDLApplication::handleMouseMotion(SDL_MouseMotionEvent event)
{
    int x, y;
    int buttons_state = SDL_GetMouseState(&x, &y);

    if (buttons_state & SDL_BUTTON(SDL_BUTTON_LEFT) && buttons_state & SDL_BUTTON(SDL_BUTTON_RIGHT))
    {
        camera.updateFOV(event.yrel * 0.1);
    }
    else if (buttons_state & SDL_BUTTON(SDL_BUTTON_LEFT))
    {
        camera.updateOrientationXY(event.yrel * 0.001, event.xrel * 0.001);
    }
    else if (buttons_state & SDL_BUTTON(SDL_BUTTON_RIGHT))
    {
        camera.updatePositionFromDelta(event.yrel * 0.1);
    }
}


void SDLApplication::mainLoop()
{
    /* wait for events */
    while (keepRunning)
    {
    	if (!checkState())
    	{
    		keepRunning = false;
    		std::cerr << "State error, breaking SDL event loop" << std::endl;
    		break;
    	}

        /* handle the events in the queue */
    	SDL_Event event;
        std::memset(&event, 0, sizeof(event));
        while (SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_ACTIVEEVENT:
                /* Something's happend with our focus */
                break;
            case SDL_VIDEORESIZE:
                /* handle resize event */
                surface = SDL_SetVideoMode(event.resize.w,
                            event.resize.h,
                            16, videoFlags);
                if ( !surface )
                {
                    fprintf( stderr, "Could not get a surface after resize: %s\n", SDL_GetError( ) );
                    keepRunning = false;
                    errorState = INVALID_SURFACE_AFTER_RESIZE;
                }
                glHandler.resizeWindow( event.resize.w, event.resize.h );
                break;
            case SDL_KEYDOWN:
                /* handle key presses */
                handleKeyPress(&event.key.keysym);
                break;
            case SDL_MOUSEMOTION:
                handleMouseMotion(event.motion);
                break;
            case SDL_QUIT:
                /* handle quit requests */
                keepRunning = false;
                break;
            default:
                break;
            }
        }

        glHandler.drawGLScene();
		SDL_GL_SwapBuffers( );
    }
}
