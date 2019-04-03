//
//  GameStateManager.cpp
//  The Meow Outing
//
//  Created by Asad Ahmed on 8/5/15.
//  Copyright (c) 2015 Asad Ahmed. All rights reserved.
//

#include "GameStateManager.h"
#include "MenuState.h"
#include "Game.h"
#include "PauseMenuState.h"

// Construct with the given window
GameStateManager::GameStateManager(sf::RenderWindow* window)
{
    m_window = window;
}

// Push a new state onto stack and start it up
// The state manager will take control for the memory management from here on for the state
void GameStateManager::PushGameState(GAMESTATES state)
{
    std::function<void(GAMESTATES state)> pushCallback = std::bind(&GameStateManager::PushGameState, this, std::placeholders::_1);
    std::function<void()> popCallback = std::bind(&GameStateManager::PopState, this);
    
    std::unique_ptr<GameState> newState = nullptr;
    
    // Create the respective game state and push onto the stack
    switch (state)
    {
        case GAMESTATES::MENU:
            newState = std::unique_ptr<MenuState>(new MenuState(pushCallback, popCallback, m_window));
            PushState(std::move(newState));
            break;
            
        case GAMESTATES::GAMEPLAY:
            newState = std::unique_ptr<Game>(new Game(pushCallback, popCallback, m_window));
            PushState(std::move(newState));
            break;
            
        case GAMESTATES::PAUSE:
            newState = std::unique_ptr<PauseMenuState>(new PauseMenuState(pushCallback, popCallback, m_window));
            PushState(std::move(newState));
            
        default:
            break;
    }
}

// Creates a state and pushes it onto the stack
void GameStateManager::PushState(std::unique_ptr<GameState> state)
{
    m_states.push(std::move(state));
    m_states.top()->Start();
}

// Pops the top state of the stack if there is one
void GameStateManager::PopState()
{
    if(!m_states.empty()){
        m_states.pop();
    }
    
    // Start the next state in the stack if there is one
    if(!m_states.empty()){
        m_states.top()->Start();
    }
    else{
        m_window->close();
    }
}