//
//  AI.cpp
//  The Meow Outing
//
//  Created by Asad Ahmed on 8/18/15.
//  Copyright (c) 2015 Asad Ahmed. All rights reserved.
//


#include <iostream>
#include "AI.h"

// Default ctor
AI::AI() : m_target(nullptr), m_previousCommandCompleted(false)
{
    
}

// Set the target for this AI to follow
void AI::SetTarget(Player *target)
{
    if (target != nullptr){
        m_target = target;
    }
}

// Set the move delegate
void AI::SetMoveRequestDelegate(std::function<bool (const sf::Vector2i &)> moveDelegate)
{
    m_moveRequestDelegate = moveDelegate;
}

// Determine the next tile to move to if the previous command has been carried out
bool AI::NextMove(sf::Vector2i &nextTile)
{
    if (m_previousCommandCompleted){
        m_previousCommandCompleted = false;
        
        // determine where the player is and attempt to move
        
    }
}


