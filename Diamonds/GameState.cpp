#include "GameState.h"

GameState::GameState(StateData* state_data)
	:State(state_data)
{
	this->initFields();
	this->initGui();
	this->initDiamonds();
	this->startGame();
}

GameState::~GameState()
{
	delete this->font;
}

void GameState::initDiamonds()
{
	
}

void GameState::initGui()
{
	//background
	this->background.setSize(static_cast<sf::Vector2f>(window->getSize()));
	this->background.setFillColor(sf::Color(232, 232, 232));

	//timer
	this->timerBackground.setSize(sf::Vector2f(150.f, 50.f));
	this->timerBackground.setPosition(sf::Vector2f(175.f, 25.f));
	this->timerBackground.setFillColor(sf::Color(60, 60, 60));

	this->timerText.setFont(*this->font);
	this->timerText.setString(remainingTime);
	this->timerText.setFillColor(sf::Color::White);
	this->timerText.setCharacterSize(30);
	this->timerText.setPosition(
		this->timerBackground.getPosition().x + (this->timerBackground.getGlobalBounds().width / 3.f),
		this->timerBackground.getPosition().y + 5.f);
	
}

void GameState::initFields()
{
	this->font = new sf::Font(); 
	if (!font->loadFromFile("Font/arial.ttf"))
	{
		std::cout << " error opening font file " << std::endl;
	}
	start = false;
	vecDiamonds.resize(9);
	vecIntDiamonds.resize(9);
	for (int i = 0; i < 9; i++)
	{
		vecDiamonds[i].resize(9);
		vecIntDiamonds[i].resize(9);
	}
}
void GameState::update()
{
	this->updateTime();
	this->updateMouseposition();
	
	if (refillCheck())
		this->diamondsRefill();
	else
		this->updateDiamonds();
}

void GameState::updateTime()
{
	this->remainingTime = "";
	time = dtClock.getElapsedTime();
	if (time.asSeconds() >= 15)
	{
		this->endState();
	}
	int currentTime = 15-static_cast<int>(this->time.asSeconds());
	int minutes = currentTime / 60;
	this->remainingTime += std::to_string(minutes);
	this->remainingTime += ":";
	int seconds = currentTime % 60;
	this->remainingTime += std::to_string(seconds);
	//std::cout << remainingTime << std::endl;
	timerText.setString(remainingTime);
}

void GameState::updateDiamonds()
{
	
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			vecDiamonds[i][j]->update(this->mousePos);
		}
		//TODO:
	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	//this->background.setFillColor(sf::Color::White);
	target->draw(this->background);
	target->draw(this->timerBackground);
	target->draw(this->timerText);
	this->renderDiamonds(*target);
}

void GameState::renderDiamonds(sf::RenderTarget& target)
{

}

void GameState::startGame()
{
	dtClock.restart();
}

bool GameState::refillCheck()
{
	bool needToRefill = false;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (vecDiamonds[i][j]->getValue() == 0)
				needToRefill = true;
		}
	}
	return needToRefill;
}

void GameState::diamondsRefill()
{

}
