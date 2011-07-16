#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "GameState.h"
#include "MainState.h"

#define BLOC_SIZE 16
#define SCREEN_W 160
#define SCREEN_H 144

int main(int argc, char** argv)
{
	SDL_Surface * ecran = NULL;
	
	argc = argc;
	argv = argv;
	
	SDL_Init(SDL_INIT_VIDEO);
	ecran = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption("Super Mario Bros.", NULL);
	
	GS_Init();
	
	GS_PushState(MS_get());
	
	while(!GS_isEmpty())
	{
		GS_draw(ecran);
		SDL_Flip(ecran);
		
		GS_handleEvent();
	}
	
	GS_Clean();
	
	SDL_Quit();
	return 0;
}
