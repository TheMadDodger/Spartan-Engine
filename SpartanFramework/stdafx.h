// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define _CRTDBG_MAP_ALLOC
#define NOMINMAX

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
#include <algorithm>
#include <fstream>
#include <functional>
#include <limits>
#include <math.h>
#include <assert.h>
#include <sstream>
#include <algorithm>
#include <random>
#include <utility>
#include <type_traits>
#include <stdexcept>
#include <deque>

// TODO: reference additional headers your program requires here
// SDL libs
#pragma comment(lib, "sdl2.lib")
#pragma comment(lib, "SDL2main.lib")

// OpenGL libs
#pragma comment (lib,"opengl32.lib")
#pragma comment (lib,"Glu32.lib")
#pragma comment (lib,"glew32.lib")

// ASSIMP
#ifdef _DEBUG
#pragma comment (lib,"assimp-vc141-mtd.lib")
#pragma comment (lib,"Bullet3Collision_Debug.lib")
#pragma comment (lib,"Bullet3Common_Debug.lib")
#pragma comment (lib,"Bullet3Dynamics_Debug.lib")
#pragma comment (lib,"Bullet3Geometry_Debug.lib")
#pragma comment (lib,"BulletCollision_Debug.lib")
#pragma comment (lib,"BulletDynamics_Debug.lib")
#pragma comment (lib,"LinearMath_Debug.lib")
#else
#pragma comment (lib,"assimp-vc141-mt.lib")
#pragma comment (lib,"Bullet3Collision.lib")
#pragma comment (lib,"Bullet3Common.lib")
#pragma comment (lib,"Bullet3Dynamics.lib")
#pragma comment (lib,"Bullet3Geometry.lib")
#pragma comment (lib,"BulletCollision.lib")
#pragma comment (lib,"BulletDynamics.lib")
#pragma comment (lib,"LinearMath.lib")
#endif // _DEBUG

// SDL extension libs 
#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "SDL2_ttf.lib")
#pragma comment(lib, "SDL2_mixer.lib")
#pragma comment(lib, "Box2D.lib")
#pragma comment(lib, "XInput.lib")

//SDL
#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_thread.h>

//Box2D
#include <Box2D.h>

//Framework files
#include "Framework.h"
#include "MathHelpers.h"
#include "Time.h"
#include "BaseGame.h"
#include "Debug.h"

// ASSIMP
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// Bullet
#include <btBulletDynamicsCommon.h>