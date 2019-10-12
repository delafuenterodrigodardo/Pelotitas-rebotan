#include <iostream>
#include <cstdlib>
#include <string>
#include <SDL.h>
#include <SDL_mixer.h>
#include <math.h>

#include "application.h"
#include "ball.h"

Application::Application(const std::string &title, int width, int height)
{
	this->title = title;
	this->width = width;
	this->height = height;

	this->closed = !init();
}



bool Application::init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		std::cerr << SDL_GetError() << std::endl;
		return false;
	}
	Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);

	Mix_Chunk *choque = Mix_LoadWAV("Randomize2.wav");

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);

	if (window == nullptr)
	{
		std::cerr << SDL_GetError() << std::endl;
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (renderer == nullptr)
	{
		std::cerr << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}
Mix_chunk *choque = NULL;
choque = Mix_LoadWAV("Randomize2.wav");
//Mix_Chunk *choque = Mix_LoadWAV("Randomize2.wav");

Application::~Application()

{
    Mix_FreeChunk(choque);
	Mix_CloseAudio();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Application::poll_events(SDL_Event &event)
{
	if (event.type == SDL_QUIT)
	{
		closed = true;
	}
}



void Application::render()
{
	SDL_RenderPresent(renderer);
	SDL_SetRenderDrawColor(renderer, 50, 50, 150, 255);
	SDL_RenderClear(renderer);
}

SDL_Renderer* Application::get_renderer()
{
	return renderer;
}



Ball::Ball(int x, int y, int radius)
{
	this->x = x;
	this->y = y;
	this->radius = radius;

	this->x_speed = 3;
	this->y_speed = 3;
}

Ball::~Ball()
{
}

void Ball::poll_events(SDL_Event &event)
{
}

void Ball::render(SDL_Renderer *renderer, int cx, int cy, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	static const int BPP = 4;

	for (double dy = 1; dy <= radius; dy += 1.0)
	{
		double dx = floor(sqrt((2.0 * radius * dy) - (dy * dy)));
		int x = (cx - dx);

		SDL_SetRenderDrawColor(renderer, r, g, b, a);
		SDL_RenderDrawLine(renderer, (cx - dx), cy + dy - radius, (cx + dx), cy + dy - radius);
		SDL_RenderDrawLine(renderer, (cx - dx), cy - dy + radius, (cx + dx), cy - dy + radius);
	}
}

void Ball::update()
{
	x += x_speed;
	y += y_speed;

	if (x <= 20 || x >= 800 - 20)
	{
		x_speed *= -1;
		Mix_PlayChannel(-1,choque,0);
		std::cout << "X: " << this->get_x() << std::endl;
	}
	if (y <= 20 || y >= 600 - 20)
	{
		y_speed *= -1;
		Mix_PlayChannel(-1,choque,0);
		std::cout << "Y: " << this->get_y() << std::endl;
	}
}

static const int WIDTH = 800;
static const int HEIGHT = 600;

void poll_all_events(Application &application, Ball &ball)
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		application.poll_events(event);
		ball.poll_events(event);
	}
}

int main(int argc, char *argv[])
{
	Application application("Bouncing Ball", WIDTH, HEIGHT);
	Ball ball(100, 100, 20);
	Ball ball2(200, 200, 30);
	Ball ball3(300, 300, 30);
	Ball ball4(500, 500, 30);
	Ball ball5(450, 100, 30);



	while (!application.is_closed())
	{
		poll_all_events(application, ball);
		application.render();
		ball.update();
		ball2.update();
		ball3.update();
		ball4.update();
		ball5.update();
		ball.render(application.get_renderer(), ball.get_x(), ball.get_y(), 20, 0xFF, 0x00, 0xFF, 0xFF);
		ball2.render(application.get_renderer(),ball2.get_x(), ball2.get_y(), 30, 0xFF, 0x00, 0xFF, 0xFF);
		ball3.render(application.get_renderer(),ball3.get_x(), ball3.get_y(), 30, 0xFF, 0x00, 0xFF, 0xFF);
		ball4.render(application.get_renderer(),ball4.get_x(), ball4.get_y(), 30, 0xFF, 0x00, 0xFF, 0xFF);
		ball5.render(application.get_renderer(),ball5.get_x(), ball5.get_y(), 30, 0xFF, 0x00, 0xFF, 0xFF);
	}

	return 0;
}
