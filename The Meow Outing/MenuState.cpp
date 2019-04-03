//
//  MenuState.cpp
//  The Meow Outing
//
//  Created by Asad Ahmed on 8/5/15.
//  Copyright (c) 2015 Asad Ahmed. All rights reserved.
//

#include "MenuState.h"
#include "ResourcePath.hpp"
#include "Button.h"

const std::string fontname("cinnamon_cake.ttf");
const sf::Color backgroundColor(63, 64, 63);
const sf::Color buttonColor(242, 236, 228);
const sf::Color textColor(191, 165, 163);

const int BUTTON_SPACING = 30;
const int BUTTON_TOP_MARGIN = 320;
const int TITLE_TOP_MARGIN = 30;
const int CREDITS_BOTTOM_MARGIN = 30;

// Constructor
MenuState::MenuState(std::function<void(GAMESTATES state)> pushStateCallback, std::function<void()> popStateCallback, sf::RenderWindow* window) : GameState(pushStateCallback, popStateCallback, window), m_playButton(200, 80), m_quitButton(200, 80)
{
    
}

// Destructor
MenuState::~MenuState() {}

// Sets up the UI
void MenuState::SetupUI()
{
    // Setup play button
    m_playButton.SetBackgroundColor(buttonColor);
    m_playButton.SetText("Play");
    m_playButton.SetFontColor(textColor);
    m_playButton.setPosition((m_window->getSize().x - m_playButton.getSize().x )/ 2.0, BUTTON_TOP_MARGIN);
    
    // Setup quit button below play button
    m_quitButton.SetBackgroundColor(buttonColor);
    m_quitButton.SetText("Quit");
    m_quitButton.SetFontColor(textColor);
    m_quitButton.setPosition(m_playButton.getPosition().x, m_playButton.getPosition().y + m_quitButton.getSize().y + BUTTON_SPACING);
    
    // Load font if not already loaded
    if (m_font.getInfo().family.size() == 0 && !m_font.loadFromFile(resourcePath() + fontname)){
        exit(-3);
    }
    
    // Setup title label
    m_titleText.setFont(m_font);
    m_titleText.setString("The Meow Outing");
    m_titleText.setCharacterSize(64);
    m_titleText.setPosition((m_window->getSize().x - m_titleText.getLocalBounds().width) / 2.0, TITLE_TOP_MARGIN);
    
    // Setup credits label
    m_creditsText.setFont(m_font);
    m_creditsText.setString("Developed by Asad Ahmed with SFML and C++11");
    m_creditsText.setCharacterSize(40);
    m_creditsText.setPosition((m_window->getSize().x - m_creditsText.getLocalBounds().width) / 2.0, m_window->getSize().y - m_creditsText.getLocalBounds().height - CREDITS_BOTTOM_MARGIN);
    
    // Reset the view to default view
    m_window->setView(m_window->getDefaultView());
}

// Start the menu state by drawing the main menu
void MenuState::Start()
{
    SetupUI();
    
    // Process button click and window close events
    while (m_window->isOpen() && !m_requestedPush && !m_shouldPopState)
    {
        sf::Event event;
        while (m_window->pollEvent(event))
        {
            // close the window if close requested
            if (event.type == sf::Event::Closed){
                m_window->close();
            }
            // Check if left mouse button pressed and released on UI
            else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left){
                
                // Play button clicked - Push game state
                if (IsPointInsideButton(m_playButton, sf::Vector2f(event.mouseButton.x, event.mouseButton.y))){
                    m_requestedPush = true;
                }
                // Quit button clicked - close window
                else if (IsPointInsideButton(m_quitButton, sf::Vector2f(event.mouseButton.x, event.mouseButton.y))){
                    m_shouldPopState = true;
                }
            }
        }
        
        Render();
    }
    
    // Check if state needed a push or pop since out of loop
    if (m_requestedPush){
        m_requestedPush = false;
        m_pushStateCallback(GAMESTATES::GAMEPLAY);
    }
    else{
        m_shouldPopState = false;
        m_popStateCallback();
    }
}

// Called when requesting a render
void MenuState::Render()
{
    m_window->clear(backgroundColor);
    
    // Draw the buttons
    m_playButton.Draw(m_window);
    m_quitButton.Draw(m_window);
    
    // Draw the title label and the credits label
    m_window->draw(m_titleText);
    m_window->draw(m_creditsText);
    
    m_window->display();
}

// Checks if the given screen coordinate is within the given button
bool MenuState::IsPointInsideButton(const GUI::Button& btn, const sf::Vector2f& point) const
{
    sf::FloatRect bounds = btn.getGlobalBounds();
    bool xInside = point.x >= bounds.left && point.x <= bounds.left + bounds.width;
    bool yInside = point.y >= bounds.top && point.y <= bounds.top + bounds.height;
    return (xInside && yInside);
}
