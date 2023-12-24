// ketsup@asura 
#include <iostream>
#include <limits>
#include <ctime>
#include <iomanip>
#include <chrono>

#include "assets.h"
#include "rankings.h"

// globals
int ROWS, COLS, MINES; // will store the rows and columns (the size of the board)

// will only be used in the infinite roulette game
bool EXITED = false;

// check if the input is an integer (can be converted to an integer)
int checkInput(std::string &input) {
    // the comments here are just used for debugging

    // std::cout << "Lenght of the string: " << input.length() << std::endl;
    if (input.length() == 0 || input.length() > 2) { return -1; }

    for (int i = 0; i < input.length(); i++) {

        //std::cout << input[i] << " " << std::endl;
        if (!std::isdigit(input[i])) { return -1; }
    }

    // std::cout << "Returned: " << input << std::endl;
    return std::stoi(input);
}

// contains the user interface during gameplay
// as well as get the needed input 
class UserInterface {
public:
    int moveOptions();
    int getCoordinateX();
    int getCoordinateY();
    std::string get_playerName();
    void printLeaderboard(const std::string& filename);
    void viewGameModeLeaderboard();
    void difficultyLevelsLeaderboard(const std::string& difficulty, const std::string& name, int time);
    bool onlyLetters(const std::string& playerName);
    void printBoard(char**& board); 
    void printFinalBoard(char**& player_board, char**& hidden_board);
};

// set of options the player can select every move in the game
int UserInterface::moveOptions() {
    std::string input_MoveOption;
    int moveOptionNumber;


    while (true) {
        
        // default warning message (needs inside of the loop to be reseted)
        std::string warningMessage = "Invalid Input! Please Enter A Positive Number...\n\n";

        std::cout << "Move Options " << std::endl;
        std::cout << "[1] Reveal Tile" << std::endl;
        std::cout << "[2] Flag/Unflag A Tile" << std::endl;
        std::cout << "[0] Quit" << std::endl;

        std::cout << "MOVE: ";
        std::getline(std::cin, input_MoveOption);

        moveOptionNumber = checkInput(input_MoveOption);
        if (moveOptionNumber != -1) {
            bool isValid = moveOptionNumber >= 0 && moveOptionNumber <= 2;
            if (isValid) {
                return moveOptionNumber;
            } else {
                warningMessage = "Option doesn't exist!\n\n";
            }
        }
        std::cout << warningMessage;
    }
}

// this will get and return the  x coordinate (the columns)
int UserInterface::getCoordinateX() {
    std::string inputy;
    int y;


    while (true) {
        std::string warningMessage = "Invalid Input! Please Enter A Single Positive Digit Number...\n\n";
        std::cout << "Enter the cell X-coordinate: ";
        std::getline(std::cin, inputy);

        y = checkInput(inputy);
        if (y != -1 && y >= 0 && y < COLS) { return y; } 

        if (y != -1) {
            warningMessage = "Invalid X-coordinate!\n\n";
        } 

        std::cout << warningMessage;
    }

}

// this will get and return the y coordinate (the rows)
int UserInterface::getCoordinateY() {
    std::string inputx;
    int x;


    while (true) {
        // default warning message (needs inside of the loop to be reseted)
        std::string warningMessage = "Invalid Input! Please Enter A Single Positive Digit Number...\n\n";

        std::cout << "Enter the cell Y-coordinate: ";
        std::getline(std::cin, inputx);

        x = checkInput(inputx);
        if (x != -1 && x >= 0 && x < ROWS) { return x; }
        if (x != -1) {
            warningMessage = "Invalid Y-coordinate!\n\n";
        } 

        std::cout << warningMessage;
    
    }

}

void UserInterface::printLeaderboard(const std::string& filename) {
    std::string leaderboard_title;
    system("cls");
 
    if (filename == "easyLeaderboard.txt") { leaderboard_title = "Easy Difficulty Leaderboard"; }
    if (filename == "mediumLeaderboard.txt") { leaderboard_title = "Medium Difficulty Leaderboard"; }
    if (filename == "hardLeaderboard.txt") { leaderboard_title = "Hard Difficulty Leaderboard"; }
    if (filename == "infinite.txt") { leaderboard_title = "Infinite Roulette LeaderBoard"; }

    std::cout <<"\n\t\t\t  " << leaderboard_title << "\n\n";

    Leaderboard leaderboard = Leaderboard(filename);
    leaderboard.displayLeaderboard();
}

