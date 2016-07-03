/// @file main.cpp
/// @brief Main file for program
/// @author Petra
/// @version 0.1
/// @date 2016-07-03

#include "langtonapp.h"

int main(int argc, char* argv[]) {
	LangtonApp app;
	
	for (int i = 1; i < argc; i++)
		printf("%d: %s\n", i, argv[i]);

	return app.OnExecute();
}
