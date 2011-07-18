#include "Mario.h"

void Mario_init(Mario * mario)
{
	SDL_Rect * frames = malloc(sizeof(*frames));
	
	mario->image = IMG_Load("images/mario.png");
	mario->currentAnimation = IDLE_SMALL_RIGHT;
	mario->direction = RIGHT;
	mario->is_moving = 0;
	mario->speed = 1;
	mario->currentFrame = 0;
	mario->position.x = 0;
	mario->position.y = 192;
	
	frames[0].x = 211;
	frames[0].y = 0;
	frames[0].w = 13;
	frames[0].h = 16;
	mario->animation[IDLE_SMALL_RIGHT].frames = frames;
	mario->animation[IDLE_SMALL_RIGHT].countFrame = 1;
	mario->animation[IDLE_SMALL_RIGHT].delay = 0;
}

void Mario_move_left(Mario * mario, int move)
{
	if(mario->is_moving == 1)
	{
		if(move == 0 && mario->direction == LEFT)
		{
			mario->is_moving = 0;
		}
	}
	else
	{
		mario->is_moving = 1;
		mario->direction = LEFT;
	}
}

void Mario_move_right(Mario * mario, int move)
{
	if(mario->is_moving == 1)
	{
		if(move == 0 && mario->direction == RIGHT)
		{
			mario->is_moving = 0;
		}
	}
	else
	{
		mario->is_moving = 1;
		mario->direction = RIGHT;
	}
}

void Mario_update(Mario * mario, Uint32 timeElapsed)
{
	if(mario->is_moving == 1)
	{
		if(mario->direction == RIGHT)
		{
			mario->position.x += (mario->speed * timeElapsed * 0.1);
		}
		else
		{
			mario->position.x -= (mario->speed * timeElapsed * 0.1);
			if(mario->position.x < 0)
				mario->position.x = 0;
		}
	}
	
	timeElapsed = timeElapsed;
}

void Mario_draw(Mario * mario, SDL_Surface * surface, SDL_Rect offset)
{
	int cf = mario->currentFrame;
	SDL_Rect tmp_pos = mario->position;
	tmp_pos.x -= offset.x;
	tmp_pos.y -= offset.y;
	SDL_BlitSurface(mario->image, &(mario->animation[mario->currentAnimation].frames[cf]), surface, &tmp_pos);
}

void Mario_clean(Mario * mario)
{
	SDL_FreeSurface(mario->image);
	free(mario->animation[IDLE_SMALL_RIGHT].frames);
}
