#pragma once
class GUIBar
{
public:
	GUIBar( Ogre::Real xPos, Ogre::Real yPos, Ogre::Real barWidth, Ogre::Real barHeight, std::string materialName);
	virtual ~GUIBar();
	void setValue(unsigned);
protected:
	void updateBar(unsigned);
	void setupBar();
	Ogre::Real m_barMaxWidth;
	Ogre::Real m_barHeight;
	Ogre::Real m_xPos;
	Ogre::Real m_yPos;
	std::string m_barMaterial;
	std::string m_rammeMaterial;
	std::string m_glassMaterial;
	Ogre::OverlayContainer* m_ramme;
	Ogre::OverlayElement* m_bar;
	Ogre::OverlayElement* m_glass;
	Ogre::TextAreaOverlayElement* m_text;
	void initText(Ogre::OverlayContainer* parent);
	static unsigned m_count;
	std::string m_id;
};


