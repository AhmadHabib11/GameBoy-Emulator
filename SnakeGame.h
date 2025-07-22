#pragma once
#include <SFML/Graphics.hpp>
#include "Point.h"
#include "Grid.h"
#include "SnakeSegment.h"
#include "Game.h"
#include "SnakeMenu.h"
#include <ctime>
#include "SoundSystem.h"

using namespace std;

class SnakeGame : public Game {
private:
	SnakeSegment snakeBody[100]; 
	int snakeLength;             
	Point direction;            
	Point food;
	Grid grid;
	SnakeMenu snakeMenu;

	sf::Font font;
	sf::RenderWindow window;
	sf::Texture appleTexture;
	sf::Sprite appleSprite;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	SoundSystem soundSystem;

	float moveDelay;             
	bool isPaused;               
	bool isGameOver;             

	
	sf::Text scoreText;         
	sf::Text gameOverText;      

	
	
public:
	// Load all necessary sprites for the game (apple, background, score, and game over text)
	void loadSprites() {
		// Load apple texture and set it to the apple sprite
		appleTexture.loadFromFile("apple.png");
		appleSprite.setTexture(appleTexture);

		// Load background texture and set it to the background sprite
		backgroundTexture.loadFromFile("snakegame.png");
		backgroundSprite.setTexture(backgroundTexture);

		// Initialize and configure the score text
		scoreText.setFont(font);
		scoreText.setCharacterSize(24);
		scoreText.setFillColor(sf::Color::White);

		// Initialize and configure the game over text
		gameOverText.setFont(font);
		gameOverText.setCharacterSize(48);
		gameOverText.setFillColor(sf::Color::Red);
		gameOverText.setOutlineColor(sf::Color::Black);
		gameOverText.setOutlineThickness(2.f);
		gameOverText.setString("    GAME OVER\nPress ESC to Exit");
		gameOverText.setPosition(250.f, 220.f);  // Position the game over message

		// Adjust the background sprite to scale it to the window size
		sf::Vector2u windowSize = window.getSize();
		backgroundSprite.setScale(
			(float)windowSize.x / backgroundTexture.getSize().x,
			(float)windowSize.y / backgroundTexture.getSize().y
		);
	}

	// Update the sprites of the snake's body based on its movement direction
	void updateBodySprites() {
		for (int i = 1; i < snakeLength - 1; ++i) {
			// Get the positions of the previous and next body segments
			Point prevPos = snakeBody[i - 1].getPosition();
			Point nextPos = snakeBody[i + 1].getPosition();
			Point currentPos = snakeBody[i].getPosition();

			// Set the appropriate texture based on the direction of the snake's body parts
			if (prevPos.x == nextPos.x) {
				snakeBody[i].loadTexture("BODY_VERTICAL");  // Vertical body part
			}
			else if (prevPos.y == nextPos.y) {
				snakeBody[i].loadTexture("BODY_HORIZONTAL");  // Horizontal body part
			}
			// Set diagonal body parts based on relative positions
			else if ((prevPos.x < currentPos.x && nextPos.y > currentPos.y) ||
				(prevPos.y > currentPos.y && nextPos.x > currentPos.x)) {
				snakeBody[i].loadTexture("BODY_TOPLEFT");
			}
			else if ((prevPos.x > currentPos.x && nextPos.y > currentPos.y) ||
				(prevPos.y > currentPos.y && nextPos.x < currentPos.x)) {
				snakeBody[i].loadTexture("BODY_TOPRIGHT");
			}
			else if ((prevPos.x < currentPos.x && nextPos.y < currentPos.y) ||
				(prevPos.y < currentPos.y && nextPos.x > currentPos.x)) {
				snakeBody[i].loadTexture("BODY_BOTTOMLEFT");
			}
			else if ((prevPos.x > currentPos.x && nextPos.y < currentPos.y) ||
				(prevPos.y < currentPos.y && nextPos.x < currentPos.x)) {
				snakeBody[i].loadTexture("BODY_BOTTOMRIGHT");
			}
		}

		// Update the tail sprite based on the second-to-last segment's position
		if (snakeLength >= 2) {
			Point prevTailPos = snakeBody[snakeLength - 2].getPosition();
			snakeBody[snakeLength - 1].updateTailSprite(prevTailPos);
		}
	}

