/// <summary>
/// author Kacie Franklin 24/02/2024
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>

const int m_HEIGHT = 600;
const int m_WIDTH = 1000;

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void setupSprite();
	void setUpRadio();
	void setUpDials();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	bool m_exitGame; // control exiting game

	sf::Sprite m_radioSprite; //sprite for radio
	sf::Texture m_radioTexture; //texture for radio
	sf::Sprite m_dialInstSprite; //sprite for instrument dial
	sf::Texture m_dialInstTexture; //texture for instrument dial
	sf::Sprite m_dialPitchSprite; //sprite for pitch dial
	sf::Texture m_dialPitchTexture; //texture for pitch dial
	sf::Sprite m_radioPlaySprite; //sprite for radio play button
	sf::Texture m_radioPlayTexture; //texture for radio play button
	sf::Sprite m_boardSprite; //sprite for board
	sf::Texture m_boardTexture; //texture for board
	sf::Sprite m_backgroundSprite; //sprite for background
	sf::Texture m_backgroundTexture; //texture for background
	sf::Sprite m_playSoundSprite; //sprite for play sound button
	sf::Texture m_playSoundTexture; //texture for play sound button
};

#endif // !GAME_HPP

