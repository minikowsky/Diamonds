#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <map>
enum diamond_states { dia_IDLE = 0, dia_HOVER, dia_ACTIVE};
class Diamond
{
public:
	Diamond(sf::Vector2f position, sf::IntRect size,
		sf::Texture* idle_tex, sf::Texture* hover_tex, sf::Texture* active_tex,
		sf::Texture* crushed_tex,int value);
		//value : red-1, green-2, blue-3, yellow-4
	virtual ~Diamond();
	//accessors
	const bool isPressed() const;
	const int getValue() const;
	const sf::Vector2f getPosition() const;
	const bool wasPressed() const;
	void move(int x);
	void setPosition(sf::Vector2f);
	void uncheckPressed();
	void crushDiamond();
	void update(const sf::Vector2i& mousePos);
	void render(sf::RenderTarget& target);
private:
	short unsigned diamondState;
	int value;
	bool pressed;
	bool hasJustBeenPressed;
	sf::Sprite diaSprite;
	sf::Vector2f position;
	sf::Texture* idleTexture;
	sf::Texture* hoverTexture;
	sf::Texture* activeTexture;
	sf::Texture* crushedTexture;
};

