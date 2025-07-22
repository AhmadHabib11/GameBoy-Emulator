#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Category.h"
#include "HangmanFigure.h"
#include "HangmanMenu.h"
#include "Game.h"
#include "SFML/Audio.hpp"


using namespace std;

class HangmanGame : public Game {
private:
	string word;              
	string guessedLetters;    
	string incorrectGuesses;  
	int lives;                
	Category category;        
	HangmanFigure hangmanFigure; 
	HangmanMenu menu;

	sf::RenderWindow window;  
	sf::Font font;            
	sf::Text wordText;        
	sf::Text titleText;       
	sf::Text livesText;       
	sf::Text endMessageText;  
	sf::Text hintText;        
	sf::Text exitMessageText; 
	sf::Texture backgroundTexture; 
	sf::Sprite backgroundSprite;   

	sf::SoundBuffer deathSoundBuffer;
	sf::Sound deathSound;


	bool gameOver;            // flag to check if the game is over
	bool paused;              // flag to check if the game is paused             

public:
	
	void initializeGraphics() {
		window.create(sf::VideoMode(800, 600), "Hangman Game");

		if (!font.loadFromFile("LilitaOne-Regular.ttf")) {
			cout << "Error loading font!" << endl;
		}

		if (!backgroundTexture.loadFromFile("hangman.jpg")) {
			cout << "Error loading background image!" << endl;
		}

		if (!deathSoundBuffer.loadFromFile("C:/Users/ahmed_nxwp15x/Desktop/OOPProject/oopproject/Mario Death - QuickSounds.com.wav")) {
			cout << "Error loading death sound!" << endl;
		}
		deathSound.setBuffer(deathSoundBuffer);

		sf::Vector2u windowSize = window.getSize();
		backgroundSprite.setTexture(backgroundTexture);


		// scale the background to fit the window
		backgroundSprite.setScale(
			static_cast<float>(windowSize.x) / backgroundTexture.getSize().x,
			static_cast<float>(windowSize.y) / backgroundTexture.getSize().y
		);



		titleText.setFont(font);
		titleText.setCharacterSize(50);
		titleText.setFillColor(sf::Color::White);
		titleText.setPosition(230.f, 10.f);
		titleText.setOutlineColor(sf::Color::Black);
		titleText.setOutlineThickness(3.f);

		wordText.setFont(font);
		wordText.setCharacterSize(40);
		wordText.setFillColor(sf::Color::White);
		wordText.setOutlineColor(sf::Color::Black);
		wordText.setOutlineThickness(2.f);
		wordText.setPosition(450.f, 200.f);

		livesText.setFont(font);
		livesText.setCharacterSize(30);
		livesText.setFillColor(sf::Color::Red);
		livesText.setPosition(680.f, 10.f);
		updateLivesText();

		hintText.setFont(font);
		hintText.setCharacterSize(20);
		hintText.setFillColor(sf::Color::White);
		hintText.setPosition(420.f, 130.f);
		hintText.setOutlineColor(sf::Color::Black);
		hintText.setOutlineThickness(2.f);
		hintText.setString("Hint: The word is from " + category.getCategoryName() + " category.");

		endMessageText.setFont(font);
		endMessageText.setCharacterSize(30);
		endMessageText.setFillColor(sf::Color::Yellow);
		endMessageText.setPosition(450.f, 280.f);
		endMessageText.setOutlineColor(sf::Color::Black);
		endMessageText.setOutlineThickness(2.f);
		endMessageText.setString("");

		exitMessageText.setFont(font);
		exitMessageText.setCharacterSize(25);
		exitMessageText.setFillColor(sf::Color::White);
		exitMessageText.setPosition(430.f, 450.f);
		exitMessageText.setOutlineColor(sf::Color::Black);
		exitMessageText.setOutlineThickness(2.f);
		exitMessageText.setString("PRESS ESC TO EXIT THE GAME ...");
	};




	// updates word progress based on guessed letters
	void updateProgressText() {
		string displayWord = "";
		for (int i = 0; i < word.length(); i++) {
			bool found = false;
			for (int j = 0; j < guessedLetters.length(); j++) {
				if (word[i] == guessedLetters[j]) {
					found = true;
					break;
				}
			}
			if (found) {
				displayWord += word[i];
				displayWord += " ";
			}
			else {
				displayWord += "_ ";
			}
		}
		wordText.setString(displayWord);
	}


	// updates lives text
	void updateLivesText() {
		string livesStr = "Lives: ";
		int tempLives = lives;
		string livesNum = "";
		while (tempLives > 0) {
			livesNum = char(tempLives % 10 + '0') + livesNum;
			tempLives /= 10;
		}
		if (livesNum == "")
			livesNum = "0";
		livesStr += livesNum;
		livesText.setString(livesStr);
	}

