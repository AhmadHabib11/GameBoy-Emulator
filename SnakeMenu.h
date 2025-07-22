#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class SnakeMenu {
private:
	sf::RenderWindow menuWindow;
	sf::Font font;
	sf::Text titleText;
	sf::Text startText;
	sf::Text exitText;
	sf::Text difficultyText;
	sf::Text easyText;
	sf::Text hardText;
	sf::Texture backgroundTexture; // Texture for the background
	sf::Sprite backgroundSprite;   // Sprite for the background
	int selectedOption;            // Tracks the currently selected menu option
	int difficultyOption;          // Tracks the currently selected difficulty (0 = Easy, 1 = Hard)

	

public:

	// Initialize menu graphics
	void initializeGraphics() {
		menuWindow.create(sf::VideoMode(800, 600), "Snake Menu");

		if (!font.loadFromFile("LilitaOne-Regular.ttf")) {
			cout << "Error loading font!" << endl;
		}

		if (!backgroundTexture.loadFromFile("snakebg.jpg")) {
			cout << "Error loading background image!" << endl;
		}

		// Set up the background sprite
		backgroundSprite.setTexture(backgroundTexture);
		backgroundSprite.setScale(
			static_cast<float>(menuWindow.getSize().x) / backgroundTexture.getSize().x,
			static_cast<float>(menuWindow.getSize().y) / backgroundTexture.getSize().y
		);

		// Title text setup
		titleText.setFont(font);
		titleText.setString("SNAKE GAME");
		titleText.setCharacterSize(72);
		titleText.setFillColor(sf::Color::White);
		titleText.setOutlineColor(sf::Color::Black);
		titleText.setOutlineThickness(3.f);
		titleText.setPosition(200.f, 20.f);

		// Start Game text setup
		startText.setFont(font);
		startText.setString("Start Game");
		startText.setCharacterSize(48);
		startText.setFillColor(sf::Color::Green); // Default selection
		startText.setOutlineColor(sf::Color::Black);
		startText.setOutlineThickness(2.f);
		startText.setPosition(100.f, 200.f);

		// Exit text setup
		exitText.setFont(font);
		exitText.setString("Exit");
		exitText.setCharacterSize(48);
		exitText.setFillColor(sf::Color::White); // Non-selected color
		exitText.setOutlineColor(sf::Color::Black);
		exitText.setOutlineThickness(2.f);
		exitText.setPosition(100.f, 300.f);

		// Difficulty label text setup
		difficultyText.setFont(font);
		difficultyText.setString("Choose Difficulty:");
		difficultyText.setCharacterSize(45);
		difficultyText.setFillColor(sf::Color::White);
		difficultyText.setOutlineColor(sf::Color::Black);
		difficultyText.setOutlineThickness(2.f);
		difficultyText.setPosition(100.f, 410.f);

		// Easy difficulty text setup
		easyText.setFont(font);
		easyText.setString("Easy");
		easyText.setCharacterSize(45);
		easyText.setFillColor(sf::Color::Green); // Default difficulty
		easyText.setOutlineColor(sf::Color::Black);
		easyText.setOutlineThickness(2.f);
		easyText.setPosition(100.f, 480.f);

		// Hard difficulty text setup
		hardText.setFont(font);
		hardText.setString("Hard");
		hardText.setCharacterSize(45);
		hardText.setFillColor(sf::Color::White);
		hardText.setOutlineColor(sf::Color::Black);
		hardText.setOutlineThickness(2.f);
		hardText.setPosition(240.f, 480.f);

		selectedOption = 0; // Default to the first option ("Start Game")
		difficultyOption = 0; // Default difficulty level to "Easy"
	}

	// Updates the color of menu options based on the selected option
	void updateMenuColors() {
		// Update start and exit options
		if (selectedOption == 0) {
			startText.setFillColor(sf::Color::Green);
			exitText.setFillColor(sf::Color::White);
		}
		else if (selectedOption == 1) {
			startText.setFillColor(sf::Color::White);
			exitText.setFillColor(sf::Color::Red);
		}

		// Update difficulty options
		if (difficultyOption == 0) {
			easyText.setFillColor(sf::Color::Green);
			hardText.setFillColor(sf::Color::White);
		}
		else if (difficultyOption == 1) {
			easyText.setFillColor(sf::Color::White);
			hardText.setFillColor(sf::Color::Red);
		}
	}
	// Return the difficulty level (0 = Easy, 1 = Hard)
	int getDifficultyLevel() const {
		return difficultyOption;
	}

	// Display the menu and handle input
	bool displayMenu() {
		initializeGraphics();

		while (menuWindow.isOpen()) {
			sf::Event event;
			while (menuWindow.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					menuWindow.close();
					return false; // Exit the program
				}

				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Up) {
						selectedOption = (selectedOption - 1 + 2) % 2; // Cycle upwards through Start/Exit
						updateMenuColors();
					}
					if (event.key.code == sf::Keyboard::Down) {
						selectedOption = (selectedOption + 1) % 2; // Cycle downwards through Start/Exit
						updateMenuColors();
					}
					if (event.key.code == sf::Keyboard::Left) {
						difficultyOption = (difficultyOption - 1 + 2) % 2; // Cycle difficulty to the left
						updateMenuColors();
					}
					if (event.key.code == sf::Keyboard::Right) {
						difficultyOption = (difficultyOption + 1) % 2; // Cycle difficulty to the right
						updateMenuColors();
					}
					if (event.key.code == sf::Keyboard::Enter) {
						menuWindow.close();
						if (selectedOption == 0) {
							return true; // Start the game
						}
						else if (selectedOption == 1) {
							return false; // Exit the program
						}
					}
				}
			}

			menuWindow.clear();
			menuWindow.draw(backgroundSprite); // Draw the background first
			menuWindow.draw(titleText);        // Draw the title text
			menuWindow.draw(startText);
			menuWindow.draw(exitText);
			menuWindow.draw(difficultyText);  // Draw the difficulty label
			menuWindow.draw(easyText);        // Draw the Easy option
			menuWindow.draw(hardText);        // Draw the Hard option
			menuWindow.display();
		}
		return false; // Default to exiting if menu closes
	}
};


