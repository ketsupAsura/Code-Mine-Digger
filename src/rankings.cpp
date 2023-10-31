// ketsup@asura
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <iomanip>
#include "rankings.h"

// initializer
Leaderboard::Leaderboard(const std::string& filename) 
: filename(filename) {}

void Leaderboard::selectionSort(std::vector<LeaderboardEntry>& leaderboard) {
    for (int i = 0 ; i < leaderboard.size() - 1; i++) {
        int min = i;
        for (int j = i + 1; j < leaderboard.size(); j++) {
            if (leaderboard[min].score < leaderboard[j].score) {
                min = j;
            }
        }

        LeaderboardEntry temp = leaderboard[i];
        leaderboard[i] = leaderboard[min];
        leaderboard[min] = temp;
    }
}

void Leaderboard::bubbleSort(std::vector<LeaderboardEntry>& leaderboard) {
    for (int i = 0; i < leaderboard.size() - 1; i++) {
        for (int j = 0; j < leaderboard.size() - i - 1; j++) {
            if(leaderboard[j].score > leaderboard[j+1].score) {
                LeaderboardEntry temp = leaderboard[j];
                leaderboard[j] = leaderboard[j+1];
                leaderboard[j+1] = temp;
            }
        }
    }
}

void Leaderboard::insertionSort(std::vector<LeaderboardEntry>& leaderboard) {
    for (int i = 1; i < leaderboard.size(); i++) {
        LeaderboardEntry temp = leaderboard[i];
        int j = i - 1;

        while (j >= 0 && leaderboard[j].score > temp.score) {
            leaderboard[j+1] = leaderboard[j];
            j--;
        }
        leaderboard[j + 1] = temp;
    }
}


// format to print the leaderboard of difficulty levels  game
void Leaderboard::printDifficultyLevels() {
    std::cout << "\t+--------------+-------------------------+--------------------+\n";
    std::cout << std::right << std::setw(12) << "\t|     Rank     |";
    std::cout << std::right << std::setw(12) << "       Player Name       |";
    std::cout << std::right << std::setw(12) <<  "        Time        |\n";
    std::cout << "\t+--------------+-------------------------+--------------------+\n";

    int rank = 1;
    for (const LeaderboardEntry& entry : leaderboard) {
        std::string hours = std::to_string(entry.score / 3600);
        std::string minutes = std::to_string((entry.score % 3600) / 60);
        std::string seconds = std::to_string(entry.score % 60);
        std::string gameTime = hours + ":" + minutes + ":" + seconds;

        // Display the sorted leaderboard
        std::cout << "\t|     " << std::left << std::setw(9) << rank << "|";  
        std::cout << "  " <<  std::left << std::setw(12) << entry.player_name << "           |";
        std::cout << "  "<< std::left << std::setw(12)  << gameTime << "      |\n";
        std::cout << "\t+--------------+-------------------------+--------------------+\n";

        //std::cout << rank << ". Name: " << entry.player_name << ", Completion Time: " << gameTime << "\n";
        rank++;
    }
}

// format to print the leaderboard of infinite roulette game
void Leaderboard::printInfiteRoulette() {
    std::cout << "\t+--------------+-------------------------+--------------------+\n";
    std::cout << std::right << std::setw(12) << "\t|     Rank     |";
    std::cout << std::right << std::setw(12) << "       Player Name       |";
    std::cout << std::right << std::setw(12) <<  "     Win Streak     |\n";
    std::cout << "\t+--------------+-------------------------+--------------------+\n";

    int rank = 1;
    for (const LeaderboardEntry& entry : leaderboard) {
        std::cout << "\t|     " << std::left << std::setw(9) << rank << "|";  
        std::cout << "  " <<  std::left << std::setw(12) << entry.player_name << "           |";
        std::cout << "        "<< std::left << std::setw(12) << entry.score << "|\n";
        std::cout << "\t+--------------+-------------------------+--------------------+\n";

        rank++;
    }
}

