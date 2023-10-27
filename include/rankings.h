// ketsup@asura

#ifndef RANKINGS_H
#define RANKINGS_H

#include <string>
#include <vector>


struct LeaderboardEntry {
    std::string player_name;
    int completion_time;

    // Overload the '<' operator for sorting
    bool operator<(const LeaderboardEntry& other) const;
};

class Leaderboard {
private:
    std::string filename;
    std::vector<LeaderboardEntry> leaderboard;

public:
    Leaderboard(const std::string& filename);
    void readLeaderboardFromFile();
    void writeLeaderboardToFile();
    void displayLeaderboard();
    void appendDataToFile(const std::string& name, int time );
};

#endif

