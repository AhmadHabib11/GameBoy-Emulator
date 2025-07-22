#pragma once
#include <iostream>
using namespace std;

class Player {
private:
    string name;         
    int highScores[10];  

public:
    
    Player() : name("") {
        
        for (int i = 0; i < 10; i++) {
            highScores[i] = 0;
        }
    }

    void setName(const string& playerName) { name = playerName; }
    string getName() const { return name; }

  
 /*   void saveProgress() {
        cout << "Saving progress for player: " << name << endl;
        for (int i = 0; i < 10; i++) {
            cout << "High Score [" << i << "]: " << highScores[i] << endl;
        }
    }

    void loadProgress() {
        cout << "Loading progress for player: " << name << endl;
      
        for (int i = 0; i < 10; i++) {
            highScores[i] = i * 10;  
        }
        cout << "Progress loaded successfully." << endl;
    }


    void updateHighScore(int score, int index) {
        if (index >= 0 && index < 10) {
            highScores[index] = score;
        }
    }

    int getHighScore(int index) const {
        if (index >= 0 && index < 10) {
            return highScores[index];
        }
        return -1; 
    }*/
};
