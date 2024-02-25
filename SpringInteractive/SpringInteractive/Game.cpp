/// <summary>
/// @author Kacie Franklin
/// @date 24/02/2024
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ m_WIDTH, m_HEIGHT, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load background texture
	setUpRadio(); //load radio texture
	setUpDials(); //load dials texture
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_backgroundSprite);
	m_window.draw(m_radioSprite);
	m_window.draw(m_dialInstSprite);
	m_window.draw(m_dialPitchSprite);
	m_window.draw(m_welcomeMessage);
	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_welcomeMessage.setFont(m_ArialBlackfont);
	m_welcomeMessage.setString("SFML Game");
	m_welcomeMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_welcomeMessage.setPosition(40.0f, 40.0f);
	m_welcomeMessage.setCharacterSize(80U);
	m_welcomeMessage.setOutlineColor(sf::Color::Red);
	m_welcomeMessage.setFillColor(sf::Color::Black);
	m_welcomeMessage.setOutlineThickness(3.0f);

}

/// <summary>
/// load the texture and setup the sprite for the background
/// </summary>
void Game::setupSprite()
{
	if (!m_backgroundTexture.loadFromFile("ASSETS\\IMAGES\\background.png"))
	{
		std::cout << "problem loading background.png" << std::endl;
	}
	m_backgroundSprite.setTexture(m_backgroundTexture);
	m_backgroundSprite.setTextureRect(sf::IntRect{ 0, 0, m_WIDTH, m_HEIGHT});
	m_backgroundSprite.setScale(4.0f, 4.0f);
}

/// <summary>
/// sets up the radio sprite and texture
/// </summary>
void Game::setUpRadio()
{
	if (!m_radioTexture.loadFromFile("ASSETS\\IMAGES\\radio.png"))
	{
		std::cout << "problem loading radio.png" << std::endl;
	}
	m_radioSprite.setTexture(m_radioTexture);
	m_radioSprite.setPosition(400.0f, 125.0f);
	m_radioSprite.setScale(4.0f, 4.0f);
}

/// <summary>
/// sets up the textures and sprites for the dials
/// </summary>
void Game::setUpDials()
{
	if (!m_dialInstTexture.loadFromFile("ASSETS\\IMAGES\\dial.png"))
	{
		std::cout << "problem loading dial.png" << std::endl;
	}
	m_dialInstSprite.setTexture(m_dialInstTexture);
	m_dialInstSprite.setScale(4.0f, 4.0f);
	m_dialInstSprite.setPosition(725.0f, 340.0f);

	if (!m_dialPitchTexture.loadFromFile("ASSETS\\IMAGES\\dial.png"))
	{
		std::cout << "problem loading dial.png" << std::endl;
	}
	m_dialPitchSprite.setTexture(m_dialPitchTexture);
	m_dialPitchSprite.setScale(4.0f, 4.0f);
	m_dialPitchSprite.setPosition(475.0f, 340.0f);
}
