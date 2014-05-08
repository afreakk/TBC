#pragma once
class MainMenuButton
{
public:
	MainMenuButton(){}
	MainMenuButton(Gorilla::Layer* layer, Ogre::Real left, Ogre::Real top, Ogre::Real width, Ogre::Real height, std::string name);
	~MainMenuButton();
	void selected(bool selected);
private:
	Gorilla::Rectangle* m_rectangle;
};

