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
	setupSprite(); // load background and board texture
	setUpRadio(); //load radio texture
	setUpDials(); //load dials texture
	setUpPlayRadio(); //load play radio button texture
	setUpPlayButton(); //load play sound button texture
	setUpSlider(); //load slider texture
	loadInstrumentBuffers(); //load buffers and default to guitar
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
		if (sf::Event::MouseMoved == newEvent.type)
		{
			processMouseMove(newEvent);
		}
		if (sf::Event::MouseButtonPressed == newEvent.type)
		{
			processMouseDown(newEvent);
		}
		if (sf::Event::MouseButtonReleased == newEvent.type)
		{
			processMouseUp(newEvent);
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
	if (sf::Keyboard::G == t_event.key.code)
	{
		setGuitar();
	}
	if (sf::Keyboard::F == t_event.key.code)
	{
		setFlute();
	}
	if (sf::Keyboard::P == t_event.key.code)
	{
		setPiano();
	}
	if (sf::Keyboard::D == t_event.key.code)
	{
		setUpDrum();
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
	checkPitch();
	releaseButtons();
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
	m_window.draw(m_boardSprite);
	m_window.draw(m_radioPlaySprite);
	m_window.draw(m_playSoundSprite);
	m_window.draw(m_sliderSprite);
	
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
}

/// <summary>
/// load the texture and setup the sprite for the background
/// </summary>
void Game::setupSprite()
{
	if (!m_backgroundTexture.loadFromFile("ASSETS\\IMAGES\\background.png")) //load texture
	{
		std::cout << "problem loading background.png" << std::endl;
	}
	m_backgroundSprite.setTexture(m_backgroundTexture);
	m_backgroundSprite.setTextureRect(sf::IntRect{ 0, 0, m_WIDTH, m_HEIGHT});
	m_backgroundSprite.setScale(4.0f, 4.0f);

	if (!m_boardTexture.loadFromFile("ASSETS\\IMAGES\\board.png")) //load texture
	{
		std::cout << "problem loading board.png" << std::endl;
	}
	m_boardSprite.setTexture(m_boardTexture);
	m_boardSprite.setScale(4.0f, 4.0f);
	m_boardSprite.setPosition(50.0f, 300.0f);
}

/// <summary>
/// sets up the radio sprite and texture
/// </summary>
void Game::setUpRadio()
{
	if (!m_radioTexture.loadFromFile("ASSETS\\IMAGES\\radio.png")) //load texture
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
	if (!m_dialInstTexture.loadFromFile("ASSETS\\IMAGES\\dial.png")) //load texture
	{
		std::cout << "problem loading dial.png" << std::endl;
	}
	m_dialInstSprite.setTexture(m_dialInstTexture);
	m_dialInstSprite.setScale(4.0f, 4.0f);
	m_dialInstSprite.setOrigin(7, 6.5);
	m_dialInstSprite.setPosition(755.0f, 365.0f);

	if (!m_dialPitchTexture.loadFromFile("ASSETS\\IMAGES\\dial.png")) //load texture
	{
		std::cout << "problem loading dial.png" << std::endl;
	}
	m_dialPitchSprite.setTexture(m_dialPitchTexture);
	m_dialPitchSprite.setScale(4.0f, 4.0f);
	m_dialPitchSprite.setOrigin(7, 6.5);
	m_dialPitchSprite.setPosition(505.0f, 365.0f);
}

/// <summary>
/// set up play radio button sprite, texture and position
/// </summary>
void Game::setUpPlayRadio()
{
	if (!m_radioPlayTexture.loadFromFile("ASSETS\\IMAGES\\playRadio.png")) //load texture
	{
		std::cout << "problem loading playRadio.png" << std::endl;
	}
	m_radioPlaySprite.setTexture(m_radioPlayTexture);
	m_radioPlaySprite.setScale(4.0f, 4.0f);
	m_radioPlaySprite.setPosition(568.0f, 290.0f);
}

/// <summary>
/// set up play sound button sprite, texture and position
/// </summary>
void Game::setUpPlayButton()
{
	if (!m_playSoundTexture.loadFromFile("ASSETS\\IMAGES\\playSound.png")) //load texture
	{
		std::cout << "problem loading playSound.png" << std::endl;
	}
	m_playSoundSprite.setTexture(m_playSoundTexture);
	m_playSoundSprite.setScale(4.0f, 4.0f);
	m_playSoundSprite.setPosition(135.0f, 400.0f);
}

/// <summary>
/// set up slider sprite, texture and position
/// </summary>
void Game::setUpSlider()
{
	if (!m_sliderTexture.loadFromFile("ASSETS\\IMAGES\\slider.png")) // load texture
	{
		std::cout << "problem loading slider.png" << std::endl;
	}
	m_sliderSprite.setTexture(m_sliderTexture);
	m_sliderSprite.setScale(3.0f, 3.0f);
	m_sliderSprite.setRotation(90.0f);
	m_sliderSprite.setPosition(568.0f, 405.0f);

}

/// <summary>
/// processes w
/// hen the mouse is held down
/// </summary>
/// <param name="t_event"></param>
void Game::processMouseDown(sf::Event t_event)
{ 
	m_mouseHeld = true;
	m_mouseEnd.x = static_cast<float>(t_event.mouseButton.x);
	m_mouseEnd.y = static_cast<float>(t_event.mouseButton.y);
	sf::FloatRect sliderBounds = { 535.f, m_sliderSprite.getPosition().y, 177.f, m_sliderSprite.getGlobalBounds().height };//sets the bounds of the slider bar to check if the mouse is in correct range
	if (sliderBounds.contains(m_mouseEnd)) //checks if the mouse is in the same position as sliderBounds
	{
		clicked = ObjectPressed::Slider;
	}
	if (m_dialInstSprite.getGlobalBounds().contains(m_mouseEnd))//checks if the mouse is in the same position as the dial
	{
		clicked = ObjectPressed::DialRight;
	}
	if (m_dialPitchSprite.getGlobalBounds().contains(m_mouseEnd))//checks if the mouse is in the same position as the dial
	{
		clicked = ObjectPressed::DialLeft;
	}
	
	if (m_radioPlaySprite.getGlobalBounds().contains(m_mouseEnd) && m_playButtonCooldown > 30)//checks if the mouse is in the same position as the radio play button
	{	
		clicked = ObjectPressed::PlayRadio;
		m_radioPlaySprite.setColor(sf::Color::Black);
		m_playButtonCooldown = 0;//goes back to zero
		
		
	}
	if (m_playSoundSprite.getGlobalBounds().contains(m_mouseEnd) && m_playButtonCooldown > 30)//checks if the mouse is in the same position as the play sound button
	{
		m_playSoundSprite.setColor(sf::Color::Black);
		m_playButtonCooldown = 0;//goes back to zero
	}
}

/// <summary>
/// processes when the mouse is released
/// </summary>
/// <param name="t_event"></param>
void Game::processMouseUp(sf::Event t_event)
{
	m_mouseHeld = false;
	if (clicked == ObjectPressed::PlayRadio) 
	{
		m_sound.play();
	}
	if (clicked == ObjectPressed::DialRight) 
	{
		checkInstrument();
	}
	clicked = ObjectPressed::None;
}


/// <summary>
/// processes the mouse moving on the screen, 
/// when held down on the slider it can be moved,
/// when held down it can rotate the dials.
/// </summary>
/// <param name="t_event"></param>
void Game::processMouseMove(sf::Event t_event)
{
	m_mouseEnd.x = static_cast<float>(t_event.mouseMove.x);
	m_mouseEnd.y = static_cast<float>(t_event.mouseMove.y);

	if (m_mouseHeld == true)
	{
		if (clicked == ObjectPressed::Slider)
		{
			sf::Vector2f location = { m_mouseEnd.x, m_sliderSprite.getPosition().y };
			if (location.x < 550) //stops the slider from going under 550
			{
				location.x = 550;
			}
			if (location.x > 710) //stops the slider from going over 710
			{
				location.x = 710;
			}
			m_sliderSprite.setPosition(location);
		}
		sf::Vector2f displacement;
		float angleR;
		float angleD;
		if (clicked == ObjectPressed::DialRight)
		{

			displacement = m_dialInstSprite.getPosition() - m_mouseEnd;
			angleR = std::atan2(displacement.y, displacement.x);
			angleD = angleR * 180.0f / 3.14f;
			angleD = (static_cast<int>(angleD + 179) / 90 + 1) * 90; //makes the dial rotate 90 degrees
			m_dialInstSprite.setRotation(angleD);
		}
		if (clicked == ObjectPressed::DialLeft)
		{
			displacement = m_dialPitchSprite.getPosition() - m_mouseEnd;
			angleR = std::atan2(displacement.y, displacement.x);
			angleD = angleR * 180.0f / 3.14f;
			angleD = (static_cast<int>(angleD + 179) / 90 + 1) * 90; //makes the dial rotate 90 degrees
			m_dialPitchSprite.setRotation(angleD);
		}
	}
}

/// <summary>
/// Checks what the instrument is based on the right dial's rotation.
/// </summary>
void Game::checkInstrument()
{
	if (m_dialInstSprite.getRotation() == 0)
	{
		setGuitar();
	}
	if (m_dialInstSprite.getRotation() == 90)
	{
		setFlute();
	}
	if (m_dialInstSprite.getRotation() == 180)
	{
		setPiano();
	}
	if (m_dialInstSprite.getRotation() == 270)
	{
		setUpDrum();
	}
}

/// <summary>
/// Loads the buffers for the instruments
/// </summary>
void Game::loadInstrumentBuffers()
{
	if (!m_bufferG.loadFromFile("ASSETS\\SOUNDS\\GuitarC.wav"))
	{
		std::cout << "problem loading guitarC.wav";
	}
	if (!m_bufferD.loadFromFile("ASSETS\\SOUNDS\\DrumHiHat.wav"))
	{
		std::cout << "problem loading drumHiHat.wav";
	}
	if (!m_bufferF.loadFromFile("ASSETS\\SOUNDS\\FluteC.wav"))
	{
		std::cout << "problem loading fluteC.wav";
	}
	if (!m_bufferP.loadFromFile("ASSETS\\SOUNDS\\PianoC.wav"))
	{
		std::cout << "problem loading pianoC.wav";
	}
	m_sound.setBuffer(m_bufferG);
}

/// <summary>
/// sets up the guitar and its different notes
/// </summary>
void Game::setGuitar()
{
	m_sound.setBuffer(m_bufferG);
	//m_sound.play();
}

/// <summary>
/// sets up the flute and its different notes
/// </summary>
void Game::setFlute()
{
	m_sound.setBuffer(m_bufferF);
	//m_sound.play();
}

/// <summary>
/// sets up the piano and its different notes
/// </summary>
void Game::setPiano()
{
	
	m_sound.setBuffer(m_bufferP);
	//m_sound.play();
}

/// <summary>
/// sets up the drum and its different notes
/// </summary>
void Game::setUpDrum()
{
	m_sound.setBuffer(m_bufferD);
	//m_sound.play();
}

/// <summary>
/// checks the rotation of the pitch dial and alters the pitch of the sound
/// </summary>
void Game::checkPitch()
{
	if (m_dialPitchSprite.getRotation() == 90)
	{
		m_sound.setPitch(2.0f);
	}
	if (m_dialPitchSprite.getRotation() == 270)
	{
		m_sound.setPitch(0.75f);
	}
}

/// <summary>
/// keeps the buttons blacked out until they can be pressed again
/// </summary>
void Game::releaseButtons()
{
	if (m_playButtonCooldown <= 30) 
	{
		m_playButtonCooldown++;
	}
	else 
	{
		m_radioPlaySprite.setColor(sf::Color::White);//reverts to its original color
		m_playSoundSprite.setColor(sf::Color::White);//reverts to its original color	
	}
}
