#pragma once
namespace Ogre
{
	class Ray;
	class AxisAlignedBox;
}
class OgreFix
{
public:
	static std::pair<bool, Ogre::Real> intersects(const Ogre::Ray& ray, const Ogre::AxisAlignedBox& box);
};

