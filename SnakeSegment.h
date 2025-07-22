#pragma once
#include <SFML/Graphics.hpp>
#include "Point.h"

using namespace std;

class SnakeSegment {
private:
    Point position;
    sf::Sprite sprite;
    sf::Texture texture;
    string segmentType;

public:
    SnakeSegment() {}


    SnakeSegment(Point pos, const string& type) : position(pos), segmentType(type) {
        loadTexture(type);
        sprite.setPosition(pos.x * 32, pos.y * 32);
    }

    // load texture based on segment type (head, body, tail)
    void loadTexture(const string& type) {
        // match segment type with appropriate texture
        if (type == "HEAD_RIGHT") {
            texture.loadFromFile("head_right.png");
        }
        else if (type == "HEAD_LEFT") {
            texture.loadFromFile("head_left.png");
        }
        else if (type == "HEAD_UP") {
            texture.loadFromFile("head_up.png");
        }
        else if (type == "HEAD_DOWN") {
            texture.loadFromFile("head_down.png");
        }
        else if (type == "BODY_HORIZONTAL") {
            texture.loadFromFile("body_horizontal.png");
        }
        else if (type == "BODY_VERTICAL") {
            texture.loadFromFile("body_vertical.png");
        }
        else if (type == "BODY_TOPLEFT") {
            texture.loadFromFile("body_topleft.png");
        }
        else if (type == "BODY_TOPRIGHT") {
            texture.loadFromFile("body_topright.png");
        }
        else if (type == "BODY_BOTTOMLEFT") {
            texture.loadFromFile("body_bottomleft.png");
        }
        else if (type == "BODY_BOTTOMRIGHT") {
            texture.loadFromFile("body_bottomright.png");
        }
        else if (type == "TAIL_LEFT") {
            texture.loadFromFile("tail_left.png");
        }
        else if (type == "TAIL_RIGHT") {
            texture.loadFromFile("tail_right.png");
        }
        else if (type == "TAIL_UP") {
            texture.loadFromFile("tail_up.png");
        }
        else if (type == "TAIL_DOWN") {
            texture.loadFromFile("tail_down.png");
        }
        sprite.setTexture(texture);
    }


    // update the tail sprite based on previous segment position
    void updateTailSprite(Point prevPos) {
        // determine tail direction based on previous position
        if (prevPos.x > position.x) {
            loadTexture("TAIL_LEFT");
        }
        else if (prevPos.x < position.x) {
            loadTexture("TAIL_RIGHT");
        }
        else if (prevPos.y > position.y) {
            loadTexture("TAIL_UP");
        }
        else if (prevPos.y < position.y) {
            loadTexture("TAIL_DOWN");
        }
    }




    // Update the position of the segment
    void setPosition(Point pos) {
        position = pos;
        sprite.setPosition(pos.x * 32, pos.y * 32); // 32 is the cell size
    }

    Point getPosition() const {
        return position;
    }

    sf::Sprite getSprite() const {
        return sprite;
    }

    string getSegmentType() const {
        return segmentType;
    }
};

