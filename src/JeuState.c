#include "JeuState.h"

typedef struct {
	SDL_Surface * fond;
	SDL_Rect pos;
} JS_t;

void JS_init(state_t * s);
void JS_update(state_t * s, Uint32 elapsedTime);
void JS_handleEvent(state_t * s);
void JS_draw(state_t * s, SDL_Surface * surface);
void JS_clean(state_t * s);

state_t * JS_get()
{
	state_t * state = malloc(sizeof(*state));
	state->init = JS_init;
	state->update = JS_update;
	state->handleEvent = JS_handleEvent;
	state->draw = JS_draw;
	state->clean = JS_clean;
	state->data = NULL;
	
	return state;
}

void JS_update(state_t * s, Uint32 elapsedTime)
{
	s = s;
	elapsedTime = elapsedTime;
}

void JS_init(state_t * s)
{
	JS_t * data = malloc(sizeof(*data));
	data->fond = IMG_Load("levels/1-1/view.png");
	data->pos.x = 0;
	data->pos.y = 80;
	data->pos.h = 144;
	data->pos.w = 160;
	
	s->data = data;
}

void JS_handleEvent(state_t * s)
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
					case SDLK_RETURN:
						GS_PopState();
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

void JS_draw(state_t * s, SDL_Surface * surface)
{
	JS_t * m = s->data;
	SDL_BlitSurface(m->fond, &m->pos, surface, NULL);
}

void JS_clean(state_t * s)
{
	JS_t * m = s->data;
	SDL_FreeSurface(m->fond);
}
