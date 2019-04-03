//
//  GameState.h
//  The Meow Outing
//
//  Created by Asad Ahmed on 8/4/15.
//  Copyright (c) 2015 Asad Ahmed. All rights reserved.
//
//  Models a game state such as main menu, gameplay, win, lose or pause
//  This class is abstract and concrete game state classes must provide all the needed functionality for rendering and game logic
//

#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <iostream>
#include <functional>
#include <memory>
#include <SFML/Graphics.hpp>

// Represents the possible states
enum GAMESTATES
{
    MENU,
    GAMEPLAY,
    PAUSE,
    WIN,
    LOSE
};

class GameState
{
public:
    
    // Construct with the given function object to call for pushing the state onto the stack and the window for the gui object
    GameState(std::function<void(GAMESTATES state)> pushStateCallback, std::function<void()> popStateCallback, sf::RenderWindow* window);
    
    // Called for initialising the state
    virtual void Start() = 0;
    
    // Render the state
    virtual void Render() = 0;
    
    virtual ~GameState() {}
    
protected:
    std::function<void(GAMESTATES state)> m_pushStateCallback;
    std::function<void()> m_popStateCallback;
    sf::RenderWindow* m_window;
    bool m_shouldPopState;
    bool m_requestedPush;
};

#endif