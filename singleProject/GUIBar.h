#pragma once
class GUIBar
{
public:
	GUIBar( Ogre::Real xPos, Ogre::Real yPos, Ogre::Real barWidth, Ogre::Real barHeight, std::string materialName);
	virtual ~GUIBar();
	void setValue(unsigned);
protected:
	void setupBar();
	const Ogre::Vector2& m_resolution;
	std::string m_materialName;
	Ogre::Real m_barMaxWidth;
	Ogre::Real m_barHeight;
	Ogre::Real m_xPos;
	Ogre::Real m_yPos;
	Ogre::OverlayContainer* m_bar;
	Ogre::TextAreaOverlayElement* m_text;
	static unsigned m_count;
	std::string m_id;
};


