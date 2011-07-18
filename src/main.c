#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "GameState.h"
#include "MainState.h"
#include "config.h"

int main(int argc, char** argv)
{
	SDL_Surface * ecran = NULL;
	Uint32 lastUpdate = 0, currentTime = 0, elapsedTime = 0;
	
	argc = argc;
	argv = argv;
	
	SDL_Init(SDL_INIT_VIDEO);
	ecran = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption("Super Mario Bros.", NULL);
	
	GS_Init();
	
	GS_PushState(MS_get());
	
	GS_handleEvent();
	while(!GS_isEmpty())
	{
		currentTime = SDL_GetTicks();
		elapsedTime = currentTime - lastUpdate;
		if(elapsedTime >= REFRESH_TIME)
		{
			GS_update(elapsedTime);
			lastUpdate = currentTime;
		}
		
		GS_draw(ecran);
		SDL_Flip(ecran);
		
		GS_handleEvent();
	}
	
	GS_Clean();
	
	SDL_Quit();
	return 0;
}
