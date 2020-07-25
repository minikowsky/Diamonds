#include "Diamond.h"

Diamond::Diamond(sf::Vector2f position, sf::IntRect size, sf::Texture* idle_tex, sf::Texture* hover_tex, sf::Texture* active_tex, int value)
{
	this->diamondState = dia_IDLE;
	this->position = position;
	this->diaSprite.setPosition(position);
	this->diaSprite.setTexture(*idle_tex);
	this->diaSprite.setTextureRect(size);
	this->idleTexture = idle_tex;
	this->hoverTexture = hover_tex;
	this->activeTexture = active_tex;
	this->value = value;
	this->pressed = false;
}

Diamond::~Diamond()
{

}

const bool Diamond::isPressed() const
{
	if (this->diamondState == dia_IDLE)
		return true;
	return false;
}

const int Diamond::getValue() const
{
	return this->value;
}

const sf::Vector2f Diamond::getPosition() const
{
	return this->position;
}

void Diamond::update(const sf::Vector2i& mousePos)
{
	//Idle
	if(!pressed) this->diamondState = dia_IDLE;
	//Hover
	if (this->diaSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
	{
		if(this->diamondState == dia_IDLE)
		this->diamondState = dia_HOVER;

		//Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->pressed = true;
			this->diamondState = dia_ACTIVE;
		}
		else if (pressed)
		{
			this->pressed = false;
		}
	}
	switch (this->diamondState)
	{
	case dia_IDLE:
		this->diaSprite.setTexture(*this->idleTexture);
		break;
	case dia_HOVER:
		this->diaSprite.setTexture(*this->hoverTexture);
		break;
	case dia_ACTIVE:
		this->diaSprite.setTexture(*this->activeTexture);
		break;
	default:
		std::cout << "diamond state changing failed\n";
		break;
	}
}

void Diamond::render(sf::RenderTarget& target)
{
	target.draw(this->diaSprite);
}
