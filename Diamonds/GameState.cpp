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
			bool x = true;
			while (x)
			{
				int rand = distribtion(generator);
				if (i == 0&&j==0)
				{
					vecDiamonds[i][j] = new Diamond(sf::Vector2f(50 * j + 25, 50 * i + 75), sf::IntRect(0, 0, 50, 50),
						&diamondTextures[3 * rand + 1], &diamondTextures[3 * rand + 2], &diamondTextures[3 * rand + 3], rand + 1);
					x = false;
				}
				else if (i == 0 && j != 0)
				{
					if (vecDiamonds[i][j - 1]->getValue() != rand+1)
					{
						vecDiamonds[i][j] = new Diamond(sf::Vector2f(50 * j + 25, 50 * i + 75), sf::IntRect(0, 0, 50, 50),
							&diamondTextures[3 * rand + 1], &diamondTextures[3 * rand + 2], &diamondTextures[3 * rand + 3], rand + 1);
						x = false;
					}
				}
				else if (i != 0 && j == 0)
				{
					if (vecDiamonds[i-1][j]->getValue() != rand+1)
					{
						vecDiamonds[i][j] = new Diamond(sf::Vector2f(50 * j + 25, 50 * i + 75), sf::IntRect(0, 0, 50, 50),
							&diamondTextures[3 * rand + 1], &diamondTextures[3 * rand + 2], &diamondTextures[3 * rand + 3], rand + 1);
						x = false;
					}
				}
				else
				{
					if (vecDiamonds[i - 1][j]->getValue() != rand+1 && vecDiamonds[i][j - 1]->getValue() != rand+1)
					{
						vecDiamonds[i][j] = new Diamond(sf::Vector2f(50 * j + 25, 50 * i + 75), sf::IntRect(0, 0, 50, 50),
							&diamondTextures[3 * rand + 1], &diamondTextures[3 * rand + 2], &diamondTextures[3 * rand + 3], rand + 1);
						x = false;
					}
				}
			}
			
			
			//std::cout << rand << "\n";
			


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

	firstI = -1, firstJ = -1, secondI = -1, secondJ = -1;
	moving = false;
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

	if (moving)
	{
		this->moveDiamonds();
	}
	else if (crushCkeck())
	{
		this->diamondsCrush();
	}
	else if (refillCheck())
	{
		this->diamondsRefill();
	}
	else
	{
		this->updateMouseposition();
		this->updateDiamonds();
	}
}

void GameState::updateTime()
{
	if (!start) return;
	this->remainingTime = "";
	time = dtClock.getElapsedTime();
	if (time.asSeconds() >= 30)
	{
		this->endState();
	}
	int currentTime = 30-static_cast<int>(this->time.asSeconds());
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
	//clearing temp variables
	

	// loop that checks if the diamond was pressed
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			vecDiamonds[i][j]->update(this->mousePos);
			if (vecDiamonds[i][j]->wasPressed())
			{
				std::cout << i << " " << j << "\n";
				//if first diamond was pressed, the timer starts
				if (this->start == false)
				{
					this->start = true;
					startGame();
				}

				if (this->firstDiamondToChange == false)
				{
					this->firstDiamondToChange = true;
					this->firstI = i;
					this->firstJ = j;
				}
				else if (this->firstDiamondToChange == true)
				{
					this->secondDiamondToChange = true;
					this->secondI = i;
					this->secondJ = j;
					
				}
				
			}
			vecDiamonds[i][j]->uncheckPressed();

		}
		//moving two diamonds if they have been pressed
		if (this->firstDiamondToChange && this->secondDiamondToChange)
		{
			if (firstI == secondI && firstJ == secondJ)
			{
				//vecDiamonds[firstI][firstJ]->uncheckPressed();
				//vecDiamonds[secondI][secondJ]->uncheckPressed();
				firstI = -1, firstJ = -1, secondI = -1, secondJ = -1;
				this->secondDiamondToChange = false;
				this->firstDiamondToChange = false;
				
			}
			else
			{
				moving = true;
				this->firstPos = vecDiamonds[firstI][firstJ]->getPosition();
				this->secondPos = vecDiamonds[secondI][secondJ]->getPosition();
			}
		}
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

bool GameState::crushCkeck()
{
	return false;
}

void GameState::diamondsRefill()
{

}

void GameState::diamondsCrush()
{

}

void GameState::moveDiamonds()
{	
	double distance = sqrt(pow(firstI - secondI, 2) + pow(firstJ - secondJ, 2));
	if (distance != 1)
	{
		std::cout <<"these diamonds cannot be changed because they are not next to each other"<< std::endl;
		moving = false;
		firstI = -1, firstJ = -1, secondI = -1, secondJ = -1;
		this->secondDiamondToChange = false;
		this->firstDiamondToChange = false;
		return;
	}
	//std::cout << secondPos.x << " " << secondPos.y << " \n";
	if (firstPos == vecDiamonds[secondI][secondJ]->getPosition()
		&& secondPos == vecDiamonds[firstI][firstJ]->getPosition())
	{

		moving = false;
		std::swap(vecDiamonds[firstI][firstJ], vecDiamonds[secondI][secondJ]);
		firstI = -1, firstJ = -1, secondI = -1, secondJ = -1;
		this->secondDiamondToChange = false;
		this->firstDiamondToChange = false;
		
		return;
	}
	//    1
	//  2  -2     <- directions
	//   -1
	int direction; //the direction of the target position of the first diamond
	if (firstI - secondI == -1) direction = -1;
	else if (firstI - secondI == 1) direction = 1;
	else if (firstJ - secondJ == 1) direction = 2;
	else direction = -2;
	vecDiamonds[firstI][firstJ]->move(direction);
	vecDiamonds[secondI][secondJ]->move(-direction);

	//std::cout << "moving first: " << firstI << " " << firstJ << "  and second: " << secondI <<" "<< secondJ << std::endl;
	//std::cout << vecDiamonds[firstI][firstJ]->getPosition().x << " " << vecDiamonds[firstI][firstJ]->getPosition().y << std::endl;
}
