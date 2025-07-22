#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Letter {
public:
    char character;
    sf::RectangleShape box;
    sf::Text text;
    sf::Color boxColor;


	// constructor to set the initial position and box color
    Letter(float x = 0.f, float y = 0.f) : character(' '), boxColor(sf::Color::White) {
        box.setSize({ 50.f, 50.f });
        box.setPosition(x, y);
        box.setFillColor(boxColor);
        box.setOutlineThickness(2.f);
        box.setOutlineColor(sf::Color::Black);
    }

	// sets the character and updates the text
    void setCharacter(char c, const sf::Font& font) {
        character = c;
        text.setFont(font);
        text.setString(std::string(1, c));
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Black);
        text.setPosition(box.getPosition().x + 15.f, box.getPosition().y + 5.f);
    }

	// draws the letter (box + character) on the window
    void draw(sf::RenderWindow& window) {
        box.setFillColor(boxColor);
        window.draw(box);
        window.draw(text);
    }
};
