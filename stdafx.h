// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define _CRTDBG_MAP_ALLOC

#include <windows.h>
#include <xinput.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <stdlib.h>
#include <crtdbg.h>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <unordered_map>
#include <typeinfo>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <fstream>


// TODO: reference additional headers your program requires here
// SDL libs
#pragma comment(lib, "sdl2.lib")
#pragma comment(lib, "SDL2main.lib")

// OpenGL libs
#pragma comment (lib,"opengl32.lib")
#pragma comment (lib,"Glu32.lib")

// SDL extension libs 
#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "SDL2_ttf.lib")
#pragma comment(lib, "SDL2_mixer.lib")
#pragma comment(lib, "Box2D.lib")
#pragma comment(lib, "XInput.lib")

//SDL
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <GL\GLU.h>

//Box2D
#include <Box2D/Box2D.h>

//Framework files
#include "Framework/Framework.h"
#include "Framework/Helpers/MathHelpers.h"
#include "Application/GameApp.h"
#include "Framework/Helpers/Time.h"
#include "Framework/Helpers/Debug.h"