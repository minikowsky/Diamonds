#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
enum button_states{btn_IDLE=0,btn_HOVER,btn_ACTIVE};
class Button
{
public:
	Button(sf::Vector2f btnPosition, sf::Vector2f btnSize,sf::Font* font,std::string text,unsigned char_size,
		sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
		sf::Color idle_color, sf::Color hover_color, sf::Color active_color, short unsigned id=0);
	~Button();

	//accessors
	const bool isPressed() const;
	const std::string getText() const;
	const short unsigned& getId() const;

	void update(const sf::Vector2i& mousePos);
	void render(sf::RenderTarget& target);
private:

	short unsigned buttonState;
	short unsigned id;
	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	sf::Color textIdleColor;
	sf::Color textHoverColor;
	sf::Color textActiveColor;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;


};

