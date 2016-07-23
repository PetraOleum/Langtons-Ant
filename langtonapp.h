/// @file langtonapp.h
/// @brief Header file for the SDL app
/// @author Petra
/// @version 1.0
/// @date 2016-07-03

#ifndef LANGTONAPP_H
#define LANGTONAPP_H

#include <SDL2/SDL.h>

#include "automata.h"

/// @brief Initial width of screen
#define INIT_SCREEN_WIDTH 500
/// @brief Initial height of screen
#define INIT_SCREEN_HEIGHT 500

/// @brief Loop time in (1000 / FPS)
#define LOOP_TIME (1000/120)

/// @brief Absolute value of A
///
/// @param A The value to find the abs of
///
/// @return A if A >=0, else -A
#define ABS(A) ((A < 0) ? -(A) : (A))

class LangtonApp {
	private:
		/// @brief The size of the squares (int pixels)
		int squareSize = 10;
		
		/// @brief Whether the app is running
		bool running = false;

		/// @brief Whether we are reversing
		bool reversing = false;

		/// @brief Whether the app is fullscreen
		bool fullscreen = false;

		/// @brief Whether the mouse is down
		bool mouseDown = false;

		/// @brief Tracking the ant or not
		bool tracking = true;

		/// @brief y when mouse starts clicking
		int mousestartx = 0;

		/// @brief y when mouse starts clicking
		int mousestarty = 0;

		/// @brief If the generation is paused or not
		bool paused = false;

		/// @brief Handle keydowns
		///
		/// @param keyEvent The keyboard event
		void onKeyDown(SDL_KeyboardEvent* keyEvent);

		/// @brief Updated with the width each render
		int winX = INIT_SCREEN_WIDTH;

		/// @brief Updated with the height each render
		int winY = INIT_SCREEN_HEIGHT;

		/// @brief The x-coord being centred on
		int centreX = 0;

		/// @brief The y-coord being centred on
		int centreY = 0;

		/// @brief Holds the window
		SDL_Window* window = NULL;

		/// @brief Holds the renderer
		SDL_Renderer* renderer;

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
