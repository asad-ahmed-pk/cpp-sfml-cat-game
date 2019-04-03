//
//  Button.cpp
//  The Meow Outing
//
//  Created by Asad Ahmed on 8/13/15.
//  Copyright (c) 2015 Asad Ahmed. All rights reserved.
//

#include "Button.h"
#include "ResourcePath.hpp"
#include <cstdlib>
#include <iostream>

namespace GUI
{
    const std::string fontname("cinnamon_cake.ttf");
    
    // Init with given side dimensions and load default font
    Button::Button(const sf::Vector2f& size) : sf::RectangleShape(size)
    {
        LoadFont();
    }
    
    // Init with width and height
    Button::Button(float width, float height) : sf::RectangleShape(sf::Vector2f(width, height))
    {
        LoadFont();
    }
    
    // Loads the font for use for the button
    void Button::LoadFont()
    {
        if (!m_font.loadFromFile(resourcePath() + fontname)){
            std::exit(-3);
        }
        
        m_text.setFont(m_font);
    }
    
    // Set the text for the button
    void Button::SetText(const std::string &text)
    {
        m_text.setString(text);
    }
    
    // Set the background color for the button
    void Button::SetBackgroundColor(const sf::Color &color)
    {
        setFillColor(color);
    }
    
    // Set the font color for the button
    void Button::SetFontColor(const sf::Color &color)
    {
        m_text.setColor(color);
    }
    
    // Render the button
    void Button::Draw(sf::RenderWindow* window)
    {
        window->draw(*this);
        
        // Draw the text in the center
        m_text.setPosition(getPosition().x + getLocalBounds().width / 2.0 - m_text.getLocalBounds().width / 2.0, getPosition().y + getLocalBounds().height / 2.0 - m_text.getLocalBounds().height);
        
        window->draw(m_text);  
    }
}
