#pragma once
class GUIBar
{
public:
	GUIBar( Ogre::Real xPos, Ogre::Real yPos, Ogre::Real barWidth, Ogre::Real barHeight, std::string materialName);
	virtual ~GUIBar();
	void setValue(unsigned newEnergy);
	void markBar(unsigned newEnergy);
protected:
	void updateBar(unsigned);
	void setupBar();
	Ogre::Real m_barMaxWidth;
	Ogre::Real m_barHeight;
	Ogre::Real m_xPos;
	Ogre::Real m_yPos;
	Ogre::Real m_dynamicBarScaleX;
	std::string m_barMaterial;
	std::string m_dynamicBarMarkerMaterial;
	std::string m_rammeMaterial;
	std::string m_glassMaterial;
	Ogre::PanelOverlayElement* m_ramme;
	Ogre::PanelOverlayElement* m_dynamicBar;
	Ogre::PanelOverlayElement* m_barMarker;
	Ogre::PanelOverlayElement* m_glass;
	Ogre::TextAreaOverlayElement* m_text;
	void initText(Ogre::OverlayContainer* parent);
	static unsigned m_count;
	std::string m_id;
	unsigned m_energy;
};


