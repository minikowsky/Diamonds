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
    void render(sf::RenderTarget* target = NULL);
private:
    //fields
    sf::RectangleShape background;
    std::map<std::string, Button*> TutorialButtons;
    std::vector<sf::Texture> diamondTextures;
    std::vector<std::vector<Diamond*> >vecDiamonds;
    sf::Font* font;
    //inits
    void initGui();
};

