#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Menu.h"
#include "Game.h"

class Screen {
private:
    int resolutionX;                    // stores the width of the screen
    int resolutionY;                    // stores the height of the screen
    sf::RenderWindow window;            // the main window where everything is drawn
    sf::RenderTexture displayBuffer;    

public:
   
    Screen(int resolutionX = 1200, int resolutionY = 800, const std::string& title = "GameBoy Emulator")
        : resolutionX(resolutionX), resolutionY(resolutionY) {
        window.create(sf::VideoMode(resolutionX, resolutionY), title);
        displayBuffer.create(resolutionX, resolutionY); 
    }

   
    void initialize() {
        window.setFramerateLimit(60); // limit the frame rate to 60 FPS
        
    }

    
    sf::RenderWindow& getWindow() {
        return window;
    }
 
    void render(const Game& game) {
        
        window.clear();
        
        window.display();
    }


    void manageState() {
        

    }

    
    void clear(const sf::Color& color = sf::Color::Black) {
        window.clear(color);
    }

    
    void display() {
        window.display();
    }

    
    bool isOpen() const {
        return window.isOpen();
    }

    
    void close() {
        window.close();
    }

    
    int getWidth() const {
        return resolutionX;
    }

    
    int getHeight() const {
        return resolutionY;
    }
};