// will display the leaderboard and write the sorted leaderboard to the database file
// according to what game mode leaderboard the player wants to see
void UserInterface::viewGameModeLeaderboard() {
    std::string input_choice;
    int choice;
    std::string filename;

    while (true) {
        system("cls");
        bool proceded = false;
        // default warning message
        std::string warningMessage = "Invalid Input! Please Enter A Positive Number...\n\n";

        std::cout << "Leaderboards: \n";
        std::cout << "[1] Easy Leaderboard\n";
        std::cout << "[2] Meduim Leaderboard\n";
        std::cout << "[3] Hard Leaderboard\n";
        std::cout << "[4] Infinite Roulette Leaderboard\n";
        std::cout << "[0] Back\n";
        std::cout << "CHOICE: ";
        std::getline(std::cin, input_choice);

        choice = checkInput(input_choice);
        if (choice != -1) {
            switch (choice) {
                case 1: 
                    printLeaderboard("easyLeaderboard.txt");
                    proceded = true;
                    break;
                case 2: 
                    printLeaderboard("mediumLeaderboard.txt");
                    proceded = true;
                    break;
                case 3: 
                    printLeaderboard("hardLeaderboard.txt");
                    proceded = true;
                    break;
                case 4:
                    printLeaderboard("infinite.txt");
                    proceded = true;
                    break;
                case 0: return;
                default: warningMessage = "\nOption doesn't exist";
            }
        }

        if (!proceded) {
            std::cout << warningMessage << std::endl;
            system("pause");
        }
    }
}

// will append the name and score of the player in the leaderboard database
void UserInterface::difficultyLevelsLeaderboard(const std::string& difficulty, const std::string& name, int time) {
    std::string filename;

    if (difficulty.empty()) { return; }

    // put the player data in the correct leaderboard
    if (difficulty == "easy") { filename = "easyLeaderboard.txt"; }
    else if (difficulty == "medium") { filename = "mediumLeaderboard.txt"; }
    else if (difficulty == "hard") { filename = "hardLeaderboard.txt"; }
    else { return; } // if the mode is not difficulty level mode

    Leaderboard leaderboard = Leaderboard(filename);
    leaderboard.appendDataToFile(name, time);
}


bool UserInterface::onlyLetters(const std::string& playerName) {

    for (char letter : playerName) {
        // allow  only letters and spaces
        if (!std::isalpha(letter) && !std::isspace(letter)) { return false; }
    }
    return true;
}

// will get the players name
std::string UserInterface::get_playerName() {
    std::string playerName;

    while (true) {
        std::cout << "\nEnter your name: ";
        std::getline(std::cin, playerName);

        // player name cannot be empty
        if (playerName.empty()) {
            std::cout << "Name should not be empty!\n";
            continue;
        }

        // first character of the name should not be a space
        if (std::isspace(playerName[0])) { 
            std::cout << "Name cannot start with spaces!\n";
            continue;
        }

        // limit the name
        if (playerName.length() > 10) {
            std::cout  << "Name should be less than 10 characters!\n";
            continue;
        }
         
        // should only contains letter
        if (!onlyLetters(playerName)) {
            std::cout << "Name should only contains letters and spaces!\n";
            continue;
        }

        
        break;
    }

    return playerName;
}

