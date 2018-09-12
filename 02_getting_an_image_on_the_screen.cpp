//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


//Prototypes
//Starts up SDL and create window
bool init();
//Loads media
bool loadMedia();
//Frees media and shuts down SDL
void close();

//Global variables
SDL_Window* gWindow 		= NULL; //Window we'll be rendering to
SDL_Surface* gScreenSurface = NULL; //surface contained by the window
SDL_Surface* gHelloWorld 	= NULL;	//Image we will load and show on the scree


int main(int argc, char* args[])
{
	//Start up SDL and create window
	if(false == init())
	{
		printf("Failed to initialize!\n");
		return -1;
	}

	if(false == loadMedia())
	{
		printf("Failed to load media1\n");
		return -2;
	}

	//Apply the image
	SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);

	//Update the surface
	SDL_UpdateWindowSurface(gWindow);

	//Wait two seconds
	SDL_Delay(2000);

	//Free resources and close SDL
	close();

	return 0;
}

bool init()
{
	//Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	gWindow = SDL_CreateWindow(	"SDL Tutorial"
							   , SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED
							   , SCREEN_WIDTH, SCREEN_HEIGHT
							   , SDL_WINDOW_SHOWN);

	if(NULL == gWindow)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	gScreenSurface = SDL_GetWindowSurface(gWindow);

	return true;

}

bool loadMedia()
{
	//Load splash image
	gHelloWorld = SDL_LoadBMP("hello_world.bmp");

	if(NULL == gHelloWorld)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "hello_world.bmp"
														 , SDL_GetError());
		return false;
	}

	return true;
}

void close()
{
	//Deallocate surface
	SDL_FreeSurface(gHelloWorld);
	gHelloWorld = NULL;

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystem
	SDL_Quit();
}
