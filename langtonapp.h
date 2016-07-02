#ifndef LANGTONAPP_H
#define LANGTONAPP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define INIT_SCREEN_WIDTH 500
#define INIT_SCREEN_HEIGHT 500

#define SQUARE_SIZE 100

#define LOOP_TIME (1000/60)

class LangtonApp {
	private:
		bool running = false;

		bool fullscreen = false;

		bool mouseDown = false;

		void onKeyDown(SDL_KeyboardEvent* keyEvent);

		int winX = INIT_SCREEN_WIDTH;

		int winY = INIT_SCREEN_HEIGHT;

		SDL_Window* window = NULL;

		SDL_Surface* screensurface = NULL;

		SDL_Texture* anttexture = NULL;

		SDL_Renderer* renderer;

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
