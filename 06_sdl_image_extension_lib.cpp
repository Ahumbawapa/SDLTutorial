//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <string>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

//Prototypes
//Starts up SDL and create window
bool init();
//Loads media
bool loadMedia();
//Frees media and shuts down SDL
void close();

//Loads individual image
SDL_Surface* loadSurface(std::string path);


//Global variables
SDL_Window* 	gWindow 			= NULL; //Window we'll be rendering to
SDL_Surface* 	gScreenSurface 		= NULL; //surface contained by the window
SDL_Surface* 	gKeyPressSurfaces [KEY_PRESS_SURFACE_TOTAL];
SDL_Surface* 	gCurrentSurface 	= NULL;	//Image we will load and show on the screen


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

	//main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	//set default current surface
	gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

	//while application is running
	while(!quit)
	{
		//Handle events on queue | Get the most recent event by SDL_PollEvent
		//Return 0 if event queue is empty
		while(SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if(e.type == SDL_QUIT)
			{
				quit = true;
			}

			//select surfaces based on key press
			switch(e.key.keysym.sym)
			{
				case SDLK_UP:
					gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
				break;
				case SDLK_DOWN:
					gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
				break;
				case SDLK_LEFT:
					gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
				break;
				case SDLK_RIGHT:
					gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
				break;

				default:
					gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
				break;
			}
		}

		//Apply the current image
		SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);

		//Update the surface
		SDL_UpdateWindowSurface(gWindow);
	}

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
	//Loading success flag
	bool success = true;

	//Load default surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("04_key_press/press.bmp");
	if(NULL == gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT])
	{
		printf("Failed to load default image!\n");
		success = false;
	}

	//Load UP surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("04_key_press/up.bmp");
	if(NULL == gKeyPressSurfaces[KEY_PRESS_SURFACE_UP])
	{
		printf("Failed to load UP image!\n");
		success = false;
	}

	//Load DOWN surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("04_key_press/down.bmp");
	if(NULL == gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN])
	{
		printf("Failed to load DONW image!\n");
		success = false;
	}

	//Load LEFT surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("04_key_press/left.bmp");
	if(NULL == gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT])
	{
		printf("Failed to load LEFT image!\n");
		success = false;
	}

	//Load RIGHT surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("04_key_press/right.bmp");
	if(NULL == gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT])
	{
		printf("Failed to load RIGHT image!\n");
		success = false;
	}

	return success;

}

void close()
{
	//Deallocate surface
	SDL_FreeSurface(gCurrentSurface);
	gCurrentSurface = NULL;

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystem
	SDL_Quit();
}

SDL_Surface* loadSurface(std::string path)
{
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if( NULL == loadedSurface)
	{
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}
	else
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, NULL );

		if(NULL == optimizedSurface)
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
	}


	return optimizedSurface;
}
