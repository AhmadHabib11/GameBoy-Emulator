#pragma once


// this class is used for the snake game representing its position on the grid and its body segments

class Point {
public:
    int x, y;  // Coordinates of the point (x, y)

    // Constructor: Initializes the point with given x and y values (default 0, 0)
    Point(int x = 0, int y = 0) : x(x), y(y) {}

    // Method to check if two points are equal
    bool equals(const Point& other) const {
        // Compare the x and y values of the current point and another point (other)
        return x == other.x && y == other.y;
    }
};