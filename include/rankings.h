// ketsup@asura

#ifndef RANKINGS_H
#define RANKINGS_H

#include <string>
#include <vector>


struct LeaderboardEntry {
    std::string player_name;
    int score;
};


class Leaderboard {
private:
    std::string filename;
    std::vector<LeaderboardEntry> leaderboard;

    void selectionSort(std::vector<LeaderboardEntry>& leaderboard);
    void bubbleSort(std::vector<LeaderboardEntry>& leaderboard);
    void insertionSort(std::vector<LeaderboardEntry>& leaderboard);

public:
    Leaderboard(const std::string& filename);
    void printDifficultyLevels();
    void printInfiteRoulette();
    bool isFileExistAndNotEmpty();
    void readLeaderboardFromFile();
    void writeLeaderboardToFile();
    void displayLeaderboard();
    void appendDataToFile(const std::string& name, int score);
};

#endif

