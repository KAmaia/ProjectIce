#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <math.h>
#include <assert.h>

#include <boost/unordered_map.hpp>
#include <boost/lexical_cast.hpp>

#include "stdio.h"

#define _TO_STRING(value) #value
#define TO_STRING(value) _TO_STRING(value)

#include "engine/log/LogSystem.h"

/* Asserting helpers */
#define _ASSERT_RANGE(p_value,p_max) assert(p_value >= 0); assert(p_value < p_max);

/* Settings for world generation, size, etc */

#define ROOM_WIDTH 80
#define ROOM_HEIGHT 20

#define WORLD_WIDTH 10
#define WORLD_HEIGHT 10
#define WORLD_DEPTH 10
#define WORLD_WATER_LEVEL 2

typedef std::string String;

/* If no render engine has defined, lets define the default one */

#ifndef TERMRENDER
#ifndef NULLRENDER
#ifndef SFMLRENDER

#ifdef WINDOWS
#define NULLRENDER
#else
#define TERMRENDER
#endif

#endif
#endif
#endif

/* --- */

#ifndef PRECOMPILED_H
#define PRECOMPILED_H

//TODO: wtf is this (2013-08-22)
#include "engine/EngineSystem.h"

#endif
