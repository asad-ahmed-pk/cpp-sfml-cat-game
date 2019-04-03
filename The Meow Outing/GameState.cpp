//
//  GameState.cpp
//  The Meow Outing
//
//  Created by Asad Ahmed on 8/4/15.
//  Copyright (c) 2015 Asad Ahmed. All rights reserved.
//
//  Models a game state such as main menu, gameplay, win, lose or pause
//

#include "GameState.h"
#include "ResourcePath.hpp"
#include <cassert>

// Constructor
GameState::GameState(std::function<void(GAMESTATES state)> pushStateCallback, std::function<void()> popStateCallback, sf::RenderWindow* window) : m_pushStateCallback(pushStateCallback), m_popStateCallback(popStateCallback), m_shouldPopState(false), m_requestedPush(false)
{
    m_window = window;
}