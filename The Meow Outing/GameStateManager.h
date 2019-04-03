//
//  GameStateManager.h
//  The Meow Outing
//
//  Created by Asad Ahmed on 8/5/15.
//  Copyright (c) 2015 Asad Ahmed. All rights reserved.
//

#ifndef GAME_STATE_MANAGER_H
#define GAME_STATE_MANAGER_H

#include <stack>
#include <memory>
#include <SFML/Graphics.hpp>
#include "GameState.h"


class GameStateManager
{
public:
    
    // Construct the manager with the given window
    GameStateManager(sf::RenderWindow* window);
    
    // Push a new state onto the stack
    void PushGameState(GAMESTATES state);
    
    // Pop the top state of the stack and start the bottom one if there is one.
    // If there is no other state, the window will close.
    void PopState();
    
private:
    std::stack<std::unique_ptr<GameState>> m_states;    // will take ownership, but allocated by other entities
    sf::RenderWindow* m_window;                         // no ownership
    
private:
    void PushState(std::unique_ptr<GameState> state);
};

#endif
