/// @file langtonapp.h
/// @brief Header file for the SDL app
/// @author Petra
/// @version 0.1
/// @date 2016-07-03

#ifndef LANGTONAPP_H
#define LANGTONAPP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "automata.h"

/// @brief Initial width of screen
#define INIT_SCREEN_WIDTH 500
/// @brief Initial height of screen
#define INIT_SCREEN_HEIGHT 500

/// @brief Size of square (int pixels)
#define SQUARE_SIZE 10

/// @brief Loop time in (1000 / FPS)
#define LOOP_TIME (1000/60)

class LangtonApp {
	private:
		/// @brief Whether the app is running
		bool running = false;

		/// @brief Whether the app is fullscreen
		bool fullscreen = false;

		/// @brief Whether the mouse is down
		bool mouseDown = false;

		/// @brief Handle keydowns
		///
		/// @param keyEvent The keyboard event
		void onKeyDown(SDL_KeyboardEvent* keyEvent);

		/// @brief Updated with the width each render
		int winX = INIT_SCREEN_WIDTH;

		/// @brief Updated with the height each render
		int winY = INIT_SCREEN_HEIGHT;

		/// @brief Holds the window
		SDL_Window* window = NULL;

		/// @brief Holds the surface
		SDL_Surface* screensurface = NULL;

		/// @brief Holds the white-square ant texture
		SDL_Texture* anttexture = NULL;

		/// @brief Holds the black-square ant texture
		SDL_Texture* ant_r_texture = NULL;

		/// @brief Holds the renderer
		SDL_Renderer* renderer;

		/// @brief Easy referencing
		std::map<Square_Colour, SDL_Texture*> antcols;

		/// @brief The automata
		LangtonAutomata automata;

	public:
		/// @brief Constructor
		LangtonApp();

		/// @brief Destructor
		~LangtonApp();

		/// @brief Run the app
		///
		/// @return Execution status
		int OnExecute();

		/// @brief Initialise the app
		///
		/// @return Success/Failure
		bool OnInit();

		/// @brief Handle events
		///
		/// @param event Stores the event
		void OnEvent(SDL_Event* event);

		/// @brief Run once on every loop
		void OnLoop();

		/// @brief Rendering code
		void OnRender();

		/// @brief Cleanup code when finishing
		void OnCleanup();
};

#endif
