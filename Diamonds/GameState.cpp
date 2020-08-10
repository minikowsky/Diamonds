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
						&diamondTextures[3 * rand + 1], &diamondTextures[3 * rand + 2], &diamondTextures[3 * rand + 3],&diamondTextures[0], rand + 1);
					x = false;
				}
				else if (i == 0 && j != 0)
				{
					if (vecDiamonds[i][j - 1]->getValue() != rand+1)
					{
						vecDiamonds[i][j] = new Diamond(sf::Vector2f(50 * j + 25, 50 * i + 75), sf::IntRect(0, 0, 50, 50),
							&diamondTextures[3 * rand + 1], &diamondTextures[3 * rand + 2], &diamondTextures[3 * rand + 3], &diamondTextures[0], rand + 1);
						x = false;
					}
				}
				else if (i != 0 && j == 0)
				{
					if (vecDiamonds[i-1][j]->getValue() != rand+1)
					{
						vecDiamonds[i][j] = new Diamond(sf::Vector2f(50 * j + 25, 50 * i + 75), sf::IntRect(0, 0, 50, 50),
							&diamondTextures[3 * rand + 1], &diamondTextures[3 * rand + 2], &diamondTextures[3 * rand + 3], &diamondTextures[0], rand + 1);
						x = false;
					}
				}
				else
				{
					if (vecDiamonds[i - 1][j]->getValue() != rand+1 && vecDiamonds[i][j - 1]->getValue() != rand+1)
					{
						vecDiamonds[i][j] = new Diamond(sf::Vector2f(50 * j + 25, 50 * i + 75), sf::IntRect(0, 0, 50, 50),
							&diamondTextures[3 * rand + 1], &diamondTextures[3 * rand + 2], &diamondTextures[3 * rand + 3], &diamondTextures[0], rand + 1);
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
	this->background.setFillColor(sf::Color(240,240,240));

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

	//scoreboard
	this->scoreBackground.setSize(sf::Vector2f(145.f, 50.f));
	this->scoreBackground.setPosition(sf::Vector2f(25.f, 20.f));
	this->scoreBackground.setFillColor(sf::Color(60, 60, 60, 60));

	this->scoreText.setFont(*this->font);
	this->scoreText.setString("0");
	this->scoreText.setFillColor(sf::Color::White);
	this->scoreText.setCharacterSize(30);
	this->scoreText.setPosition(
		this->scoreBackground.getPosition().x + (this->scoreBackground.getGlobalBounds().width / 3.f),
		this->scoreBackground.getPosition().y + 5.f);
	
}

void GameState::initFields()
{
	this->font = new sf::Font(); 
	if (!font->loadFromFile("Font/arial.ttf"))
	{
		std::cout << " error opening font file " << std::endl;
	}
	
	this-> start = false;
	this-> score = 0;
	this->falling = false;
	vecDiamonds.resize(9);
	for (int i = 0; i < 9; i++)
	{
		vecDiamonds[i].resize(9);
	}

	firstI = -1, firstJ = -1, secondI = -1, secondJ = -1;
	this->moving = false;
	this->returned = false;
	this->counter = 0;
	diamondTextures.resize(13);
	diamondTextures[0].loadFromFile("Assets/crushed.png");
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
	if (falling) 
	{

		// if there are some empty places int the middle, diamonds that are higher fall
		this->fallingDiamonds();
	}
	else if (moving)
	{
		// if user move diamond, there appears animation of moving
		this->moveDiamonds();
	}
	else if (refillCheck())// <- this method searches for empty places, if some appears in the middle, then the falling begins
	{                                                                // if some appears on the top row, then diamond refilling begins
		
		//if on the top row are empty places, there appears new diamond
		this->diamondsRefill();
	}
	else if (crushCkeck())// <- this method searches for min. 3 diamonds of the same type in a row or in a column
	{
		//if there are min. 3 diamonds in a row or in a column, then these diamonds are crushing
		this->diamondsCrush();
	}
	else
	{
		//if there are not falling or moving action and there are not diamonds to crush or empty places, then user can do sth ;p
		this->updateMouseposition();
		this->updateDiamonds();
	}
}

void GameState::updateTime()
{
	if (!start) return;
	this->remainingTime = "";
	time = dtClock.getElapsedTime();
	if (time.asSeconds() >= 120)
	{
		this->endState();
	}
	int currentTime = 120-static_cast<int>(this->time.asSeconds());
	int minutes = currentTime / 60;
	this->remainingTime += std::to_string(minutes);
	this->remainingTime += ":";
	int seconds = currentTime % 60;
	this->remainingTime += std::to_string(seconds);
	//std::cout << remainingTime << std::endl;
	timerText.setString(remainingTime);

	scoreText.setString(std::to_string(this->score));
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

	target->draw(this->scoreBackground);
	target->draw(this->scoreText);

	this->renderDiamonds(*target);
}

void GameState::renderDiamonds(sf::RenderTarget& target)
{
	for (int i = 8; i >= 0; i--)
	{
		for (int j = 8; j >= 0; j--)
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
			{
				if (i == 0)
				{
					needToRefill = true;
				}
				else
				{
					falling = true;
				}
			}
				
		}
	}
	
	return needToRefill;
}

