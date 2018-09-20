#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <stdio.h>

using namespace std;


//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Prototypes
//Loads individual image as texture
bool init(); //starts up SDL and creates window
void close();
bool loadMedia(); //loads media in general
SDL_Texture* loadTexture(std::string path); //loads individual image as texture


//global variables
//----------------
//The window we will be rendering to
SDL_Window* gWindow = nullptr;
//The window renderer
SDL_Renderer* gRenderer = nullptr;
//Current displayed texture
SDL_Texture* gTexture = nullptr;

int main(int argc, char* args[])
{
	cout << __func__ << endl;


	//Start up SDL and create window
	if(false == init())
	{
		printf("Failed to initialize\n");
		return -1;
	}


	//Load media
	if(false == loadMedia())
	{
		printf("Failed to load media\n");
		return -2;
	}


	//preparations for main loop
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

		//clear screen
		SDL_RenderClear(gRenderer);

		//Render texture to screen
		SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

		//Update screen
		SDL_RenderPresent(gRenderer);
	}

    //Free resources and close SDL
	close();

	return 0;
}


bool init()
{
	cout << __func__ << endl;

	cout << "SDL_Init()..." << endl;
	//initialize SDL
	if( SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	cout << "SDL_SetHint()..." << endl;
	//Set texture filtering to linear
	if(false == SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		printf("Warning: Linear texture filtering not enabled!");
	}


	cout << "SDL_CreateWindow()..." << endl;
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


	cout << "SDL_CreateRenderer()..." << endl;
	//create renderer for window
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

	if(nullptr == gRenderer || NULL == gRenderer)
	{
		printf("Renderer could not be created! SDL Error:%s\n", SDL_GetError());
		return false;
	}


	cout << "SDL_SetRenderDrawColor()..." << endl;
	//Initialize rederer color
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);


	cout << "IMG_Init()..." << endl;
	//Initialize PNG loading
	int imgFlags = IMG_InitFlags::IMG_INIT_PNG;
	if( false == (IMG_Init(imgFlags) & imgFlags ) )
	{
		printf("SDL image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
		return false;
	}

	return true;
}

//Calls loadTexture to create a texture from an png image
bool loadMedia()
{
	//Load PNG texture
	gTexture = loadTexture("C:\\work\\SDL\\lazyFooTutorial\\07_texture_loading_and_rendering\\texture.png");

	if(nullptr == gTexture)
	{
		printf("Failed to load texture image!\n");
		return false;
	}

	return true;
}


SDL_Texture* loadTexture(std::string path)
{

	//The final texture
	SDL_Texture* newTexture = nullptr;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if(nullptr == loadedSurface)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());

		return newTexture;
	}

	//create texture from surface pixels
	newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

	if(nullptr == newTexture)
		printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());

	//get rid of loaded surface
	SDL_FreeSurface(loadedSurface);

	return newTexture;
}

void close()
{
	//Free loaded image
	SDL_DestroyTexture(gTexture);
	gTexture = nullptr;

	//destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;
	gRenderer = nullptr;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
