#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>

using namespace std;

class InputSystem {
public:
    
	// handles menu navigation by detecting up and down arrow key presses
    static void handleMenuNavigation(sf::Event& event, int& selectedIndex, sf::Text menuText[], int menuSize) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up) {
                menuText[selectedIndex].setFillColor(sf::Color(50, 50, 50)); 
                selectedIndex = (selectedIndex - 1 + menuSize) % menuSize; 
                menuText[selectedIndex].setFillColor(sf::Color::Red);



            }
            else if (event.key.code == sf::Keyboard::Down) {
                menuText[selectedIndex].setFillColor(sf::Color(50, 50, 50)); 
                selectedIndex = (selectedIndex + 1) % menuSize;
                menuText[selectedIndex].setFillColor(sf::Color::Red); 
            }
        }
    }

	// checks if a specific key is currently pressed
    static bool isKeyPressed(sf::Keyboard::Key key) {
        return sf::Keyboard::isKeyPressed(key);
    }

 

	// handles events like closing the window
    static void processEvents(sf::RenderWindow& window, bool& isRunning) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                isRunning = false; 
                window.close();
            }
        }
    }
};

