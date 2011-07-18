#ifndef MARIO_H
#define MARIO_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#define BIG_OR_SMALL_ENUM(x) \
	DIRECTION_ENUM(x ## _BIG) \
	DIRECTION_ENUM(x ## _SMALL)

#define DIRECTION_ENUM(x) \
	x ## _LEFT, \
	x ## _RIGHT,

enum {
	BIG_OR_SMALL_ENUM(IDLE)
	BIG_OR_SMALL_ENUM(WALKING)
	NUMBER_OF_ANIMATION
};

enum {
	RIGHT,
	LEFT
};

typedef struct {
	SDL_Rect * frames;
	int countFrame;
	Uint32 delay;
} Animation;

typedef struct {
	SDL_Surface * image;
	Animation animation[NUMBER_OF_ANIMATION];
	int currentAnimation;
	int currentFrame;
	Uint32 lastUpdate;
	SDL_Rect position;
	int direction;
	int is_moving;
	float speed;
} Mario;

void Mario_init(Mario * mario);
void Mario_move_left(Mario * mario, int move);
void Mario_move_right(Mario * mario, int move);
void Mario_update(Mario * mario, Uint32 timeElapsed);
void Mario_draw(Mario * mario, SDL_Surface * surface, SDL_Rect offset);
void Mario_clean(Mario * mario);

#endif
