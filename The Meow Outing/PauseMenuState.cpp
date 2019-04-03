//
//  PauseMenuState.cpp
//  The Meow Outing
//
//  Created by Asad Ahmed on 8/15/15.
//  Copyright (c) 2015 Asad Ahmed. All rights reserved.
//

#include "PauseMenuState.h"

// Constructor
PauseMenuState::PauseMenuState(std::function<void(GAMESTATES state)> pushStateCallback, std::function<void()> popStateCallback, sf::RenderWindow* window) : MenuState(pushStateCallback, popStateCallback, window)
{
    
}

// Overriden setup ui to change the button text and title, but similar look to a main menu
void PauseMenuState::SetupUI()
{
    MenuState::SetupUI();
    
    // change button text
    m_quitButton.SetText("Return to menu");
    
    // change the title and remove the credits text
    m_titleText.setString("Game Paused");
    m_creditsText.setString(" ");
}

