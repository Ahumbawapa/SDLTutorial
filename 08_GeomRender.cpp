#include <SDL.h>
#include <iostream>
#include <stdio.h>

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Prototypes
bool init();
void close();
bool loadMedia();

//global variables
//Application Window
SDL_Window* gWindow = nullptr;
// Window renderer
SDL_Renderer* gRenderer = nullptr;
// current displayed texture
SDL_Texture* gTexture = nullptr;

int main (int argc, char* args[])
{
	cout << __func__ << endl;

	if(false == init())
	{
		printf("Failed to initialize\n");
		return -1;
	}

	if(false == loadMedia())
	{
		printf("Failed to load media\n");
		return -2;
	}

	// preparation for main loop
	bool quit = false;

	SDL_Event e;

	int loopCounter = 0;

	// main event loop
	while(!quit)
	{
		//Handle events on queue
		while(SDL_PollEvent(&e) != 0)
		{
			if(e.type == SDL_QUIT)
				quit = true;
		}


		//Clear screen
		if (-1 == SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF))
			cout << "Error SDL_SetRenderDrawColor()" << endl;

		if(-1 == SDL_RenderClear(gRenderer))
			cout << "Error SDL_RenderClear()" << endl;

		// Render red filled quad
		SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRect);

	}

	close();
	return 0;

} // end of main()

bool init()
{
	cout << __func__ << endl;

	//Init SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0 )
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	cout << "SDL_Init done" << endl;

	if(false == SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		printf("Warning: Linear texture filtering not enabled!");
	}

	// create appclication window
	gWindow = SDL_CreateWindow(   "SDL_Tutorial 8 Geometry Rendering"
								, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED
								, SCREEN_WIDTH, SCREEN_HEIGHT
								, SDL_WINDOW_SHOWN);

	if(nullptr == gWindow)
	{
		printf("Window could not be created! SDL_Error:%s\n", SDL_GetError());
		return false;
	}

	cout << "SDL_CreateWindow done" << endl;


	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

	if(nullptr == gRenderer)
	{
		printf("Renderer could not be created! SDL_Error:%s\n", SDL_GetError());
		return false;
	}

	cout << "SDL_CreateRenderer() done" << endl;

	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

	// no images this time

	return true;
}

void close()
{
	SDL_DestroyTexture(gTexture);
	gTexture = nullptr;

	//destroy renderer
	SDL_DestroyRenderer(gRenderer);
	gRenderer = nullptr;

	//destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	// Quit subsystems
	SDL_Quit();
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Nothing to load
	return success;
}
