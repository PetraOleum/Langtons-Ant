/// @file main.cpp
/// @brief Main file for program
/// @author Petra
/// @version 1.0
/// @date 2016-07-03

#include <windows.h>
#include "langtonapp.h"

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	LangtonApp app;
	return app.OnExecute();
}
