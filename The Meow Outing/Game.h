// Main Game class - provides the main framework for running the game, updating entities and rendering sprites to the window
// This class manages the timestep to ensure consistent updating.
// It also includes the game world, player and other entities, including a HUD

#ifndef GAME_H
#define GAME_H

#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "World.h"
#include "Hud.h"
#include "Player.h"
#include "GameState.h"

class Game : public GameState
{
private:
    
    // Game world and view
    std::unique_ptr<World> m_world;
    TextureLoader m_textureLoader;
    sf::View m_view;
    
    // Player and enemies
    Player* m_player;
    int m_playerScore;
    //Player* m_enemy01;
    sf::Texture m_playerSpriteSheet;
    
    // Sounds
    sf::Sound m_playerSound;
    sf::SoundBuffer m_soundBuffer;
    
    // Hud
    Hud m_hud;

public:
    Game(std::function<void(GAMESTATES state)> pushStateCallback, std::function<void()> popStateCallback, sf::RenderWindow* window);
    
    // Implementation of abstract methods from GameState
    void Start();
    void End();
    
    // Main Game Loop
	void Run();
	void Update();
	void Render();
    
    // Called when another object notifies the game that a player scoring event occured, score is added to the player's score
    void PlayerScored(int scored);

private:
	void ProcessEvents(const sf::Time& time);
};

#endif