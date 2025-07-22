#pragma once
#include <iostream>
#include <SFML/Audio.hpp>
using namespace std;


class SoundSystem {
private:
    // sf::SoundBuffer is used to hold the sound data that we load from a file
    sf::SoundBuffer soundBuffer;

    // sf::Sound is used to play the sound
    sf::Sound sound;

public:
    // loadSound: Loads a sound file into the sound buffer.
    // Takes the file path as input and returns true if loading was successful, false otherwise.
    bool loadSound(const string& filepath) {
        // Attempts to load the sound from the given file path
        if (!soundBuffer.loadFromFile(filepath)) {
            cerr << "Error loading sound: " << filepath << endl;  // Logs an error message if the file cannot be loaded
            return false; // Returns false if loading fails
        }

        // If the sound is successfully loaded, set the buffer of the sound object to the loaded soundBuffer
        sound.setBuffer(soundBuffer);
        return true; // Return true indicating successful loading
    }

    // playSound: Plays the sound that was loaded into the sound buffer.
    void playSound() {
        sound.play(); // Plays the loaded sound
    }

  
};
