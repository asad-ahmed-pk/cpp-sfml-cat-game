//
//  AI.h
//  The Meow Outing
//
//  Created by Asad Ahmed on 8/18/15.
//  Copyright (c) 2015 Asad Ahmed. All rights reserved.
//
//  The AI class for providing intelligence to computer controlled players.
//

#ifndef AI_H
#define AI_H

#include <functional>
#include <SFML/Graphics.hpp>

#include "Player.h"
#include "AnimatableEntity.h"
#include "Global_Enums.h"

class AI
{
public:
    
    // Default constructor
    AI();
    
    // Sets the target to attempt to follow and attack
    void SetTarget(Player* target);
    
    // Returns true if the AI should move and sets the nextTile param to the tile [row,col] and index
    bool NextMove(sf::Vector2i& nextTile);
    
    // Set the move request delegate to call to determine if it is possible to move to the given tile
    void SetMoveRequestDelegate(std::function<bool(const sf::Vector2i&)> moveDelegate);
    
private:
    Player* m_target;
    sf::Vector2i m_currentlyMovingToTile;
    bool m_previousCommandCompleted;
    std::function<bool(const sf::Vector2i&)> m_moveRequestDelegate;
};

#endif
