//
//  Button.h
//  The Meow Outing
//
//  Created by Asad Ahmed on 8/13/15.
//  Copyright (c) 2015 Asad Ahmed. All rights reserved.
//
//  GUI button class to represent and render a button for game menu elements
//

#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

namespace GUI
{
    class Button : public sf::RectangleShape
    {
    public:
        
        // Construct the button with the given size
        Button(const sf::Vector2f& size);
        
        // Construct the button with the given width and height
        Button(float width, float height);
        
        // Set the text for the button
        void SetText(const std::string& text);
        
        // Get the text that is set on the button
        const std::string& GetText() const;
        
        // Set the background color for the button
        void SetBackgroundColor(const sf::Color& color);
        
        // Set the font color for the button
        void SetFontColor(const sf::Color& color);
        
        // Set the callback for the click event
        void SetClickEventListener(std::function<void()> listener);
        
        // Call to render the button to the given window
        void Draw(sf::RenderWindow* window);
        
    private:
        sf::Text m_text;
        sf::Font m_font;
        
    private:
        void LoadFont();
    };
}

#endif
