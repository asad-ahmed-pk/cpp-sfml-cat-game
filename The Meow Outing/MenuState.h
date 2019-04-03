//
//  MenuState.h
//  The Meow Outing
//
//  Created by Asad Ahmed on 8/5/15.
//  Copyright (c) 2015 Asad Ahmed. All rights reserved.
//

#ifndef MENU_STATE_H
#define MENU_STATE_H

#include <iostream>
#include "GameState.h"
#include "Button.h"

class MenuState : public GameState
{
public:
    MenuState(std::function<void(GAMESTATES state)> pushStateCallback, std::function<void()> popStateCallback, sf::RenderWindow* window);
    virtual ~MenuState();
    virtual void Start();
    
protected:
    GUI::Button m_playButton;
    GUI::Button m_quitButton;
    sf::Text m_titleText;
    sf::Text m_creditsText;
    sf::Font m_font;
    virtual void SetupUI();
    
private:
    bool IsPointInsideButton(const GUI::Button& btn, const sf::Vector2f& point) const;
    void Render();
};

#endif
