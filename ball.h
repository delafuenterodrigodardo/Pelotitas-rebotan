#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#pragma once

#include <SDL.h>

class Ball
{
	public:
		Ball(int x, int y, int radius);
		~Ball();

		void poll_events(SDL_Event &event);
		void render(SDL_Renderer *renderer, int cx, int cy, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

		inline int get_x() const { return x; }
		inline int get_y() const { return y; }

		void update();

	private:
		int x;
		int y;
		int radius;
		int x_speed;
		int y_speed;
};

#endif // BALL_H_INCLUDED
