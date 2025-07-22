#pragma once
#include <SFML/Graphics.hpp>
using namespace std;
class Keyboard {
public:

    sf::RectangleShape keys[27];  // array to hold key shapes (26 letters + Enter key)
    sf::Text labels[27];  // array to hold the labels on the keys
    bool used[26];  // tracks if a letter key has been used
    bool highlighted[27];  // tracks if a key is highlighted
    sf::Color normalColor, highlightColor;  // colors for normal and highlighted states
    float xOffset, yOffset;  // position offsets for the keyboard

	Keyboard(const sf::Font& font, float x = 50.f, float y = 400.f)
		: xOffset(x), yOffset(y), normalColor(sf::Color::White), highlightColor(sf::Color::Blue) {

        // initialize letter keys (A-Z)
		for (int i = 0; i < 26; i++) {
			keys[i].setSize({ 30.f, 40.f });
			keys[i].setPosition(x + (i % 10) * 35.f, y + (i / 10) * 50.f);
			keys[i].setFillColor(normalColor);
			keys[i].setOutlineThickness(1.f);
			keys[i].setOutlineColor(sf::Color::Black);

			char letter = static_cast<char>(i + 'A');
			labels[i].setFont(font);
			labels[i].setString(string(1, letter));
			labels[i].setCharacterSize(20);
			labels[i].setFillColor(sf::Color::Black);
			labels[i].setPosition(keys[i].getPosition().x + 5.f, keys[i].getPosition().y + 5.f);

			used[i] = false; // mark key as unused initially
			highlighted[i] = false;  // mark key as not highlighted initially
		}

		
        // initialize 'Enter' key
		keys[26].setSize({ 80.f, 40.f });
		keys[26].setPosition(x + 10 * 35.f, y + 2 * 50.f);
		keys[26].setFillColor(normalColor);
		keys[26].setOutlineThickness(1.f);
		keys[26].setOutlineColor(sf::Color::Blue);

		labels[26].setFont(font);
		labels[26].setString("Enter");
		labels[26].setCharacterSize(20);
		labels[26].setFillColor(sf::Color::Black);
		labels[26].setPosition(keys[26].getPosition().x + 5.f, keys[26].getPosition().y + 5.f);
	}

    // reset all keys to their default state
	void reset() {
		for (int i = 0; i < 26; i++) {
			keys[i].setFillColor(normalColor);
			used[i] = false;
			highlighted[i] = false;
		}
		
		keys[26].setFillColor(normalColor);
		highlighted[26] = false;
	}

    // highlight or unhighlight a specific key
	void highlightKey(int index, bool highlight) {
		if (index >= 0 && index < 26) {  
			if (highlight) {
				keys[index].setFillColor(sf::Color::Black);  
			}
			else {
				keys[index].setFillColor(sf::Color::White);  
			}
		}
		else if (index == 26) {  
			if (highlight) {
				keys[26].setFillColor(sf::Color::Black);  
			}
			else {
				keys[26].setFillColor(sf::Color::White);  
			}
		}
	}


    // set the position of the keyboard
	void setPosition(float x, float y) {
		xOffset = x;
		yOffset = y;
		for (int i = 0; i < 26; i++) {
			keys[i].setPosition(xOffset + (i % 10) * 35.f, yOffset + (i / 10) * 50.f);
			labels[i].setPosition(keys[i].getPosition().x + 5.f, keys[i].getPosition().y + 5.f);
		}
		
		keys[26].setPosition(xOffset + 7 * 35.f, yOffset + 2 * 50.f);
		labels[26].setPosition(keys[26].getPosition().x + 5.f, keys[26].getPosition().y + 5.f);
	}

    // draw all the keys and labels on the window
	void draw(sf::RenderWindow& window) {
		for (int i = 0; i < 27; i++) {
			window.draw(keys[i]);
			window.draw(labels[i]);
		}
	}
    // update highlighting state based on elapsed time
	void update(sf::Clock& highlightClock) {
		if (highlightClock.getElapsedTime().asSeconds() > 0.2f) {
	
			for (int i = 0; i < 27; i++) {
				if (highlighted[i]) {
					highlightKey(i, false);
				}
			}
		}
	}
};
