#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

typedef struct _state_t {
	void (*init)(struct _state_t * s);
	void (*update)(struct _state_t * s, Uint32 elapsedTime);
	void (*handleEvent)(struct _state_t * s);
	void (*draw)(struct _state_t * s, SDL_Surface * surface);
	void (*clean)(struct _state_t * s);
	void * data;
} state_t;

void GS_Init();
void GS_Clean();

void GS_handleEvent();
void GS_update();
void GS_draw(SDL_Surface * surface);

void GS_PushState(state_t * state);
void GS_PopState();

int GS_isEmpty();

#endif
