// Game.cpp
// Main game framework

#include <iostream>
#include <functional>
#include <cstdlib>
#include "Game.h"
#include "TextureLoader.h"
#include "resourcePath.hpp"

const sf::Time TIME_PER_FRAME = sf::seconds(1.0 / 60.0);
const float PLAYER_SPEED = 2.0f;

const std::string PLAYER_FISH_EAT_SOUND("meow_happy.wav");

// Construct a game object with the given window
Game::Game(std::function<void(GAMESTATES state)> pushStateCallback, std::function<void()> popStateCallback, sf::RenderWindow* window) : GameState(pushStateCallback, popStateCallback, window)
{
	// Load player texture using TextureLoader class
	m_textureLoader.LoadTexture(resourcePath() + "cat_sprites.png", Textures::PLAYER);
	m_playerSpriteSheet = *m_textureLoader.GetTextureRef(Textures::PLAYER);
    
    // Load fish item texture
    m_textureLoader.LoadTexture(resourcePath() + "fish.png", Textures::FISH);
	
	// player movement direction map
	std::map<Movement::Direction, int> movementMap;
	movementMap[Movement::DOWN] = 0;
	movementMap[Movement::LEFT] = 1;
	movementMap[Movement::RIGHT] = 2;
	movementMap[Movement::UP] = 3;

	// Set up animation properties
	m_player = new Player(PLAYER_SPEED, &m_playerSpriteSheet);
	m_player->SetAnimationAttributes(800, 100);			// 500, 100
	m_player->SetSpriteSheetAttributes(4, 3, 0, 32, movementMap);
	m_player->setTextureRect(sf::IntRect(0, 0, 32, 32));
	m_player->setPosition(30, 0);

	//// make another copy of a player to be the enemy
	//m_enemy01 = new Player(0.0, &m_playerSpriteSheet);
	//m_enemy01->SetAnimationAttributes(800, 100);			// 500, 100
	//m_enemy01->SetSpriteSheetAttributes(4, 3, 0, 32, movementMap);
	//m_enemy01->setTextureRect(sf::IntRect(0, 0, 32, 32));
	//m_enemy01->setPosition(140, 200);

	// Load game map
	m_textureLoader.LoadTexture(resourcePath() + "map_01.png", Textures::WORLD_TILEMAP);
	m_world = std::unique_ptr<World>(new World(resourcePath() + "map_02.csv", resourcePath() + "map_02_col.csv", &m_textureLoader, 8, 8));

	// Add player and enemy to the world to observe for collisions
	m_world->AddEntity(m_player);
	//m_world->AddEntity(m_enemy01);
	m_world->AddPlayer(m_player);

	// Setup the view
	m_view.reset(sf::FloatRect(0.0, 0.0, m_window->getSize().x, m_window->getSize().y));
	m_window->setView(m_view);
    
    // Setup player score and scoring callback from world
    m_playerScore = 0;
    m_world->NotifyForScoringEvent(std::bind(&Game::PlayerScored, this, std::placeholders::_1));
    
    // Setup player sounds
    if(!m_soundBuffer.loadFromFile(resourcePath() + PLAYER_FISH_EAT_SOUND)){
        std::exit(-4);
    }
}

// Called when the state is started
void Game::Start()
{
    Run();
}

// Called when the state is about to end
void Game::End()
{
    
}

// Main game loop
void Game::Run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (m_window->isOpen() && !m_shouldPopState && !m_requestedPush)
	{
		timeSinceLastUpdate += clock.restart();

		// TODO: Should pause instead, not implemented yet due to time contraints
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            m_shouldPopState = true;
            //m_pushStateCallback(GAMESTATES::PAUSE);
		}

		// Process until frame is less than time per frame, then render to maintain consistent time step
		while (timeSinceLastUpdate > TIME_PER_FRAME)
		{
			timeSinceLastUpdate -= TIME_PER_FRAME;
			ProcessEvents(timeSinceLastUpdate);
			Update();
		}
		Render();
	}
    
    // Check if state needs to be popped
    if (m_shouldPopState){
        m_shouldPopState = false;
        m_popStateCallback();
    }
}

// Process the main application level events
void Game::ProcessEvents(const sf::Time& time)
{
    sf::Event event;
    while (m_window->pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                m_window->close();
                break;
        }
    }

	// Check for keyboard input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		m_player->Move(Movement::UP);
		m_player->Animate(time, Movement::UP);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		m_player->Move(Movement::DOWN);
		m_player->Animate(time, Movement::DOWN);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		m_player->Move(Movement::LEFT);
		m_player->Animate(time, Movement::LEFT);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		m_player->Move(Movement::RIGHT);
		m_player->Animate(time, Movement::RIGHT);
	}

	// update the view to center on the player's position
	sf::Vector2f playerCenter(m_player->getPosition().x + m_player->GetBoudingRect().width / 2.0f, m_player->getPosition().y + m_player->GetBoudingRect().height / 2.0f);
	sf::Vector2f newCenter(m_view.getCenter());

	// adjust the view so that it does not display out of bounds
	sf::Vector2f viewOrigin = sf::Vector2f(playerCenter.x - (m_view.getSize().x / 2.0f), playerCenter.y - (m_view.getSize().y / 2.0f));
	if (viewOrigin.x > 0 && (viewOrigin.x + m_view.getSize().x) < m_world->GetSize().x){
		newCenter.x = playerCenter.x;
	}
	if (viewOrigin.y > 0 && (viewOrigin.y + m_view.getSize().y) < m_world->GetSize().y){
		newCenter.y = playerCenter.y;
	}

	m_view.setCenter(newCenter);
	m_window->setView(m_view);
}

// Update the entities and state of the game
void Game::Update()
{
	// Ask world to observe for a collision this frame
	m_world->ObserveCollisions();
}

// Render the output to screen
void Game::Render()
{
	m_window->clear();

	m_world->Draw(*m_window);
	m_window->draw(*m_player);
    m_hud.Draw(*m_window);
	//m_window.draw(*m_enemy01);

	m_window->display();
}

// Callback when player scoring event occurs with the given score to be added
void Game::PlayerScored(int scored)
{
    m_playerScore += scored;
    
    // Call on HUD to update score
    m_hud.SetScore(m_playerScore);
    
    // Play happy meow sound since player ate a fish
    m_playerSound.setBuffer(m_soundBuffer);
    m_playerSound.play();
}
