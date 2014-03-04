// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#include "Ogre.h"
#include "Overlay/OgreOverlay.h"
#include "Overlay/OgreOverlaySystem.h"
#include "OIS.h"
#include "boost/lexical_cast.hpp"
#include <iostream>
#include "Gorilla.h"
using namespace Ogre;
using namespace std;

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
const Real EPSILON = 10e-5f;

template<typename T>
bool float_compare(const T& a, const T& b, const T& tolerance = EPSILON)
{
	return (((a - b) < tolerance) && ((a - b) > (tolerance / -1)));
}


// TODO: reference additional headers your program requires here
