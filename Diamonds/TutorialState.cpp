#include "TutorialState.h"

TutorialState::TutorialState(StateData* state_data)
	:State(state_data)
{
	this->initGui();
	this->initFields();
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
	this->background.setFillColor(sf::Color(90, 90, 90));
	//Text
	this->text.setFont(*this->font);
	this->text.setFillColor(sf::Color(60, 60, 60));
	this->text.setCharacterSize(30);
	this->text.setPosition(50.f, 120.f);


	this->tutorialButtons["<"] = new Button(sf::Vector2f(150.f, 150.f), sf::Vector2f(200.f, 50.f), this->font, "<", 30,
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 150), sf::Color(150, 150, 150, 150), sf::Color(20, 20, 20, 150), 30.f);

	this->tutorialButtons[">"] = new Button(sf::Vector2f(150.f, 250.f), sf::Vector2f(200.f, 50.f), this->font, ">", 30,
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 150), sf::Color(150, 150, 150, 150), sf::Color(20, 20, 20, 150), 50.f);
}

void TutorialState::initFields()
{
	this->font = new sf::Font();
	if (!this->font->loadFromFile("Font/arial.ttf"))
	{
		std::cout << " error opening font file " << std::endl;
	}
	tutorialStage = 1;
	vecTexts.resize(6);
	vecTexts[0] = "";
	vecTexts[1] = "text_1";
	vecTexts[2] = "text_2";
	vecTexts[3] = "text_3";
	vecTexts[4] = "text_4";
	vecTexts[5] = "";
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
		this->endState();
		break;
	default:
		std::cout << "update_Text error :/";
		break;
	}
}

void TutorialState::render(sf::RenderTarget* target)
{

}