// this is another version of the board which will contains much wider squares to see
// cause i find the space of the previous board crowded and easy to be loss at where the coordinates are
// as when the user puts a large number for the columns and rows there is a lot of square and 
// less space for the tiles to be seen
// though this uses a lots of  for loop
void UserInterface::printBoard(char**& board) {
    
    // this will print the coordinate of x
    std::cout << "\t   ";
    for (int i = 0; i < COLS; i++) {
        // this std::left and std::setw are way in c++ to formatt ouput
        // needed to put the x coordinate properly
        std::cout << std::left << std::setw(6) << i;
    }
    std::cout << "-> X" << std::endl;
    
    // will print the top part of the board
    std::cout << std::right << std::setw(8) << "Y ";
    for (int i = 0; i < COLS; i++) {
        std::cout << " _____";
    }
    std::cout << std::endl;

    for (int i = 0; i < ROWS; i++) {
        std::cout << "\t|";
        for (int j = 0; j < COLS; j++) {
            std::cout << "     |";
        }
        std::cout << std::endl;

        std::cout << "      " << i << " |";
        for (int k = 0; k < COLS; k++) {
            std::cout << "  " << board[i][k] << "  |";
        }
        std::cout << std::endl;

        std::cout << "\t|";
        for (int z = 0; z < COLS; z++) {
            std::cout << "_____|";  
        }
        std::cout << std::endl;
    }
    
}


void UserInterface::printFinalBoard(char**& player_board, char**& hidden_board) {

    // this will print the coordinate of x
    std::cout << "\t   ";
    for (int i = 0; i < COLS; i++) {
        // this std::left and std::setw are way in c++ to formatt ouput
        // needed to put the x coordinate properly
        std::cout << std::left << std::setw(6) << i;
    }
    std::cout << "-> X" << std::endl;

    std::cout << std::right << std::setw(8) << "Y ";
    for (int i = 0; i < COLS; i++) {
        std::cout << " _____";
    }
    std::cout << std::endl;

    for (int i = 0; i < ROWS; i++) {
        std::cout << "\t|";
        for (int j = 0; j < COLS; j++) {
            std::cout << "     |";
        }
        std::cout << std::endl;

        std::cout << "      " << i << " |";
        for (int k = 0; k < COLS; k++) {
            if (hidden_board[i][k] == '*') {
                std::cout << "  " << hidden_board[i][k] << "  |";
            }
            else {
                std::cout << "  " << player_board[i][k] << "  |";
            }
        }
        std::cout << std::endl;

        std::cout << "\t|";
        for (int z = 0; z < COLS; z++) {
            std::cout << "_____|";  
        }
        std::cout << std::endl;
    }

}

// handles the gameloop and memory management(allocation/deallocation)
class Minesweeper {
private:
    // The player_board will be the board that is printed
    // while the hidden_board will be the board that is hidded as it contains the bombs
    char** player_board, **hidden_board;  
    int moves;
    UserInterface &ui;
public:
    Minesweeper(UserInterface ui_);
    void allocate_memory(char**& board);
    void free_memory(char**& board);
    void initializeBoard(char**& board);
    void plantMines(const int &playerMove_x, const int &playerMove_y);
    bool isValidCoord(const int &x, const int &y);
    bool isMine(const int &x, const int &y);
    inline bool isValidNumMines();
    int countAdjacentMines(const int &x, const int &y);
    bool isFlag(const int &x, const int &y);
    bool alreadyRevealed(const int &x, const int &y);
    bool canBeRevealed(const int &x, const int &y);
    void revealCell(const int &x, const int &y);
    void gameloop(const std::string& gameMode, std::string playerName);
};


Minesweeper::Minesweeper(UserInterface ui_)
: ui(ui_) {}

// allocate memory for the board dynamically (during runtime)
void Minesweeper::allocate_memory(char**& board) {
    board = new char* [ROWS];
    for (int i = 0; i < ROWS; i++) {
        board[i] = new char[COLS];
    }
}

// this will free the memory from the boards after the game has ended
void Minesweeper::free_memory(char**& board) {
    for (int i = 0; i < ROWS; i++) {
        delete [] board[i];
    }
    delete [] board;
    board = nullptr; // make sure that the pointer does not points anywhere in the memory
}


// put the ? character as the default value of the board
void Minesweeper::initializeBoard(char**& board) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = '?';
        }
    }
}



