#pragma once
enum class ButtonType
{
    play,
    options,
    quit,
    none,
    windowed,
    music,
    backToMenu,
};
class MainMenuButton
{
public:
	MainMenuButton(){}
	MainMenuButton(Gorilla::Layer* layer, Ogre::Real left, Ogre::Real top, Ogre::Real width, Ogre::Real height, std::string spriteName, 
		ButtonType buttonType);
	~MainMenuButton();
	void selected(bool selected);
	void animateClick();
	ButtonType getType();
	void addSpriteName(const std::string& spriteName);
private:
	Gorilla::Rectangle* m_rectangle;
	ButtonType m_btnType;

	std::vector<std::string> m_spriteNames;
	std::vector<std::string>::iterator m_currentSpriteName;
	static Gorilla::Colours::Colour s_inactiveColor;
	static Gorilla::Colours::Colour s_activeColour;
};

