#include "rankings.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>


// LeaderboardEntry -> struct
bool LeaderboardEntry::operator<(const LeaderboardEntry& other) const {
    return (completion_time < other.completion_time);
}

// Leaderboard -> class

// initializer
Leaderboard::Leaderboard(const std::string& filename) 
    : filename(filename) {}

void Leaderboard::readLeaderboardFromFile() {
    // clears the leader board before putting the data in the vector
    leaderboard.clear();

    std::ifstream fhand(filename);
    if (!fhand) {
        std::cerr << "Error! File can't be opened" << std::endl;
        return;
    }

    // since the format of data is (name time)
    LeaderboardEntry entry;
    while (fhand >> entry.player_name >> entry.completion_time) {
        leaderboard.push_back(entry);
    }
    fhand.close();
}


void Leaderboard::appendDataToFile(const std::string& name, int time) {
    std::string dataToAppend = name + " " + std::to_string(time) + "\n";

    std::ofstream fhand(filename, std::ios::app);

    if (!fhand) {
        std::cout << "Error! File can't be opened" << std::endl;
    } else {
        fhand << dataToAppend;
        fhand.close();
    }

}

// this will overwrite the contents of the File
// the sorted one will be the one it will contain
void Leaderboard::writeLeaderboardToFile() {
    std::ofstream fhand(filename);
    if (!fhand) {
        std::cerr << "Error! File can't be opened" << std::endl;
        return;
    }

    for (const LeaderboardEntry& entry : leaderboard) {
        fhand << entry.player_name << " " << entry.completion_time << "\n";
    }
    fhand.close();
}

void Leaderboard::displayLeaderboard() {
    // Sort the leaderboard entries by completion time
    std::sort(leaderboard.begin(), leaderboard.end());

    // Remove duplicates based on player_name, keeping the one with the lowest time
    leaderboard.erase(std::unique(leaderboard.begin(), leaderboard.end(),
        [](const LeaderboardEntry& a, const LeaderboardEntry& b) {
            return a.player_name == b.player_name;
        }), leaderboard.end());

    int rank = 1;
    for (const LeaderboardEntry& entry : leaderboard) {
        std::string hours = std::to_string(entry.completion_time / 3600);
        std::string minutes = std::to_string((entry.completion_time % 3600) / 60);
        std::string seconds = std::to_string(entry.completion_time % 60);
        std::string gameTime = hours + ":" + minutes + ":" + seconds;

        // Display the sorted leaderboard
        std::cout << rank << ". Name: " << entry.player_name << ", Completion Time: " << gameTime << "\n";
        rank++;
    }

    if (leaderboard.empty()) {
        std::cout << "The Leaderboard is empty!\n";
    }
    std::cout << "\n\n";

}

