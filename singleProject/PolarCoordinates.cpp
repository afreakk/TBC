#include "stdafx.h"
#include "PolarCoordinates.h"


PolarCoordinates::PolarCoordinates()
: r(0)
, d(0)
, h(0)
{
}

PolarCoordinates::PolarCoordinates(Real radian, Real distance, Real height) 
: r(radian)
, d(distance)
, h(height)
{
}

PolarCoordinates::~PolarCoordinates()
{
}
