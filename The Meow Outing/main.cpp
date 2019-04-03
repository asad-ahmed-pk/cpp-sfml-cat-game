// The Meow Outing
// Main file

#include <cstdlib>
#include <SFML/Graphics.hpp>

#include "Game.h"
#include "MenuState.h"
#include "GameStateManager.h"

int main()
{
    // Create the window and push main menu state into the state machine
    //sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "The Meow Outing", sf::Style::Fullscreen)  //-- For Fullscreen
    sf::RenderWindow window(sf::VideoMode::VideoMode(1000, 800), "The Meow Outing");
    
    GameStateManager stateMachine(&window);
    stateMachine.PushGameState(GAMESTATES::MENU);
    
	return 0;
}