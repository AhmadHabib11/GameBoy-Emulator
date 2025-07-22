#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class HangmanFigure {
private:
    int lives;                        // keeps track of the number of lives remaining (7 in total)
    sf::Texture gallowTexture;        // texture for the gallows image
    sf::Sprite gallowSprite;          // sprite for the gallows, which will be drawn on the screen

    // Shape components to represent the hangman figure (head, body, arms, legs)
    sf::CircleShape head;
    sf::RectangleShape body;
    sf::RectangleShape leftArm;
    sf::RectangleShape rightArm;
    sf::RectangleShape leftLeg;
    sf::RectangleShape rightLeg;

public:
    // Constructor: initializes the figure with 7 lives and loads all textures and shapes
    HangmanFigure() : lives(7) {

        // Try to load the gallows texture from a file
        if (!gallowTexture.loadFromFile("gallows.png")) {
            cout << "Error loading gallows.png!" << endl;  // Print error if loading fails
        }

        // Set the texture to the gallows sprite
        gallowSprite.setTexture(gallowTexture);

        // Set the position of the gallows sprite on the screen
        gallowSprite.setPosition(100.f, 100.f);

        // Scale the gallows sprite to fit a particular size (300x350)
        float scaleX = 300.f / gallowTexture.getSize().x;
        float scaleY = 350.f / gallowTexture.getSize().y;
        gallowSprite.setScale(scaleX, scaleY);

        // Set up the head (circle shape)
        head.setRadius(24);  // radius of the head
        head.setFillColor(sf::Color::White);  // fill color for the head (white)
        head.setPosition(280.f, 265.f);  // position of the head

        // Set up the body (rectangle shape)
        body.setSize(sf::Vector2f(10.f, 80.f));  // width and height of the body
        body.setFillColor(sf::Color::White);  // fill color for the body (white)
        body.setPosition(300.f, 310.f);  // position of the body

        // Set up the left arm (rectangle shape)
        leftArm.setSize(sf::Vector2f(60.f, 10.f));  // width and height of the left arm
        leftArm.setFillColor(sf::Color::White);  // fill color for the left arm (white)
        leftArm.setPosition(300.f, 310.f);  // position of the left arm

        // Set up the right arm (rectangle shape)
        rightArm.setSize(sf::Vector2f(60.f, 10.f));  // width and height of the right arm
        rightArm.setFillColor(sf::Color::White);  // fill color for the right arm (white)
        rightArm.setPosition(240.f, 310.f);  // position of the right arm

        // Set up the left leg (rectangle shape)
        leftLeg.setSize(sf::Vector2f(10.f, 60.f));  // width and height of the left leg
        leftLeg.setFillColor(sf::Color::White);  // fill color for the left leg (white)
        leftLeg.setPosition(300.f, 390.f);  // position of the left leg
        leftLeg.setRotation(-45.f);  // rotate the left leg at a 45-degree angle

        // Set up the right leg (rectangle shape)
        rightLeg.setSize(sf::Vector2f(10.f, 60.f));  // width and height of the right leg
        rightLeg.setFillColor(sf::Color::White);  // fill color for the right leg (white)
        rightLeg.setPosition(300.f, 390.f);  // position of the right leg
        rightLeg.setRotation(45.f);  // rotate the right leg at a 45-degree angle
    }

    // draw: This method is called to render the hangman figure on the window based on the number of lives left
    void draw(sf::RenderWindow& window, int livesLeft) {

        // Draw the gallows background
        window.draw(gallowSprite);

        // Conditionally draw each body part based on the number of lives left
        if (livesLeft <= 6)
            window.draw(head);     // Draw the head if there are 6 or fewer lives left
        if (livesLeft <= 5)
            window.draw(body);     // Draw the body if there are 5 or fewer lives left
        if (livesLeft <= 4)
            window.draw(leftArm);  // Draw the left arm if there are 4 or fewer lives left
        if (livesLeft <= 3)
            window.draw(rightArm); // Draw the right arm if there are 3 or fewer lives left
        if (livesLeft <= 2)
            window.draw(leftLeg);  // Draw the left leg if there are 2 or fewer lives left
        if (livesLeft <= 1)
            window.draw(rightLeg); // Draw the right leg if there is 1 or fewer lives left
    }
};
