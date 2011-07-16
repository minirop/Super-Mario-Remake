#include "MainState.h"
#include "JeuState.h"

typedef struct {
	SDL_Surface * image;
} MS_t;

void MS_init(state_t * s);
void MS_update(state_t * s, Uint32 elapsedTime);
void MS_handleEvent(state_t * s);
void MS_draw(state_t * s, SDL_Surface * surface);
void MS_clean(state_t * s);

state_t * MS_get()
{
	state_t * state = malloc(sizeof(*state));
	state->init = MS_init;
	state->update = MS_update;
	state->handleEvent = MS_handleEvent;
	state->draw = MS_draw;
	state->clean = MS_clean;
	state->data = NULL;
	
	return state;
}

void MS_init(state_t * s)
{
	MS_t * data = malloc(sizeof(*data));
	data->image = IMG_Load("images/title.png");
	
	s->data = data;
}

void MS_update(state_t * s, Uint32 elapsedTime)
{
	s = s;
	elapsedTime = elapsedTime;
}

void MS_handleEvent(state_t * s)
{
	SDL_Event event;
	int continuer = 1;
	
	s = s;
	
	while(continuer && SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_QUIT:
				GS_PopState();
				continuer = 0;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						GS_PopState();
						continuer = 0;
						break;
					case SDLK_RETURN:
						GS_PopState();
						GS_PushState(JS_get());
						continuer = 0;
						break;
					default:
						;
				}
				break;
			default:
				;
		}
	}
}

void MS_draw(state_t * s, SDL_Surface * surface)
{
	MS_t * m = s->data;
	SDL_BlitSurface(m->image, NULL, surface, NULL);
}

void MS_clean(state_t * s)
{
	MS_t * m = s->data;
	SDL_FreeSurface(m->image);
}
