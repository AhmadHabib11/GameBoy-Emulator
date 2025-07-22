#pragma once

#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;
// The Category class handles the selection of categories and words for a game.
class Category {
private:
    // categories array holds the names of the three categories: "Animals", "Countries", "Food"
    string categories[3] = { "Animals", "Countries", "Food" };

    // words array stores words for each category. 
    // Each category (Animals, Countries, Food) has an array of 10 words.
    string words[3][10] = {
        { "elephant", "giraffe", "zebra", "tiger", "dolphin", "penguin", "rabbit", "monkey", "cheetah", "kangaroo" },
        { "canada", "brazil", "germany", "japan", "australia", "india", "egypt", "russia", "france", "italy" },
        { "pizza", "burger", "pasta", "sushi", "apple", "banana", "grape", "orange", "chocolate", "cookie" }
    };

    int selectedCategory;    // stores the index of the selected category (0 = Animals, 1 = Countries, 2 = Food)
    string selectedWord;     // stores the randomly selected word from the chosen category

public:
    // Constructor: initializes the random number generator and selects a random category and word
    Category() {
        srand(time(0));  // seeds the random number generator with the current time
        selectedCategory = rand() % 3;  // randomly selects a category (0, 1, or 2)
        selectRandomWord();  // selects a random word from the selected category
    }

    // selectRandomWord: selects a random word from the chosen category
    void selectRandomWord() {
        int randomIndex = rand() % 10;  // selects a random index from 0 to 9
        selectedWord = words[selectedCategory][randomIndex];  // assigns the selected word to the class variable
    }

    // getSelectedWord: returns the currently selected word
    string getSelectedWord() const {
        return selectedWord;  // simply returns the word
    }

    // getCategoryName: returns the name of the selected category (Animals, Countries, or Food)
    string getCategoryName() const {
        return categories[selectedCategory];  // returns the name of the category
    }
};