// put mines in the hidden_board in random
void Minesweeper::plantMines(const int &playerMove_x, const int &playerMove_y) {
    std::srand(std::time(0));
    while (MINES > 0) {
        int x = std::rand() % ROWS;
        int y = std::rand() % COLS;

        // if the cell is the player's first move don't plant a mine
        if (x == playerMove_x && y == playerMove_y) { continue; }

        // if the cell already has a bomb then put the bomb in another cell
        if (hidden_board[x][y] == '*') { continue; }
        hidden_board[x][y] = '*';
        MINES--;
    }
}


// check if the position in the array is a valid coord
bool Minesweeper::isValidCoord(const int &x, const int &y) {
    return (x >= 0 && x < ROWS && y >= 0 && y < COLS);
}


// check if the cell is a mine
bool Minesweeper::isMine(const int &x, const int &y) {
    if (hidden_board[x][y] == '*') { return true; }
    else { return false; }
}

// the inline here is optional it just say that the function is oneline
inline bool Minesweeper::isValidNumMines() { return (ROWS * COLS) > MINES && MINES > 0; }

// counts the neighboring mines (the no. of adjacent mines from the cell the user picks)
int Minesweeper::countAdjacentMines(const int &x, const int &y) {
    int count = 0;

    if (isValidCoord(x-1, y-1) && isMine(x-1, y-1)) { count++; }
    if (isValidCoord(x-1, y) && isMine(x-1, y)) { count++; }
    if (isValidCoord(x-1, y+1) && isMine(x-1, y+1)) { count++; }
    if (isValidCoord(x, y-1) && isMine(x, y-1)) { count++; }
    if (isValidCoord(x, y+1) && isMine(x, y+1)) { count++; }
    if (isValidCoord(x+1, y-1) && isMine(x+1, y-1)) { count++; }
    if (isValidCoord(x+1, y) && isMine(x+1, y)) { count++; }
    if (isValidCoord(x+1, y+1) && isMine(x+1, y+1)) { count++; }

    return count;
}



// check if a cell is flagged
bool Minesweeper::isFlag(const int &x, const int &y) {
    if (player_board[x][y] == 'F') { 
        return true; 
    }
    return false;
}

// check if the cell is already revealed i.e. the value is not the default '?'
bool Minesweeper::alreadyRevealed(const int &x, const int &y) {

    // by the way it took me too long to find how to put this feature (whatever it's fun finding a way)...
    // during recursion we need to change the flag to an unrevealed tile
    // because if in any case the the user inputs a tile which doens't Have
    // any adjacent bombs then the revealCell will do a recursion 
    // and even if it is flagged the cell or the tile should be revelead
    // in short the system can as long as the tile is not a bomb will change the value of the tile
    // but if the user try to open a flagged tile that should not be possible
    
    if (player_board[x][y] == 'F') {
        player_board[x][y] = '?';
    }
    if ( player_board[x][y] != '?') { return true; }
    return false; 
}

bool Minesweeper::canBeRevealed(const int &x, const int &y) {
    if (isFlag(x, y) || player_board[x][y] == '?') {
        return true;
    }
    return false;
}

// reveal the cell ( does recursion if the user cell doesn't contain any neigboring mines)
void Minesweeper::revealCell(const int &x, const int &y) {

    // this will ensure that the cell will not be revealed again if it is already revealed
    if (alreadyRevealed(x, y)) { 
        return; 
    }

    int num_mines = countAdjacentMines(x, y);

    // this works using implicit(automatically) conversion since in ASCII
    // every character has a correponding integer value
    player_board[x][y] = '0' + num_mines;

    if (player_board[x][y] == '0') { player_board[x][y] = ' '; }
    moves--;

    // if there is no mines we do recursion to reveal all the neighboring cells
    // here the one that should be check is the player_board
    // as it is the one whom the value will chage each iteration 
    // and the hidden_board is just a container for the bomb
    // in order to hid the bomb from the user
    if (num_mines == 0) {

        if (isValidCoord(x-1, y-1) && canBeRevealed(x-1, y-1)) { revealCell(x-1, y-1); }
        if (isValidCoord(x-1, y) && canBeRevealed(x-1, y)) { revealCell(x-1, y); }
        if (isValidCoord(x-1, y+1) && canBeRevealed(x-1, y+1)) { revealCell(x-1, y+1); }
        if (isValidCoord(x, y-1) && canBeRevealed(x, y-1)) { revealCell(x, y-1); }
        if (isValidCoord(x, y+1) && canBeRevealed(x, y+1)) { revealCell(x, y+1); }
        if (isValidCoord(x+1, y-1) && canBeRevealed(x+1, y-1)) { revealCell(x+1, y-1); }
        if (isValidCoord(x+1, y) && canBeRevealed(x+1, y)) { revealCell(x+1, y); }
        if (isValidCoord(x+1, y+1) && canBeRevealed(x+1, y+1)) { revealCell(x+1, y+1); }

    }
}



