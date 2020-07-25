#include "Button.h"

Button::Button(sf::Vector2f btnPosition, sf::Vector2f btnSize, sf::Font* font, std::string text, unsigned char_size, sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color, sf::Color idle_color, sf::Color hover_color, sf::Color active_color, float text_x, short unsigned id)
{
	std::cout << text_x;
	this->buttonState = btn_IDLE;
	this->id = id;
	this->shape.setPosition(btnPosition);
	this->shape.setSize(btnSize);
	this->shape.setFillColor(idle_color);

	this->text.setFont(*font);
	this->text.setString(text);
	this->text.setFillColor(text_idle_color);
	this->text.setCharacterSize(char_size);
	this->text.setPosition(
		this->shape.getPosition().x + text_x,
		this->shape.getPosition().y + 5.f
	);

	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textActiveColor = text_active_color;

	this->idleColor = idle_color;
	this->hoverColor = hover_color;
	this->activeColor = active_color;
	

}

Button::~Button()
{
}

const bool Button::isPressed() const
{
	if (this->buttonState == btn_ACTIVE) 
		return true;

	return false;
}

const std::string Button::getText() const
{
	return this->text.getString();
}

const short unsigned& Button::getId() const
{
	return this->id;
}

void Button::update(const sf::Vector2i& mousePos)
{
	//std::cout << mousePos.x << " " << mousePos.y << "\n";
	//Idle
	this->buttonState = btn_IDLE;
	//std::cout << shape.getGlobalBounds().height<<" "<< shape.getGlobalBounds().width<<" "<< shape.getGlobalBounds().left<<" "<< shape.getGlobalBounds().top<<"\n";
	//Hover
	if (this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
	{
		this->buttonState = btn_HOVER;

		//Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = btn_ACTIVE;
		}
	}
	switch (this->buttonState)
	{
	case btn_IDLE:
		this->shape.setFillColor(this->idleColor);
		this->text.setFillColor(this->textIdleColor);
		break;
	case btn_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->textHoverColor);
		break;
	case btn_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->text.setFillColor(this->textActiveColor);
		break;
	default:
		this->shape.setFillColor(sf::Color::Blue);
		this->text.setFillColor(sf::Color::Red);
		break;
	}
}

void Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}
