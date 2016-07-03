/// @file langtonapp.cpp
/// @brief Class/implementation of the app
/// @author Petra
/// @version 0.1
/// @date 2016-07-03

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
	screensurface = SDL_GetWindowSurface(window);
	if ((renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)) == NULL) {
		fprintf(stderr, "Could not create renderer. SDL error: %s\n", SDL_GetError());
		return false;
	}
	int imgFlags = IMG_INIT_PNG; 
	if( !( IMG_Init( imgFlags ) & imgFlags ) ) { 
		 fprintf(stderr, "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() ); 
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
	SDL_FreeSurface(loadsurface);
	loadsurface = IMG_Load("Ant_r.png");
	if (loadsurface == NULL) {
		fprintf(stderr, "Could not load Ant_r.png. %s\n", IMG_GetError());
		return false;
	}
	ant_r_texture = SDL_CreateTextureFromSurface(renderer, loadsurface);
	if (ant_r_texture == NULL) {
		fprintf(stderr, "Could not convert texture. %s\n", SDL_GetError());
		return false;
	}
	antcols[Square_Colour::White] = anttexture;
	antcols[Square_Colour::Black] = ant_r_texture;
	SDL_FreeSurface(loadsurface);
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	running = true;
	return true;
}

void LangtonApp::OnLoop() {
	automata.Advance();
//	running = false;

}

void LangtonApp::OnRender() {
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(renderer);
	SDL_GetWindowSize(window, &winX, &winY);
	int fitsquaresx = winX / SQUARE_SIZE + 2;
	int fitsquaresy = winY / SQUARE_SIZE + 2;
//	int expixx = winX % SQUARE_SIZE;
//	int expixy = winY % SQUARE_SIZE;
	int originx = winX / 2 - SQUARE_SIZE / 2;
	int originy = winY / 2 + SQUARE_SIZE / 2;
	LangtonAnt ant = automata.getAnt();
	int firstx = ant.x - fitsquaresx / 2;
	int firsty = ant.y - fitsquaresy / 2;
	for (int x = firstx; x < fitsquaresx + firstx; x++)
		for (int y = firsty; y < fitsquaresy + firsty; y++) {
			SDL_Rect drect = {
				originx + (x - ant.x) * SQUARE_SIZE, 
				originy - (y - ant.y) * SQUARE_SIZE, 
				SQUARE_SIZE, SQUARE_SIZE
			};
			Square_Colour sqc = automata.getSquare(x, y);
			switch (sqc) {
				case Square_Colour::White:
					SDL_SetRenderDrawColor(renderer, 
							0xFF, 
							0xFF, 
							0xFF, 
							0xFF);
					break;
				default:
					SDL_SetRenderDrawColor(renderer, 
							0x00, 
							0x00, 
							0x00, 
							0xFF);
					break;
			}
			SDL_RenderFillRect(renderer, &drect);
		}
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
	SDL_DestroyTexture(ant_r_texture);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	anttexture = NULL;
	ant_r_texture = NULL;
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