	// Spawn new food at a random position on the grid
	void spawnFood() {
		int x = rand() % grid.getWidth();
		int y = rand() % grid.getHeight();

		food = Point(x, y);  // Set the food position
		appleSprite.setPosition(x * grid.getCellSize(), y * grid.getCellSize());  // Set the apple sprite position
	}

	// Initialize the snake with a length of 3 at a starting position
	void initializeSnake() {
		snakeLength = 3;  // Start with 3 segments
		snakeBody[0] = SnakeSegment(Point(10, 10), "HEAD_RIGHT");  // Set the snake's head
		snakeBody[1] = SnakeSegment(Point(9, 10), "BODY_HORIZONTAL");  // Set the first body segment
		snakeBody[2] = SnakeSegment(Point(8, 10), "TAIL_RIGHT");  // Set the snake's tail
		direction = Point(1, 0);  // Initial movement direction is right
	}

	// Grow the snake by adding a new segment
	void growSnake() {
		if (snakeLength < 100) {
			// Get the position of the last segment and add a new one
			Point newSegmentPos = snakeBody[snakeLength - 1].getPosition();
			snakeBody[snakeLength] = SnakeSegment(newSegmentPos, "BODY_HORIZONTAL");
			snakeLength++;  // Increase snake length
			updateBodySprites();  // Update the body sprites
		}
	}

	// Move the snake based on its current direction
	void moveSnake() {
		// Move each body segment to the position of the segment ahead of it
		for (int i = snakeLength - 1; i > 0; --i) {
			snakeBody[i].setPosition(snakeBody[i - 1].getPosition());
		}

		// Move the head segment based on the current direction
		Point headPosition = snakeBody[0].getPosition();
		headPosition.x += direction.x;
		headPosition.y += direction.y;
		snakeBody[0].setPosition(headPosition);

		// Set the appropriate texture for the snake's head based on the direction
		if (direction.x == 1)
			snakeBody[0].loadTexture("HEAD_RIGHT");
		else if (direction.x == -1)
			snakeBody[0].loadTexture("HEAD_LEFT");
		else if (direction.y == 1)
			snakeBody[0].loadTexture("HEAD_DOWN");
		else if (direction.y == -1)
			snakeBody[0].loadTexture("HEAD_UP");

		updateBodySprites();  // Update body segments after moving the snake
	}

	// Check for collisions with walls or self-collisions
	void detectCollision() {
		Point headPosition = snakeBody[0].getPosition();

		// Collision with walls (outside the grid)
		if (headPosition.x < 0 || headPosition.x >= grid.getWidth() ||
			headPosition.y < 0 || headPosition.y >= grid.getHeight()) {
			// Play sound and end the game
			soundSystem.loadSound("C:/Users/ahmed_nxwp15x/Desktop/OOPProject/oopproject/Voicy_Tom Scream Effect.wav");
			soundSystem.playSound();
			isGameOver = true;  // Set the game over flag
		}

		// Collision with food (snake eats food)
		if (headPosition.x == food.x && headPosition.y == food.y) {
			growSnake();  // Grow the snake
			spawnFood();  // Spawn new food
			// Play sound for eating food
			soundSystem.loadSound("C:/Users/ahmed_nxwp15x/Desktop/OOPProject/oopproject/retro-coin-4-236671.wav");
			soundSystem.playSound();
			score += 10;  // Increase score by 10
		}

		// Self-collision (snake hits itself)
		for (int i = 1; i < snakeLength; ++i) {
			if (headPosition.x == snakeBody[i].getPosition().x &&
				headPosition.y == snakeBody[i].getPosition().y) {
				// Play sound and end the game
				soundSystem.loadSound("C:/Users/ahmed_nxwp15x/Desktop/OOPProject/oopproject/Voicy_Tom Scream Effect.wav");
				soundSystem.playSound();
				isGameOver = true;  // Set the game over flag
			}
		}
	}

	// Handle user input for controlling the snake's direction and game pause
	void handleInput() {
		// Change direction based on key presses (up, down, left, right)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && direction.y == 0) {
			direction = Point(0, -1);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && direction.y == 0) {
			direction = Point(0, 1);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && direction.x == 0) {
			direction = Point(-1, 0);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && direction.x == 0) {
			direction = Point(1, 0);
		}

