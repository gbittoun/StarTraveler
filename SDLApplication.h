#pragma once

#include <iostream>
#include <SDL.h>

#include "ErrorStateBase.h"
#include "GLHandler.h"

class SDLApplication : public ErrorStateBase
{
public:

	SDLApplication(int width, int height, int bpp);
	~SDLApplication();

	ErrorStateBase::ErrorCode init();

	void mainLoop();

	GLHandler & getGLHandler() const; 

private:

	const SDL_VideoInfo *videoInfo;
	SDL_Surface *surface;
	const int width, height, bpp;
	GLHandler glHandler;
	bool keepRunning;
	int videoFlags;

	void initSDL();

	void initVideoInfo();

	void createGLWindow();

	void initGL();

	void initStarData();

	void handleKeyPress(SDL_keysym *keysym);
};
