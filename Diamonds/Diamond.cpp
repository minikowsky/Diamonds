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
	pressed = false;
	hasJustBeenPressed = false;
}

Diamond::~Diamond()
{

}

const bool Diamond::isPressed() const
{
	if (this->diamondState == dia_ACTIVE)
		return true;
	return false;
}

const int Diamond::getValue() const
{
	return this->value;
}

const sf::Vector2f Diamond::getPosition() const
{
	return diaSprite.getPosition();
	//return this->position;
}

const bool Diamond::wasPressed() const
{
	if (this->hasJustBeenPressed)
		return true;

	return false;
}
//    1
//  2  -2     <- directions
//   -1
void Diamond::move(int x)
{
	switch (x)
	{
	case -1:
		this->diaSprite.move(sf::Vector2f(0.f, 1.f));
		this->position.y += 0.1f;
		break;
	case 1:
		this->diaSprite.move(sf::Vector2f(0.f, -1.f));
		this->position.y += -0.1f;
		break;
	case 2:
		this->diaSprite.move(sf::Vector2f(-1.f, 0.f));
		this->position.x += -0.1f;
		break;
	case -2:
		this->diaSprite.move(sf::Vector2f(1.f, 0.f));
		this->position.x += 0.1f;
		break;
	default:
		std::cout << "sth went wrong :/ \n";
		break;
	}
}

void Diamond::uncheckPressed()
{
	this->hasJustBeenPressed = false;
}

void Diamond::update(const sf::Vector2i& mousePos)
{
	//Idle
	this->diamondState = dia_IDLE;
	
	//Hover
	if (this->diaSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
	{
		this->diamondState = dia_HOVER;

		//Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->diamondState = dia_ACTIVE;
			pressed = true;
		}
		else if (pressed)
		{
			pressed = false;
			hasJustBeenPressed = true;
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
