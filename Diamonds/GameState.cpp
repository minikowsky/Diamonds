#include "GameState.h"

GameState::GameState(StateData* state_data)
	:State(state_data)
{
	this->initFields();
	this->initGui();
	this->initDiamonds();
}

GameState::~GameState()
{
	delete this->font;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			delete vecDiamonds[i][j];
		}
	}
}

void GameState::initDiamonds()
{
	std::random_device r;
	std::default_random_engine generator(r());
	std::uniform_int_distribution<int> distribtion(0, 3);

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			int rand = distribtion(generator);
			//std::cout << rand << "\n";
			vecDiamonds[i][j] = new Diamond(sf::Vector2f(50 * j + 25, 50 * i + 75), sf::IntRect(0, 0, 50, 50), 
				&diamondTextures[3 * rand + 1], &diamondTextures[3 * rand + 2], &diamondTextures[3 * rand + 3], rand+1);


		}
	}
}

void GameState::initGui()
{
	//background
	this->background.setSize(static_cast<sf::Vector2f>(window->getSize()));
	this->background.setFillColor(sf::Color(232, 232, 232));

	//timer
	this->timerBackground.setSize(sf::Vector2f(150.f, 50.f));
	this->timerBackground.setPosition(sf::Vector2f(175.f, 20.f));
	this->timerBackground.setFillColor(sf::Color(60, 60, 60,60));

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
	for (int i = 0; i < 9; i++)
	{
		vecDiamonds[i].resize(9);
	}

	firstI = 0, firstJ = 0, secondI = 0, secondJ = 0;

	diamondTextures.resize(13);
	std::vector<std::string> colors = { "red","green","blue","yellow" };
	for (int i = 0; i < 4; i++)//four colors
	{						//three states
		diamondTextures[i * 3+1].loadFromFile("Assets/" + colors[i] + "_idle.png");
		diamondTextures[i * 3+2].loadFromFile("Assets/" + colors[i] + "_hover.png");
		diamondTextures[i * 3+3].loadFromFile("Assets/" + colors[i] + "_active.png");
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
	if (!start) return;
	this->remainingTime = "";
	time = dtClock.getElapsedTime();
	if (time.asSeconds() >= 20)
	{
		this->endState();
	}
	int currentTime = 20-static_cast<int>(this->time.asSeconds());
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
			if (vecDiamonds[i][j]->isPressed())
			{
				if (this->start == false)
				{
					start = true;
					startGame();
				}
				if (this->firstDiamondToChange == false)
				{
					this->firstDiamondToChange = true;
					this->firstI = i;
					this->firstJ = j;
				}
				else if (this->secondDiamondToChange == false && firstI != i && firstJ != j)
				{
					this->secondDiamondToChange = true;
					this->secondI = i;
					this->secondJ = j;
					moveDiamonds();
				}
				
			}


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
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			vecDiamonds[i][j]->render(target);
		}
	}
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

void GameState::moveDiamonds()
{
}
