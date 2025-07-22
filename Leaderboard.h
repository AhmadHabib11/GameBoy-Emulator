#pragma once
#include <iostream>
using namespace std;

class Leaderboard {
private:
	Score[] highScores;
	Player[] topPlayers;

public:

	updateScore(Player player, int score);
	displayTopScores();
	resetLeaderboard();
	saveLeaderboard();
	loadLeaderboard();

};