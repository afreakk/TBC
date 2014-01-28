#include "stdafx.h"
#include "Player.h"
#include "PlayerModelHandler.h"

Player::Player() 
: BehaviourObject(new PlayerModelHandler( PolarCoordinates( 0.0, 5.5, 0.2 )  ) )
{
}

Player::~Player()
{

}

