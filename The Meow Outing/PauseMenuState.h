//
//  PauseMenuState.h
//  The Meow Outing
//
//  Created by Asad Ahmed on 8/15/15.
//  Copyright (c) 2015 Asad Ahmed. All rights reserved.
//
//  Game state for the pause menu
//

#ifndef PAUSE_MENU_STATE_H
#define PAUSE_MENU_STATE_H

#include "MenuState.h"

class PauseMenuState : public MenuState
{
public:
    PauseMenuState(std::function<void(GAMESTATES state)> pushStateCallback, std::function<void()> popStateCallback, sf::RenderWindow* window);
    
protected:
    void SetupUI();
    
};

#endif