// take the move of the player, updates and renders the board
// the behaviour will based on the user's selected gamemode
void Minesweeper::gameloop(const std::string& gameMode = "", std::string playerName = "") {

    // this will check if the player's move is its first move
    bool playerFirstMove = true;

    moves = ROWS * COLS - MINES;
    
    // memory allocation
    allocate_memory(player_board);
    allocate_memory(hidden_board);

    // initialize the board
    initializeBoard(hidden_board);
    initializeBoard(player_board);

    // get the player name before starting the game
    // if there is no playerName provided 
    // don't get player name for custom_game
    if (playerName.empty() && gameMode != "custom_game") {
        playerName = ui.get_playerName();
    }

    int x, y;
    // starts the game timer
    auto start_time = std::chrono::high_resolution_clock::now();
    while (true) {
        system("cls");

        /*// Uncomment to print the hidden_board where the bombs are
        std::cout << std::endl;
        std::cout << "hidden_board:" << std::endl;
        ui.printBoard(hidden_board);
        std::cout << std::endl;
        */
         
        
        //std::cout << "player_board:" << std::endl;
        ui.printBoard(player_board);
        std::cout << "\n";
        std::cout << "MOVES LEFT: "<< moves << std::endl;

        int moveNumber = ui.moveOptions();
    
        bool Flag = false; // use when flagging and unflagging a tile

        if (moveNumber == 1) {

            std::string inputx, inputy;
            std::cout << "\nReveal cell at: " << std::endl;
            y = ui.getCoordinateX(); // rows
            x = ui.getCoordinateY(); // columns

            if (playerFirstMove) {
                plantMines(x, y);
                playerFirstMove = false;
            }

            if (!isFlag(x, y)) {
                revealCell(x, y);
            } 
            else {
                Flag = true;
                std::cout << "\nUnflag the tile before you can reveal it!\n";
                system("pause");
            }

        }

        // this line of code introduce one options both for putting a flag and unflagging of a tile
        if (moveNumber == 2) {
            Flag = true;

            std::cout << "\nFlag/Unflag At: \n";
            y = ui.getCoordinateX(); 
            x = ui.getCoordinateY();

            if (isFlag(x, y)) {
                player_board[x][y] = '?';
                std::cout << "Unflag At: x -> " << y << ", y -> " << x << "\n";
                system("pause");
            } 
            else if (alreadyRevealed(x, y)) {
                //std::cout << "Flag can only be put in an unrevealed cell!\n";
                std::cout << "\nA cell can only be flag if it is unrevealed!\n";
                system("pause");
            }
            else {
                player_board[x][y] = 'F';
                std::cout << "Flag At: x -> " << y << ", y -> " << x << "\n";
                system("pause");
            }
           
        }

        if(moveNumber == 0) {
             if (gameMode == "infinite_roulette") { EXITED = true; }

            // game ended, free_memory
            free_memory(player_board);
            free_memory(hidden_board);
            return;
        }

        

        if(isMine(x, y) && Flag == false) { 
            if (gameMode == "infinite_roulette") { EXITED = true; }

            system("cls");
            // stops the game timer
            auto end_time = std::chrono::high_resolution_clock::now();

            // get the time it took the player to finish a game of minesweeper in seconds
            auto completionTimeInSeconds = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);

            /* formulas
                * hours
                * in an hour there is 3600 sec (60min * 60sec)
                * divide it by the total seconds and you get the hours
                *
                * minutes
                * the remainder when getting hours from the total time in seconds 
                * gives you the number of seconds left after computing hours
                * divide it by 60 since there is 60 seconds in one minute
                *
                * seconds
                * dividing by 60 gives you what is left in seconds after computing
                * for the hours and minutes;
            */

            int hours = completionTimeInSeconds.count() / 3600;
            int minutes = (completionTimeInSeconds.count() % 3600) / 60;
            int seconds = completionTimeInSeconds.count() % 60;

            std::cout << "Time Played: " << hours << ":" << minutes << ":" << seconds << std::endl; 
            bomb_ascii();
            system("pause");
            system("cls");

            std::cout << "\nFINAL_BOARD:" << std::endl;
            ui.printFinalBoard(player_board, hidden_board);
            std::cout << "You dig the cell at x -> " << y << " ,Y -> " << x << std::endl;
            std::cout << "You Lose!, you detonated the bomb" << std::endl; 
            std::cout << "\nLegend:" << std::endl;
            std::cout << "'*' -> mines" << std::endl;
            std::cout << "'?' -> unrevealed cell" << std::endl;
            std::cout << "'F' -> flag" << std::endl;
            std::cout << "The number's (1-8) -> represents the number of bombs adjacent to that cell/tile" << std::endl;
            system("pause");

            // game ended, free the memory
            free_memory(player_board);
            free_memory(hidden_board);

            return;
        }

        if (moves == 0) {
            if (gameMode == "infinite_roulette") { EXITED = false; }

            system("cls");
            // stops the game timer
            auto end_time = std::chrono::high_resolution_clock::now();

            // get the time it took the player to finish a game of minesweeper in seconds
            auto completionTimeInSeconds = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);

            // convert the chrono time to integer
            int time = static_cast<int>(completionTimeInSeconds.count());

            // record the data of the player in difficulty level mode
            ui.difficultyLevelsLeaderboard(gameMode, playerName, time);

            int hours = completionTimeInSeconds.count() / 3600;
            int minutes = (completionTimeInSeconds.count() % 3600) / 60;
            int seconds = completionTimeInSeconds.count() % 60;

            std::cout << "Time Played: " << hours << ":" << minutes << ":" << seconds << std::endl;
            win_ascii();
            system("pause");
            system("cls");

            std::cout << "\nFINAL_BOARD:" << std::endl;
            ui.printFinalBoard(player_board, hidden_board);
            std::cout << "Eeeey...! You Win! Let's Go!" << std::endl;
            std::cout << "\nLegend:" << std::endl;
            std::cout << "'*' -> mines" << std::endl;
            std::cout << "'?' -> unrevealed cell" << std::endl;
            std::cout << "'F' -> flag" << std::endl;
            std::cout << "The number's (1-8) -> represents the number of bombs adjacent to that cell" << std::endl;
            system("pause");

            
            // game ended, free the memory
            free_memory(player_board);
            free_memory(hidden_board);

            return;
        }

    }
}

