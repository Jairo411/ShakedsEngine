#ifndef WINDOW_H
#define	WINDOW_H

#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
// the order for these 3 ^^^ must be in that order

#include <string>
#include <iostream>

// pragma once is only windows, ifndef is universal
// struct is public by default, class is private by default

class Window 
{
public:
	Window();
	~Window();

	bool OnCreate(std::string name_, int width_, int height_);
	void OnDestroy();
	int GetWidth();
	int GetHeight();
	SDL_Window* GetWindow() const;

private:
	void SetPreAttributes();
	void SetPostAttributes();
	int width, height;
	SDL_Window* window;
	SDL_GLContext context; // doorway to the gpu - this communicates from the window to the gpu
};
#endif
