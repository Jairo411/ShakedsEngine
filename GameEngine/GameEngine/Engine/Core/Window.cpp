#include "Window.h"
#include "Debug.h"

Window::Window() : window(nullptr), width(0), height(0)
{
	//window = nullptr;    is the same as ^^ : window(nullptr)
	// same for initializing width and height
}

Window::~Window()
{
	OnDestroy();
}

bool Window::OnCreate(std::string name_, int width_, int height_)
{
	// initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		Debug::FatalError("SDL failed to initialize!", "Window.cpp", __LINE__);
		return false;
	}

	width = width_;
	height = height_;
	
	SetPreAttributes();
	
	window = SDL_CreateWindow(name_.c_str(), 
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height,
		SDL_WINDOW_OPENGL);
	
	if (!window) {
		Debug::FatalError("Window failed to create!", "Window.cpp", __LINE__);
		return false;
	}

	context = SDL_GL_CreateContext(window);

	SetPostAttributes();
	
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		Debug::FatalError("GLEW failed to initialize!", "Window.cpp", __LINE__);
		return false;
	}

	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, width, height);

	std::cout << "Graphics Card: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	return true;
}

void Window::OnDestroy() {
	// always destroy from the inside out
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	window = nullptr;
	// always delete pointers before setting it to nullptr
}

int Window::GetWidth() {
	return width;
}

int Window::GetHeight() {
	return height;
}

SDL_Window* Window::GetWindow() const {
	return window;
}

void Window::SetPreAttributes() {
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);
	
	glewExperimental = GL_TRUE;
}

void Window::SetPostAttributes() {
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
}