// contains the various modes of the game
class GameMode {
private:
    Minesweeper &ms;
public:
    GameMode(Minesweeper ms_);
    void customGame();
    void difficultyLevels();
    void infiniteRoulette(const std::string& gameMode, const std::string& playerName);

};

GameMode::GameMode(Minesweeper ms_)
: ms(ms_) {}

// The Rows and Columns of the board as well as the number of mines 
// will be determined by this functions according to what the user selected game mode
// ------------------------------------- Game Modes ---------------------------------------------

void GameMode::difficultyLevels() {
    std::string input_difficulty;
    int difficulty;


    while (true) {
        // default warning message
        std::string warningMessage = "Invalid Input! Please Enter A Positive Number...\n\n";

        // check if the user proceded to playing
        bool proceded = false;
        
        system("cls"); 
        std::cout << "Pick The Level of Difficulty" << std::endl; 
        std::cout << "[1] Easy" << std::endl;
        std::cout << "[2] Medium" << std::endl;
        std::cout << "[3] Hard" << std::endl;
        std::cout << "[0] Back to Menu" << std::endl;

        std::cout << "CHOICE: ";
        std::getline(std::cin, input_difficulty);

        difficulty = checkInput(input_difficulty);
        if (difficulty != -1) {
            switch (difficulty) {
                case 1:
                    ROWS = 5;
                    COLS = 5;
                    MINES = 10;
                    ms.gameloop("easy");
                    proceded = true;
                    break;
                case 2: 
                    ROWS = 7;
                    COLS = 7;
                    MINES = 17;
                    ms.gameloop("medium");
                    proceded = true;
                    break;
                case 3: 
                    ROWS = 9;
                    COLS = 12;
                    MINES = 50;
                    ms.gameloop("hard");
                    proceded = true;
                    break;
                case 0: 
                    return;
                default: 
                    warningMessage = "\nOption doesn't exist!"; // change the warning message
            }
        }

        if (!proceded) {
            std::cout << warningMessage << std::endl;
            system("pause");
        }
    }

}


