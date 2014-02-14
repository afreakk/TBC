#pragma once
struct PlayerStatus
{
	unsigned energy;
	unsigned markEnergy;
	unsigned maxEnergy;
	unsigned health;
	unsigned markHealth;
	unsigned maxHealth;
	PlayerStatus() :energy(0), health(0), markEnergy(0), markHealth(0), maxHealth(0), maxEnergy(0)
	{}
};