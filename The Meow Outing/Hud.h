//
//  Hud.h
//  The Meow Outing
//
//  Created by Asad Ahmed on 8/4/15.
//  Copyright (c) 2015 Asad Ahmed. All rights reserved.
//
//  Class responsible for drawing out the game Hud.

#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>

class Hud
{
public:
    Hud();
    
    // Set the score to draw in the hud
    void SetScore(int score);
    
    // Draw out the hud using the given render target
    void Draw(sf::RenderTarget& window);
    
private:
    int m_score;
    sf::Font m_font;
    sf::Text m_text;
};

#endif
