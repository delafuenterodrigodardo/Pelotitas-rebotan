#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED

#pragma once

#include <string>
#include <SDL.h>

class Application
{
	public:
		Application(const std::string &title, int width, int height);
		~Application();

		inline bool is_closed() const {
			return closed;
		}

		void poll_events(SDL_Event &event);
		void render();

		SDL_Renderer* get_renderer();

	private:
		bool init();

		SDL_Window *window = nullptr;
		SDL_Renderer *renderer = nullptr;

		std::string title;
		int width = 640;
		int height = 480;
		bool closed = false;
};

#endif // APPLICATION_H_INCLUDED
