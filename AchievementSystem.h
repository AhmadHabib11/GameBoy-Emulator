#pragma once

#include <iostream>
using namespace std;



class AchievementSystem {
private:
	Achievement[] achievements;
	Progress progress;

public:
	trackAchievement(string achievement);
	updateProgress();


};