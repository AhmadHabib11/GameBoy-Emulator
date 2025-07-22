#pragma once

class Grid {
private:
    int width;      // stores the width of the grid
    int height;     // stores the height of the grid
    int cellSize;   // stores the size of each cell in the grid

public:
    // Constructor: Initializes the width, height, and cellSize.
    
    Grid(int w = 0, int h = 0, int cSize = 0)
        : width(w), height(h), cellSize(cSize) {}

    // getWidth: Returns the width of the grid.
    int getWidth() const {
        return width; // returns the width value of the grid
    }

    // getHeight: Returns the height of the grid.
    int getHeight() const {
        return height; // returns the height value of the grid
    }

    // getCellSize: Returns the size of each individual cell in the grid.
    int getCellSize() const {
        return cellSize; // returns the size of each cell in the grid
    }
};
