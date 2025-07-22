#pragma once

#include <iostream>
#include "SoundSystem.h"  
using namespace std;

// the Game class is the base class for all games, so it's meant to be inherited by specific game classes.
class Game {
protected:
    string name;  // this stores the name of the game
    int score;    // this stores the player's score in the game
    SoundSystem* soundSystem;  // this is a pointer to a SoundSystem object that handles game sounds

public:
    // Constructor that initializes the score to 0 and creates a new SoundSystem object
    Game() : score(0), soundSystem(new SoundSystem()) {}

    // A pure virtual function, which means any derived class must provide its own implementation of 'run'
    virtual void run() = 0;

    // Virtual destructor to make sure when the derived class object is destroyed, it also deletes the sound system object
    virtual ~Game() {
        delete soundSystem;  // clean up the soundSystem memory to prevent memory leaks
    }

    // This function plays a sound for the game. It takes the sound file's name as a parameter
    void playGameSound(const string& soundFile) {
        // attempt to load the sound file using the SoundSystem class
        if (!soundSystem->loadSound(soundFile)) {
            // if loading the sound fails, print an error message
            cout << "Failed to load sound: " << soundFile << endl;
        }
        else {
            // if the sound is successfully loaded, play the sound
            soundSystem->playSound();
        }
    }

    // This function updates the score of the game by adding the points passed as an argument
    void updateScore(int points) {
        score += points;  // add points to the current score
    }

    // This function returns the current score of the game
    int getScore() const {
        return score;  // simply returns the score
    }
};
