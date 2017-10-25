#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <Windows.h>
#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "MyApplication.hpp"


int main(int argc, char *argv[])
{
	sdx::MyApplication app;
	//sdx::WindowSettings settings;
	app.Init("Deferred Shaders");
	app.Run();

	return EXIT_SUCCESS;
}