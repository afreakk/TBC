#include "stdafx.h"
#include "PolarCoordinates.h"


PolarCoordinates::PolarCoordinates()
: theta(0)
, radius(0)
, h(0)
{
}

PolarCoordinates::PolarCoordinates(Real radian, Real distance, Real height) 
: theta(radian)
, radius(distance)
, h(height)
{
}

PolarCoordinates::~PolarCoordinates()
{
}
