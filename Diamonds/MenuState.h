#pragma once
#include "State.h"
class MenuState :
    public State
{
public:
    MenuState(StateData* state_data);
    virtual ~MenuState();

    //methods
    void updateButtons();
    void update();
    void renderButtons();
    void render();

private:
    sf::Texture backgroundTex;
    sf::Sprite background;


    //methods
    void initFields();
};