// custom game mode -> ask the user to initialize his/her own row, columns (size of the board) and no. of mines
void GameMode::customGame() {

    // this variable will be place holder until the user input the valid data
    std::string rows, cols, mines;

    while (true) {
        system("cls");
        std::cout << "PLease Enter The Values of Rows, Columns and Mines For The Custom Game\n";
        std::cout << "Rows: minimum = 3, maximum = 9\n\n";
        
        std::cout << "Enter ROWS: ";
        std::getline(std::cin, rows);

        ROWS = checkInput(rows);
        if (ROWS != -1 && ROWS >= 3 && ROWS <= 9) {
            break;
        }

        std::cout << "\nInvalid value for rows" << std::endl;
        system("pause");
    }

    while (true) {
        system("cls");
        std::cout << "PLease Enter The Values of Rows, Columns and Mines For The Custom Game\n";
        std::cout << "Rows: minimum = 3, maximum = 9\n";
        std::cout << "Columns: minimum = 3, maximum = 20\n\n";
        
        std::cout << "Enter COLUMNS: ";
        std::getline(std::cin, cols);

        COLS = checkInput(cols);
        if (COLS != -1 && COLS >= 3 && COLS <= 20) {
            break;
        }

        std::cout << "\nInvalid value for columns" << std::endl;
        system("pause");
    }

    while (true) {
        system("cls");
        std::cout << "PLease Enter The Values of Rows, Columns and Mines For The Custom Game\n";
        std::cout << "Rows: minimum = 3, maximum = 9\n";
        std::cout << "Columns: minimum = 3, maximum = 20\n";
        std::cout << "Mines: minimum = 1, maximum = " << ( ROWS * COLS ) - 1 << "\n\n";
        
        std::cout << "Enter MINES: ";
        std::cin >> mines;

        MINES = checkInput(mines);
        if (MINES != -1 && ms.isValidNumMines()) {
            break;
        } 
       
        std::cout << "\nInvalid value for mines" << std::endl;
        system("pause");

    }

    // I found out that system("pause") will leave \n in the input stream 
    // if the user enters (since user can enter any key on the keyboard to continue)
    // so this next line will make sure that the \n will be ignored 
    // as the next function in these is the gameloop which also
    // takes input using getline because when getline gets a \n 
    // it means that its already end of the line or the input (which will then put the value in the stream to a variable)
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    ms.gameloop("custom_game");

}

// this game will continuously give a random board as well as random mines
// to the player to play, this will only end if the player choose to quit the game 
// of if the player losses the game
void GameMode::infiniteRoulette(const std::string& gameMode, const std::string& playerName) {
    // this is so hard to implement ... 

    while (true) {
        srand(time(0));

        // we add 3 here because if it generate zero
        // the the mines would have an equation of rand() % 0 which is an error
        ROWS = (rand() % 9) + 3;
        COLS = (rand() % 20) + 3;
        /*
        std::cout << "rows: " << ROWS << std::endl;
        std::cout << "cols: " << COLS << std::endl;
        system("pause");
        */

        // generates mine atmost half the board size 
        MINES = rand() % ((ROWS * COLS)/2);

        // atleast 3 mines is on the board
        if (MINES < 3) { MINES = 3; }
        if (ROWS >= 3 && COLS >= 3 && ROWS <= 9 && COLS <= 20) { break; }
     }


    ms.gameloop(gameMode, playerName);
}

