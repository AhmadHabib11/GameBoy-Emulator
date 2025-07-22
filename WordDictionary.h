#pragma once
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

class WordDictionary {
private:
    string wordList[10];

public:
    string chosenWords[5];

    WordDictionary() {

        wordList[0] = "APPLE";
        wordList[1] = "CRANE";
        wordList[2] = "BRAVE";
        wordList[3] = "WATCH";
        wordList[4] = "EAGLE";
        wordList[5] = "HOUSE";
        wordList[6] = "STONE";
        wordList[7] = "PLANT";
        wordList[8] = "CHESS";
        wordList[9] = "MOUSE";


        srand(time(0));


        bool selected[10] = { false };  // keep track of selected words
        for (int i = 0; i < 5; i++) {  // pick 5 unique words
            int randomIndex;
            do {
                randomIndex = rand() % 10;  // get random index
            } while (selected[randomIndex]);  // ensure not picked before
            chosenWords[i] = wordList[randomIndex];  // assign word
            selected[randomIndex] = true;  // mark as selected
        }
    }


    // checks if the word is in the list
    bool validateWord(const string& word) const {
        for (int i = 0; i < 10; i++) {
            if (wordList[i] == word) {
                return true;
            }
        }
        return false;
    }


    const string* getChosenWords() const {
        return chosenWords;
    }
};
