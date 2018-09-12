#include <SDL.h>
#include <iostream>
#include <stdio.h>


//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Prototypes
//Loads individual image as texture
SDL_Texture* loadTexture(std::string path);
bool init();

//global variables
//The window we will be rendering to
SDL_Window* gWindow = nullptr;
//The window renderer
SDL_Renderer* gRenderer = nullptr;
//Current displayed texture
SDL_Texture* gTexture = nullptr;

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if(false == init())
	{
		printf("Failed to initialize\n");
		return -1;
	}

	bool quit = false;
	SDL_Event e;

	//main event loop
	while(!quit)
	{
		while(SDL_PollEvent(&e) != 0)
		{
			if(e.type == SDL_QUIT)
				quit = true;
		}
	}

	//shutdown SDL subsystem
	SDL_DestroyWindow(gWindow);
	SDL_Quit();
	return 0;
}


bool init()
{
	//initialize SDL
	if( SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	//create main window
	gWindow = SDL_CreateWindow( "SDL Tutorial 7"
								, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED
								, SCREEN_WIDTH, SCREEN_HEIGHT
								, SDL_WINDOW_SHOWN);

	if(nullptr == gWindow)
	{
		printf("Window could not be created! SDL_Error:%s\n", SDL_GetError());
		return false;
	}

	return true;
}

SDL_Texture* loadTexture(std::string path)
{
	return nullptr;
}
