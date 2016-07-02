#include <cstdio>
#include "langtonapp.h"

LangtonApp::LangtonApp() {

}

LangtonApp::~LangtonApp() {

}

int LangtonApp::OnExecute() {
	if (!OnInit())
		return -1;

	SDL_Event event;

	while (running) {
		Uint32 lstart = SDL_GetTicks();
		while (SDL_PollEvent(&event))
			OnEvent(&event);
		OnLoop();
		OnRender();
		Uint32 lend = SDL_GetTicks();
		if ((lend - lstart) < LOOP_TIME)
			SDL_Delay(LOOP_TIME - (lend - lstart));
	}

	OnCleanup();
	return 0;
}

bool LangtonApp::OnInit() {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Could not initialise SDL. SDL error: %s\n", SDL_GetError());
		return false;
	}
	window = SDL_CreateWindow("Langton\'s Ant", 
			SDL_WINDOWPOS_UNDEFINED, 
			SDL_WINDOWPOS_UNDEFINED, 
			INIT_SCREEN_WIDTH, 
			INIT_SCREEN_HEIGHT, 
			SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (window == NULL) {
		fprintf(stderr, "Window could not be created. SDL error: %s\n", SDL_GetError());
		return false;
	}
	int imgflags = IMG_INIT_PNG;
	if (! (IMG_Init(imgflags)) & imgflags) {
		fprintf(stderr, "SDL_Image could not be loaded. %s\n", IMG_GetError());
		return false;
	}
	screensurface = SDL_GetWindowSurface(window);
	if ((renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)) == NULL) {
		fprintf(stderr, "Could not create renderer. SDL error: %s\n", SDL_GetError());
		return false;
	}
	SDL_Surface* loadsurface = IMG_Load("Ant.png");
	if (loadsurface == NULL) {
		fprintf(stderr, "Could not load Ant.png. %s\n", IMG_GetError());
		return false;
	}
	anttexture = SDL_CreateTextureFromSurface(renderer, loadsurface);
	if (anttexture == NULL) {
		fprintf(stderr, "Could not convert texture. %s\n", SDL_GetError());
		return false;
	}
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	running = true;
	return true;
}

void LangtonApp::OnLoop() {

}

void LangtonApp::OnRender() {
	SDL_GetWindowSize(window, &winX, &winY);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

void LangtonApp::OnEvent(SDL_Event* event) {
	switch (event->type) {
		case SDL_QUIT:
			running = false;
			break;
		case SDL_KEYDOWN:
			onKeyDown(&event->key);
			break;
		default:
			break;
	}
}

void LangtonApp::OnCleanup() {
	SDL_DestroyTexture(anttexture);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	anttexture = NULL;
	window = NULL;
	renderer = NULL;
	IMG_Quit();
	SDL_Quit();
}

void LangtonApp::onKeyDown(SDL_KeyboardEvent* keyEvent) {
	switch (keyEvent->keysym.sym) {
		case SDLK_q:
			running = false;
			break;
		default:
			break;
	}
}