bool Leaderboard::isFileExistAndNotEmpty() {
    bool isFileValid = true;
    std::string path = "data/" + filename;

    std::fstream fhand(path, std::ios::in);

    // does the file exist
    if (!fhand.is_open()) { isFileValid = false; }

    // is the file empty
    if (fhand.peek() == std::ifstream::traits_type::eof()) { isFileValid = false; }

    fhand.close();
    return isFileValid;
}

void Leaderboard::readLeaderboardFromFile() {
    // clears the leader board before putting the data in the vector
    leaderboard.clear();

    // open the file in read mode
    std::fstream fhand;
    std::string path = "data/" + filename;
    fhand.open(path, std::ios::in);

    // kept putting the data until its the end of the file
    while (!fhand.eof()) {
        LeaderboardEntry entry;

        // Read the player_name
        std::getline(fhand, entry.player_name, ',');

        // Read the score
        fhand >> entry.score;

        // Ignore the newline character
        fhand.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Add the entry to the leaderboard vector
        leaderboard.push_back(entry);
    }
    fhand.close();

}


void Leaderboard::appendDataToFile(const std::string& name, int score) {
    // if the name is empty then were not going to append it to the file
    if (name.empty()) { return; }

    std::string dataToAppend = name + "," + std::to_string(score);

    // open the file in append mode
    std::fstream fhand;
    std::string path = "data/" + filename;
    fhand.open(path, std::ios::app);

    fhand << dataToAppend;
    fhand.close();
    
}

// this will overwrite the contents of the File
// the sorted one will be the one it will contain
void Leaderboard::writeLeaderboardToFile() {

    // open the file in write mode
    std::fstream fhand;
    std::string path = "data/" + filename;
    fhand.open(path, std::ios::out);

    std::string dataToWrite;
    for (const LeaderboardEntry& entry : leaderboard) {
        dataToWrite = entry.player_name + "," + std::to_string(entry.score) + "\n";
        fhand << dataToWrite;
    }
    fhand.close();
}

void Leaderboard::displayLeaderboard() {

     if (isFileExistAndNotEmpty()) {
        readLeaderboardFromFile();
    } else {
        std::cout << "The Leaderboard is empty!\n\n\n";
        system("pause");
        return;
    }

    // sort according to what the game leaderboard needs
    if (filename == "easyLeaderboard.txt") {
        bubbleSort(leaderboard);
    } else if (filename == "mediumLeaderboard.txt") {
        bubbleSort(leaderboard);
    } else if (filename == "hardLeaderboard.txt") {
        insertionSort(leaderboard);
    } else {
        selectionSort(leaderboard);
    }

   /* used for debugging
    std::cout << "Before filetring: " << std::endl;
    std::cout << leaderboard.size() << std::endl;
    for (auto entry : leaderboard) {
        std::cout << entry.player_name << ", ";
        std::cout << entry.score << std::endl;
    }
    */

    // filter
    // Remove duplicates based on player_name, the second occurence will be the one to be deleted
    auto duplicate = std::unique(leaderboard.begin(), leaderboard.end(),
        [](const LeaderboardEntry& a, const LeaderboardEntry& b) {
            return a.player_name == b.player_name;
        });
    leaderboard.erase(duplicate, leaderboard.end());

   /* used for debugging
    std::cout << "After filetring: " << std::endl;
    std::cout << leaderboard.size() << std::endl;
    for (auto entry : leaderboard) {
        std::cout << entry.player_name << ", ";
        std::cout << entry.score << std::endl;
    } */

    writeLeaderboardToFile();

    if (filename == "easyLeaderboard.txt" || filename == "mediumLeaderboard.txt" || filename == "hardLeaderboard.txt") {
        printDifficultyLevels();
    }

    if (filename == "infinite.txt") {
        printInfiteRoulette();
    }

    std::cout << "\n\n";
    system("pause");
}


