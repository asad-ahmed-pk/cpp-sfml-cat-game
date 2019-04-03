//
//  Hud.cpp
//  The Meow Outing
//
//  Created by Asad Ahmed on 8/4/15.
//  Copyright (c) 2015 Asad Ahmed. All rights reserved.
//

#include "Hud.h"
#include <string>
#include <cstdlib>
#include "ResourcePath.hpp"

const std::string fontname("cinnamon_cake.ttf");
const int TEXT_RIGHT_PADDING = 10;
const int TEXT_UP_PADDING = 10;

// Default Constructor
Hud::Hud() : m_score(0)
{
    // Load up the font
    if (!m_font.loadFromFile(resourcePath() + fontname)){
        std::exit(-3);
    }
    
    // Setup text attributes
    m_text.setFont(m_font);
}

// Set the score to draw
void Hud::SetScore(int score)
{
    m_score = score;
}

// Draw out the hud using the render target
void Hud::Draw(sf::RenderTarget &window)
{
    m_text.setString("Score: " + std::to_string(m_score));
    
    // Calculate position to render in top right corner of screen
    float viewRightCorner = window.getView().getCenter().x + (window.getView().getSize().x / 2.0);
    float viewTopCorner = window.getView().getCenter().y - (window.getView().getSize().y / 2.0);
    
    //float x = window.getView().getSize().x - m_text.getLocalBounds().width - TEXT_RIGHT_PADDING;
    float x = viewRightCorner - m_text.getLocalBounds().width - TEXT_RIGHT_PADDING;
    float y = viewTopCorner + TEXT_UP_PADDING;
    m_text.setPosition(x, y);
    
    window.draw(m_text);
}