		// Pause and resume the game using P and R keys
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
			isPaused = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
			isPaused = false;
		}

		// Exit the game if ESC is pressed after game over
		if (isGameOver && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window.close();  // Close the window and end the game
		}
	}

	// Increase the game difficulty by reducing the movement delay
	void increaseDifficulty() {
		moveDelay = 0.1f;  // Decrease the delay for faster movement
	}

	// Constructor for SnakeGame class
	SnakeGame()
		: grid(25, 19, 32),            // Initializing the grid with width, height, and cell size
		snakeMenu(),                   // Initializing the snake menu
		window(sf::VideoMode(800, 600), "Snake Game"),  // Creating the game window with specified resolution
		moveDelay(0.2f),               // Setting the delay between snake moves
		isPaused(false),               // Game is not paused initially
		isGameOver(false) {            // Game is not over initially

		// Seed for random number generation
		srand(static_cast<unsigned int>(time(0)));
		loadSprites();                 // Load all game sprites (background, apple, snake)
		initializeSnake();             // Initialize the snake with starting position and length
		spawnFood();                   // Spawn food at a random position

		// Load the font for text
		if (!font.loadFromFile("LilitaOne-Regular.ttf")) {
			cout << "Error loading font!" << endl;  // Error message if font loading fails
		}
	}

	// Main game loop
	void run() override {
		bool startGame = snakeMenu.displayMenu();  // Display the main menu and check if the user wants to start the game

		if (!startGame) {
			cout << "Exiting the game..." << endl;  // Exit if user decides not to start
			return;
		}

		// Set difficulty based on menu selection
		if (snakeMenu.getDifficultyLevel() == 1) {
			increaseDifficulty();  // Increase game difficulty (i.e., decrease move delay)
		}

		sf::Clock clock;  // Create a clock to track time for move delay
		while (window.isOpen()) {  // Main game loop (runs until the window is closed)
			sf::Event event;
			while (window.pollEvent(event)) {  // Poll for events (like closing the window)
				if (event.type == sf::Event::Closed) {
					window.close();  // Close the window if the close event is triggered
				}
			}

			handleInput();  // Handle user input for moving the snake or pausing the game

			// Only move the snake if the game is not paused and not over
			if (!isPaused && !isGameOver) {
				if (clock.getElapsedTime().asSeconds() > moveDelay) {  // Check if enough time has passed
					moveSnake();  // Move the snake
					detectCollision();  // Check if the snake collided with walls or itself
					clock.restart();  // Restart the clock for the next move
				}
			}

			// Update the score text to display current score
			scoreText.setString("Score: " + std::to_string(score));

			window.clear();  // Clear the window for the next frame
			window.draw(backgroundSprite);  // Draw the background
			window.draw(appleSprite);  // Draw the apple sprite

			// Draw each segment of the snake's body
			for (int i = 0; i < snakeLength; ++i) {
				window.draw(snakeBody[i].getSprite());
			}

			// If the game is paused, display a pause overlay and message
			if (isPaused) {
				sf::RectangleShape pauseOverlay(sf::Vector2f(window.getSize().x, window.getSize().y));  // Create an overlay
				pauseOverlay.setFillColor(sf::Color(0, 0, 0, 150));  // Semi-transparent black overlay
				window.draw(pauseOverlay);  // Draw the overlay

				// Display a message saying the game is paused and how to resume
				sf::Text pauseMessage;
				pauseMessage.setFont(font);
				pauseMessage.setString("     Game Paused\nPress R to Resume");
				pauseMessage.setCharacterSize(48);
				pauseMessage.setFillColor(sf::Color::Yellow);
				pauseMessage.setOutlineColor(sf::Color::Black);
				pauseMessage.setOutlineThickness(3.f);
				pauseMessage.setPosition(240.f, 220.f);  // Position the pause message on the screen
				window.draw(pauseMessage);  // Draw the pause message
			}

			// If the game is over, display a game over message
			if (isGameOver) {
				sf::RectangleShape pauseOverlay(sf::Vector2f(window.getSize().x, window.getSize().y));  // Create overlay for game over screen
				pauseOverlay.setFillColor(sf::Color(0, 0, 0, 150));  // Semi-transparent black overlay
				window.draw(pauseOverlay);  // Draw the overlay

				window.draw(gameOverText);  // Draw the "Game Over" text on the screen
			}

			window.draw(scoreText);  // Draw the current score text
			window.display();  // Display the current frame on the window
		}
	}
};
