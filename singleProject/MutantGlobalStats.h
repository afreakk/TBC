#pragma once
class MutantGlobalStats : public Ogre::Singleton<MutantGlobalStats>
{
public:
	MutantGlobalStats();
	~MutantGlobalStats();
	const Ogre::Real& getWalkSpeed() const;
	const Ogre::Real& getAttackDistance() const;
	const Ogre::Real& getLERPSpeed() const;
	const Ogre::Real& getRangedCooldown() const;
private:
	void parseScript();
	Ogre::Real m_walkSpeed;
	Ogre::Real m_attackDistance;
	Ogre::Real m_LERPSpeed;
	Ogre::Real m_rangedCooldown;
};

