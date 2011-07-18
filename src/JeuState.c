#include "JeuState.h"
#include "Mario.h"
#include "config.h"

typedef struct {
	SDL_Surface * fond;
	SDL_Rect pos;
	int ymax;
	Mario * mario;
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
	JS_t * m = s->data;
	
	Mario_update(m->mario, elapsedTime);
}

void JS_init(state_t * s)
{
	JS_t * data = malloc(sizeof(*data));
	data->fond = IMG_Load("levels/1-1/view.png");
	data->pos.x = 0;
	data->pos.y = 80;
	data->pos.h = 144;
	data->pos.w = 160;
	data->mario = malloc(sizeof(*(data->mario)));
	data->ymax = 224;
	
	Mario_init(data->mario);
	
	s->data = data;
}

void JS_handleEvent(state_t * s)
{
	SDL_Event event;
	int continuer = 1;
	JS_t * m = s->data;
	
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
					case SDLK_LEFT:
						Mario_move_left(m->mario, 1);
						break;
					case SDLK_RIGHT:
						Mario_move_right(m->mario, 1);
						break;
					default:
						;
				}
				break;
			case SDL_KEYUP:
				switch(event.key.keysym.sym)
				{
					case SDLK_LEFT:
						Mario_move_left(m->mario, 0);
						break;
					case SDLK_RIGHT:
						Mario_move_right(m->mario, 0);
						break;
					default:
						;
				}
				break;
			default:
				;
		}
	}
	
	{
		SDL_Rect frame_rect = m->mario->animation[m->mario->currentAnimation].frames[m->mario->currentFrame];
		int px = (SCREEN_W - frame_rect.w) / 2;
		int py = (SCREEN_H - frame_rect.h) / 2;
		int pymax = m->ymax - SCREEN_H;
		
		if(m->mario->position.x < px)
		{
			m->pos.x = 0;
		}
		else
		{
			m->pos.x = m->mario->position.x - px;
		}
		
		if(m->mario->position.y < py)
		{
			m->pos.y = 0;
		}
		else if(m->mario->position.y > pymax)
		{
			m->pos.y = pymax;
		}
		else
		{
			m->pos.y = m->mario->position.y - py;
		}
	}
}

void JS_draw(state_t * s, SDL_Surface * surface)
{
	JS_t * m = s->data;
	SDL_BlitSurface(m->fond, &(m->pos), surface, NULL);
	Mario_draw(m->mario, surface, m->pos);
}

void JS_clean(state_t * s)
{
	JS_t * m = s->data;
	SDL_FreeSurface(m->fond);
	Mario_clean(m->mario);
}