bool GameState::crushCkeck() 
{
	this->beginningOfCrush = sf::Vector2i(-1, -1);
	this->endOfCrush = sf::Vector2i(-1, -1);
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			
			//down
			if (i<=6 && vecDiamonds[i][j]->getValue() == vecDiamonds[i + 1][j]->getValue())
			{
				if (vecDiamonds[i+1][j]->getValue() == vecDiamonds[i + 2][j]->getValue())
				{
					if (i <= 5)
					{
						if (vecDiamonds[i + 2][j]->getValue() == vecDiamonds[i + 3][j]->getValue())
						{
							if (i <= 4)
							{
								if (vecDiamonds[i + 3][j]->getValue() == vecDiamonds[i + 4][j]->getValue())
								{
									//5 in a row
									beginningOfCrush = sf::Vector2i(i, j);
									endOfCrush = sf::Vector2i(i + 4, j);
									return true;
								}
							}
							//four in a row
							beginningOfCrush = sf::Vector2i(i, j);
							endOfCrush = sf::Vector2i(i + 3, j);
							return true;
						}
					}
					//3 in a row
					beginningOfCrush = sf::Vector2i(i, j);
					endOfCrush = sf::Vector2i(i + 2, j);
					return true;
				}
			
			
			}
			//right
			if (j<=6 && vecDiamonds[i][j]->getValue() == vecDiamonds[i][j+1]->getValue())
			{
				if (vecDiamonds[i][j+1]->getValue() == vecDiamonds[i][j+2]->getValue())
				{
					if (j <= 5)
					{
						if (vecDiamonds[i][j+2]->getValue() == vecDiamonds[i][j+3]->getValue())
						{
							if (j <= 4)
							{
								if (vecDiamonds[i][j+3]->getValue() == vecDiamonds[i][j+4]->getValue())
								{
									//5 in a row
									beginningOfCrush = sf::Vector2i(i, j);
									endOfCrush = sf::Vector2i(i, j+4);
									return true;
								}
							}
							//four in a row
							beginningOfCrush = sf::Vector2i(i, j);
							endOfCrush = sf::Vector2i(i, j+3);
							return true;
						}
					}
					//3 in a row
					beginningOfCrush = sf::Vector2i(i, j);
					endOfCrush = sf::Vector2i(i, j+2);
					return true;
				}
			}
		}
	}
	falling = false;
	return false;
}

void GameState::diamondsRefill()
{
	std::random_device r;
	std::default_random_engine generator(r());
	std::uniform_int_distribution<int> distribtion(0, 3);
	for (int j = 0; j < 9; j++)
	{
		if (vecDiamonds[0][j]->getValue() == 0)
		{
			vecDiamonds[0][j] = NULL;
			int rand = distribtion(generator);
			vecDiamonds[0][j] = new Diamond(sf::Vector2f(50 * j + 25,  75), sf::IntRect(0, 0, 50, 50),
				&diamondTextures[3 * rand + 1], &diamondTextures[3 * rand + 2], &diamondTextures[3 * rand + 3], &diamondTextures[0], rand + 1);
		}
	}
}

void GameState::diamondsCrush()
{
	int x = 0;
	if (beginningOfCrush.x != endOfCrush.x)
	{
		for (int i = beginningOfCrush.x; i <= endOfCrush.x; i++)
		{
			vecDiamonds[i][beginningOfCrush.y]->crushDiamond();
			this->score += (i - beginningOfCrush.x) * 10 + 10;
			x += (i - beginningOfCrush.x) * 10 + 10;
		}
		falling = true;
		std::cout << x << std::endl;
	}
	else if (beginningOfCrush.y != endOfCrush.y)
	{
		for (int j = beginningOfCrush.y; j <= endOfCrush.y; j++)
		{
			vecDiamonds[beginningOfCrush.x][j]->crushDiamond();
			this->score += (j - beginningOfCrush.y) * 10 + 10;
			x += (j - beginningOfCrush.y) * 10 + 10;

		}
		falling = true;
		std::cout << x << std::endl;
	}
	else
	{
		std::cout << "Something went wrong, error\t";
	}
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
		if (!crushCkeck()&&!returned)
		{
			std::swap(firstI, secondI);
			std::swap(firstJ, secondJ);
			std::swap(firstPos, secondPos);
			moving = true;
			returned = true;
		}
		else
		{
			firstI = -1, firstJ = -1, secondI = -1, secondJ = -1;
			this->secondDiamondToChange = false;
			this->firstDiamondToChange = false;
			returned = false;
		}
		
		
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

void GameState::fallingDiamonds()
{
	if (this->counter == 100)
	{ 
		//TODO:

		this->counter = 0;
		
		bool end = false;
		this->falling = false;
		for (int i = 8; i > 0; i--)
		{
			for (int j = 0; j < 9; j++)
			{
				if (vecDiamonds[i][j]->getValue() == 0)
				{
					end = true;
					for (int ii = i; ii > 0; ii--)
					{
						std::swap(vecDiamonds[ii][j], vecDiamonds[ii - 1][j]);
					}
				}
			}
			if (end == true)
			{
				break;
			}

		}
		return;
	}

	bool end = false;
	for (int i = 8; i >= 0; i--)
	{
		for (int j = 0; j <= 8; j++)
		{
			if (vecDiamonds[i][j]->getValue() == 0)
			{
				end = true;
				for (int ii = i-1; ii >= 0; ii--)
				{
					vecDiamonds[ii][j]->move(-1);
				}
			}
		}
		if (end == true)
		{
			break;
		}

	}
	this->counter++;
}
