#include "stdafx.h"
#include "Player.h"
#include "../ModelBehaviour/ModelHandlerPlayer.h"

Player::Player() 
: BehaviourObject(new ModelHandlerPlayer( PolarCoordinates( 0.0, 5.75, 0.2 )  ) )
{
}

Player::~Player()
{

}

