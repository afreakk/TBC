#pragma once
struct PlayerStatus
{
	unsigned energy;
	unsigned health;
	PlayerStatus(unsigned e, unsigned h) :energy(e), health(h)
	{}
};