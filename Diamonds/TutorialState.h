#pragma once
#include "State.h"
#include "Button.h"
#include "Diamond.h"
#include <map>

class TutorialState :
    public State
{
public:
    //ctor/dtor
    TutorialState(StateData* state_data);
    virtual ~TutorialState();

    //public methods
    void update();
    void updateText();
    void render(sf::RenderTarget* target = NULL);
    void renderBtns(sf::RenderTarget& target);
private:
    //fields
    sf::RectangleShape background;
    std::map<std::string, Button*> tutorialButtons;
    std::vector<sf::Texture> diamondTextures;
    std::vector<std::vector<Diamond*> >vecDiamonds;
    sf::Font *font;
    sf::Text text;
    int tutorialStage;
    std::vector<std::string> vecTexts;
    sf::Texture boardTex, three1Tex,three2Tex;
    sf::Sprite boardSprite, three1Sprite,three2Sprite;
    //inits
    void initGui();
    void initFields();

    
};

