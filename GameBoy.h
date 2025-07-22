
  #pragma once

  #include "Menu.h"
  #include "Screen.h"
  #include "InputSystem.h"
  #include "Game.h"          
  #include "SnakeGame.h"   
  #include "HangmanGame.h"   
  #include "WordleGame.h"    
  #include "SoundSystem.h"
  #include <SFML/Audio.hpp>

  #include <iostream>
  using namespace std;

  class GameBoy {
  private:
      Menu menu;                // Handles the game menus and navigation options
      Screen screen;            // Manages the window and screen for displaying graphics
      InputSystem inputSystem;  // Responsible for processing user input (keyboard, mouse, etc.)
      Game* currentGame;        // A pointer to the current game being played (e.g., Snake, Hangman, Wordle)
      SoundSystem soundSystem;  // Manages sound effects and background music during gameplay

      sf::Music backgroundMusic; // SFML object to manage background music
      string playerName;         // Holds the player's name for personalization

  public:
      GameBoy() : currentGame(nullptr), playerName("") { // Constructor initializes currentGame to nullptr and playerName to an empty string
      }

     
      void start() {
          screen.initialize();                // Initializes the screen (window) for rendering
          menu.displaySplashScreen(screen);    // Displays the splash screen with a title and instructions

          // Main loop that keeps the game running while the window is open
          while (screen.getWindow().isOpen()) {
              string selectedGame = menu.getSelectedGame(); // Gets the game selected from the menu (e.g., Snake, Hangman)

              // If the player doesn't select a game (empty string), the loop breaks, ending the game
              if (selectedGame.empty()) {
                  break;
              }

              // This is where you would handle starting the selected game logic, but it seems to be missing
              // For example, you might start the game based on the selectedGame variable
          }

          shutdown();  // Once the game loop ends (window is closed), shutdown the system
      }

      // Starts a specific game (like Snake, Hangman, etc.)
      void startGame(Game* game) {
          if (currentGame != nullptr) {  // If there’s already a game being played, delete it to prevent memory leak
              delete currentGame;
          }
          currentGame = game;    // Assign the new game to currentGame, so the system knows which game to run

          currentGame->run();     // Calls the run function of the selected game (starts the gameplay)

          screen.clear();         // Clears the screen after the game finishes, preparing for the next round or menu
      }

      // Shuts down the GameBoy system, cleaning up resources and exiting the game
      void shutdown() {
          if (currentGame != nullptr) {  // If there’s a game currently running, delete it to avoid memory leak
              delete currentGame;
              currentGame = nullptr;  // Set currentGame to nullptr after deletion
          }
          menu.exit();  // Calls the exit function of the menu to exit the game menu
      }
  };
