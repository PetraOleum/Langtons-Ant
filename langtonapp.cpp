/// @file langtonapp.cpp
/// @brief Class/implementation of the app
/// @author Petra
/// @version 1.0
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
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	running = true;
	return true;
}

void LangtonApp::OnLoop() {
	if (!paused) {
		if (!reversing)
			automata.Advance();
		else
			automata.Reverse();
	}
}

void LangtonApp::OnRender() {
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(renderer);
	SDL_GetWindowSize(window, &winX, &winY);
	int fitsquaresx = winX / squareSize + 2;
	int fitsquaresy = winY / squareSize + 2;
	int originx = winX / 2 - squareSize / 2;
	int originy = winY / 2 + squareSize / 2;
	LangtonAnt ant = automata.getAnt();
	if (tracking) {
		if (ABS(ant.x - centreX) > fitsquaresx / 4)
			centreX = ant.x;
		if (ABS(ant.y - centreY) > fitsquaresy / 4)
			centreY = ant.y;
	}
	int firstx = centreX - fitsquaresx / 2;
	int firsty = centreY - fitsquaresy / 2;
	for (int x = firstx; x < fitsquaresx + firstx; x++)
		for (int y = firsty; y < fitsquaresy + firsty; y++) {
			SDL_Rect drect = {
				originx + (x - centreX) * squareSize, 
				originy - (y - centreY) * squareSize, 
				squareSize, squareSize
			};
			Square_Colour sqc = automata.getSquare(x, y);
			if (x == ant.x && y == ant.y) {
				SDL_SetRenderDrawColor(renderer,
						0xFF,
						0x00,
						0x00,
						0xFF);
				SDL_RenderFillRect(renderer, &drect);
			}
			else if (sqc == Square_Colour::White) {
				SDL_SetRenderDrawColor(renderer, 
						0xFF, 
						0xFF, 
						0xFF, 
						0xFF);
				SDL_RenderFillRect(renderer, &drect);
			}
//			switch (sqc) {
//				case Square_Colour::White:
//					SDL_SetRenderDrawColor(renderer, 
//							0xFF, 
//							0xFF, 
//							0xFF, 
//							0xFF);
//					break;
//				default:
//					SDL_SetRenderDrawColor(renderer, 
//							0x00, 
//							0x00, 
//							0x00, 
//							0xFF);
//					break;
//			}
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
		case SDL_MOUSEWHEEL:
			squareSize -= event->wheel.y;
			if (squareSize < 1)
				squareSize = 1;
		case SDL_MOUSEBUTTONDOWN:
			if (event->button.button == SDL_BUTTON_LEFT) {
				mouseDown = true;
				mousestartx = event->button.x;
				mousestarty = event->button.y;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (event->button.button == SDL_BUTTON_LEFT)
				mouseDown = false;
			break;
		case SDL_MOUSEMOTION:
			if (mouseDown) {
				tracking = false;
				int rx = mousestartx - event->button.x;
				int ry = mousestarty - event->button.y;
				if (ABS(rx) > squareSize) {
					centreX += rx / squareSize;
					mousestartx -= rx;
				}
				if (ABS(ry) > squareSize) {
					centreY -= ry / squareSize;
					mousestarty -= ry;
				}
			}
			break;
		default:
			break;
	}
}

void LangtonApp::OnCleanup() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	window = NULL;
	renderer = NULL;
	SDL_Quit();
}

void LangtonApp::onKeyDown(SDL_KeyboardEvent* keyEvent) {
	switch (keyEvent->keysym.sym) {
		case SDLK_q:
			running = false;
			break;
		case SDLK_p:
			paused = !paused;
			break;
		case SDLK_c:
			centreX = automata.getAnt().x;
			centreY = automata.getAnt().y;
			tracking = true;
			break;
		case SDLK_F11:
			if (fullscreen) {
				SDL_SetWindowFullscreen(
						window, 
						0);
				fullscreen = false;
			} else {
				SDL_SetWindowFullscreen(
						window, 
						SDL_WINDOW_FULLSCREEN_DESKTOP);
				fullscreen = true;
			}
			break;
		case SDLK_n:
			if (reversing)
				automata.Reverse();
			else
				automata.Advance();
			break;
		case SDLK_RIGHT:
			reversing = false;
			break;
		case SDLK_LEFT:
			reversing = true;
			break;
		case SDLK_ESCAPE:
			if (fullscreen) {
				SDL_SetWindowFullscreen(
						window, 
						0);
				fullscreen = false;
			} else {
				running = false;
			}
			break;
		case SDLK_PLUS:
		case SDLK_KP_PLUS:
			squareSize = squareSize * 15 / 10 + 1;
			break;
		case SDLK_MINUS:
		case SDLK_KP_MINUS:
			squareSize = squareSize * 5 / 10;
			if (squareSize < 1)
				squareSize = 1;
			break;
		default:
			break;
	}
}
