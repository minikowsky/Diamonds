#include "TutorialState.h"

TutorialState::TutorialState(StateData* state_data)
	:State(state_data)
{
	this->initFields();
	this->initGui();
	
}

TutorialState::~TutorialState()
{
	auto it = this->tutorialButtons.begin();
	for (it = this->tutorialButtons.begin(); it != this->tutorialButtons.end(); ++it)
	{
		delete it->second;
	}
}
void TutorialState::initGui()
{
	//Background
	this->background.setSize(static_cast<sf::Vector2f>(window->getSize()));
	this->background.setFillColor(sf::Color(70,70,70));
	//Text
	this->text.setFont(*this->font);
	this->text.setFillColor(sf::Color(200, 200, 200));
	this->text.setCharacterSize(24);
	this->text.setPosition(50.f, 120.f);


	this->tutorialButtons["<"] = new Button(sf::Vector2f(50.f, 500.f), sf::Vector2f(50.f, 50.f), this->font, "<", 30,
		sf::Color(70, 70, 70), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(26, 196, 179), sf::Color(26, 173, 159), sf::Color(26, 145, 134),15.f);

	this->tutorialButtons[">"] = new Button(sf::Vector2f(400.f, 500.f), sf::Vector2f(50.f, 50.f), this->font, ">", 30,
		sf::Color(70, 70, 70), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(26, 196, 179), sf::Color(26, 173, 159), sf::Color(26, 145, 134), 15.f);
}

void TutorialState::initFields()
{
	this->font = new sf::Font();
	if (!this->font->loadFromFile("Font/arial.ttf"))
	{
		std::cout << " error opening font file " << std::endl;
	}

	tutorialStage = 1;
	vecTexts.resize(7);
	vecTexts[0] = "";
	vecTexts[1] = "After pressing 'New game' \na 9x9 board with diamonds of \ndiferent colors will be shown";
	vecTexts[2] = "Your task is to line up \ndiamonds of the same color \nby swapping two adjacent diamonds \nto create at least a string of 3 or more \ndiamonds in the same color";
	vecTexts[3] = "When you place at least 3 diamonds, \nthey will be destroyed and \nnew diamonds will fall from above";
	vecTexts[4] = "The more rows \nof diamonds you arrange, \nthe more points you get";
	vecTexts[5] = "You have only 120 seconds for that. \nHurry up!";
	vecTexts[6] = "";
}

void TutorialState::update()
{
	this->updateMouseposition();
	for (auto& it : this->tutorialButtons)
	{
		it.second->update(this->mousePos);
	}
	if (this->tutorialButtons["<"]->wasPressed())
	{
		this->tutorialStage--;
	}
	if (this->tutorialButtons[">"]->wasPressed())
	{
		this->tutorialStage++;
	}
	this->updateText();
}

void TutorialState::updateText()
{
	switch (this->tutorialStage)
	{
	case 0:
		this->endState();
		break;
	case 1:
		text.setString(vecTexts[1]);
		break;
	case 2:
		text.setString(vecTexts[2]);
		break;
	case 3:
		text.setString(vecTexts[3]);
		break;
	case 4:
		text.setString(vecTexts[4]);
		break;
	case 5:
		text.setString(vecTexts[5]);
		break;
	case 6:
		this->endState();
		break;
	default:
		std::cout << "update_Text error :/";
		break;
	}
}

void TutorialState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	
	target->draw(this->background);
	target->draw(this->text);
	renderBtns(*target);
}

void TutorialState::renderBtns(sf::RenderTarget& target)
{
	for (auto& it : this->tutorialButtons)
	{
		it.second->render(target);
	}
}