// ------------------------------------- Game Modes ---------------------------------------------

// contains the menus of the game
class Menu {
private:
    GameMode &gm;
    UserInterface &ui;
public: 
    Menu(GameMode gm_, UserInterface ui_);
    void gameMenu();
    void startMenu();
};

Menu::Menu(GameMode gm_, UserInterface ui_)
: gm(gm_), ui(ui_) {}

void Menu::gameMenu() {
    // this will store the user input until it is valid
    std::string input_choice;

    // this will store the valid input of the user 
    int choice;

    while (true) {
        std::string playerName;

        // this two variables will only be used in infinite_roulette game
        bool play_infiniteRoulette = false;
        int win_streak = 0;

        // notes if the player plays a game
        bool proceded = false;

        // default warning message (inside the loop cause needed to be reseted)
        std::string warningMessage = "Invalid Input! Please Enter A Positive Number...\n\n";
       
        system("cls");

        game_title();

        std::cout << "GAMEPLAY MODES:" << std::endl;
        std::cout << "[1] Difficulty Levels" << std::endl;
        std::cout << "[2] Custom Game" << std::endl;
        std::cout << "[3] Infinite Roulette" << std::endl;
        std::cout << "[0] Back" << std::endl;
        std::cout << "CHOICE: ";
        std::getline(std::cin, input_choice);

        choice = checkInput(input_choice);
        if (choice != -1) {

            switch (choice) {
                case 1:
                    gm.difficultyLevels();
                    proceded = true;
                    break;
                case 2: 
                    gm.customGame();
                    proceded = true;
                    break;
                case 3: 
                    playerName = ui.get_playerName();
                    while (true) {
                        gm.infiniteRoulette("infinite_roulette", playerName);

                        if (EXITED) { 
                            EXITED = false;
                            break;
                        }

                        // add a score if the player only wins
                        win_streak++;
                    }
                    play_infiniteRoulette = true;
                    proceded = true;
                    break;
                case 0: 
                    return; 
                default: warningMessage = "\nOption doesn't exist!"; // change the warning message
            }

        }

        
        if (play_infiniteRoulette) {
            Leaderboard leaderboard = Leaderboard("infinite.txt");
            leaderboard.appendDataToFile(playerName, win_streak);
        }
        if (!proceded) {
            std::cout << warningMessage << std::endl;
            system("pause");
        }
    }
}

// will be the starting menu of the game
void Menu::startMenu() {
    // this will store the user input until it is valid
    std::string input_choice;

    // this will store the valid input of the user 
    int choice;
    
    while (true) {
        bool proceded = false;

        // default warning message (inside the loop cause needed to be reseted)
        std::string warningMessage = "Invalid Input! Please Enter A Positive Number...\n\n";
        system("cls");
        game_title();

        std::cout << "Start Menu: \n";
        std::cout << "[1] Start Game\n";
        std::cout << "[2] LeaderBoards\n";
        std::cout << "[0] Exit\n";
        std::cout << "CHOICE: ";
        std::getline(std::cin, input_choice);

        choice = checkInput(input_choice);
        if (choice != -1) {
            switch (choice) {
                case 1: 
                    proceded = true;
                    gameMenu(); 
                    break; 
                case 2: 
                    proceded = true;
                    ui.viewGameModeLeaderboard(); 
                    break;
                case 0: 
                    std::cout << "\nThank You For Checking The Game!!!" << std::endl;
                    return;
                default: warningMessage = "\nOption doesn't exist!"; // change the warning message
            }
        }

        if (!proceded) {
            std::cout << warningMessage << std::endl;
            system("pause");
        }
        
    }
}

int main() {
    UserInterface ui = UserInterface();
    Minesweeper ms = Minesweeper(ui);
    GameMode gm = GameMode(ms);
    Menu menu = Menu(gm, ui);
    menu.startMenu();
    return 0;
}