	// checks if the character is a letter
	bool isAlpha(char ch) {
		return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
	}


	// checks if the guessed character is in the word
	bool contains(const string& str, char ch) {
		for (int i = 0; i < str.length(); i++) {
			if (str[i] == ch) {
				return true;
			}
		}
		return false;
	}


	// tracks the guesses and adds to guessedLetters if not already guessed
	void trackGuesses(char guess) {
		
		for (int i = 0; i < guessedLetters.length(); i++) {
			if (guessedLetters[i] == guess) {
				return; 
			}
		}
		guessedLetters += guess; 
	}

	// draws the hangman figure based on remaining lives
	void drawHangman() {
		hangmanFigure.draw(window, lives); 
	}

	// manages lives based on correct or incorrect guesses
	void manageLives(char guess) {
		
		bool incorrectGuess = true;

		// check if guess is incorrect
		for (int i = 0; i < word.length(); i++) {
			if (word[i] == guess) {
				incorrectGuess = false; 
				break;
			}
		}

		// if incorrect guess, subtract a life
		if (incorrectGuess) {
			for (int i = 0; i < incorrectGuesses.length(); i++) {
				if (incorrectGuesses[i] == guess) {
					return; 
				}
			}

		
			incorrectGuesses += guess;
			lives--; 
			updateLivesText(); 
		}
	}

	// handles the guessing logic and checks if game is over
	void handleGuess(char guess) {
		
		for (int i = 0; i < guessedLetters.length(); i++) {
			if (guessedLetters[i] == guess) {
				return;
			}
		}

		trackGuesses(guess); 

		bool correctGuess = false;
		
		for (int i = 0; i < word.length(); i++) {
			if (word[i] == guess) {
				correctGuess = true; 
				break;
			}
		}


		if (!correctGuess) {
			manageLives(guess); // reduce lives for incorrect guess
		}

		// check if word is guessed or game over
		if (hasGuessedWord() || lives <= 0) {
			handleGameOver(); 
		}
	}


	// checks if the word has been fully guessed
	bool hasGuessedWord() {
		for (int i = 0; i < word.length(); i++) {
			if (!contains(guessedLetters, word[i])) {
				return false;
			}
		}
		return true;
	}

	// handles end of the game and displays the result
	void handleGameOver() {
		if (hasGuessedWord()) {
			endMessageText.setString("Congrats!\nYou guessed the\nword correctly!");
		}
		else {
			endMessageText.setString("Better luck next time!\nThe word was: " + word);

			deathSound.play();
		}
		gameOver = true;
	}


	HangmanGame() : lives(7), gameOver(false), paused(false), window(sf::VideoMode(800, 600), "Hangman Game") {
		srand(time(0));
		word = category.getSelectedWord();  
		initializeGraphics();
		
	}

	


	void run() override {
		if (!menu.displayMenu()) {
			return; // exit if menu is closed
		}

		bool paused = false; 

		while (window.isOpen()) {
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					window.close();
				}

				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Escape) {
						window.close();
					}
					else if (event.key.code == sf::Keyboard::LControl) {
						paused = true; 
					}
					else if (event.key.code == sf::Keyboard::LShift) {
						paused = false; 
					}
				}

				if (!paused && !gameOver && event.type == sf::Event::TextEntered) {
					char guess = static_cast<char>(event.text.unicode);
					if (isAlpha(guess)) {
						handleGuess(guess);
					}
				}
			}

			window.clear(); 

			
			window.draw(backgroundSprite);

			if (!paused) {
			
				updateProgressText();
				window.draw(backgroundSprite);  
				drawHangman();
				window.draw(titleText);
				window.draw(hintText);
				window.draw(wordText);
				window.draw(livesText);

				if (gameOver) {
					window.draw(endMessageText);
					window.draw(exitMessageText);
				}

				window.display(); 
			}
			else {



				// if game is paused
				sf::RectangleShape pauseOverlay(sf::Vector2f(window.getSize().x, window.getSize().y));
				pauseOverlay.setFillColor(sf::Color(0, 0, 0, 150));  
				window.draw(pauseOverlay);  

				
				sf::Text pauseMessageText;
				pauseMessageText.setFont(font);
				pauseMessageText.setCharacterSize(48);
				pauseMessageText.setFillColor(sf::Color::Yellow);
				pauseMessageText.setOutlineColor(sf::Color::Black);
				pauseMessageText.setOutlineThickness(2.f);
				pauseMessageText.setPosition(200.f, 240.f);
				pauseMessageText.setString("       GAME PAUSED\nPress SHIFT to Resume");
				window.draw(pauseMessageText);

				window.display(); 
			}
		}
	}



};
