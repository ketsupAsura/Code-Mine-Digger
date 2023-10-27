// ketsup@asura 

#include <iostream>
#include <limits>
#include <ctime>
#include <iomanip>
#include "assets.h"

// globals
int ROWS, COLS; // will store the rows and columns (the size of the board)

// The PLAYER_BOARD will be the board that is printed
// while the HIDDEN_BOARD will be the board that is hidded as it contains the bombs
char** PLAYER_BOARD, **HIDDEN_BOARD;  
int MINES, MOVES;

// allocate memory for the board dynamically
void allocate_memory(char**& board) {
    board = new char* [ROWS];
    for (int i = 0; i < ROWS; i++) {
        board[i] = new char[COLS];
    }
}

// this will free the memory from the boards after the game has ended
void free_memory(char**& board) {
    for (int i = 0; i < ROWS; i++) {
        delete [] board[i];
    }
    delete [] board;
    board = nullptr; // make sure that the pointer does not points anywhere in the memory
}


// put character as the default value of the board
void initializeBoard(char**& board) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = '?';
        }
    }
}

// check if the input is an integer (can be converted to an integer)
int checkInput(std::string &input) {
    // the comments here are just used for debugging

    // std::cout << "Lenght of the string: " << input.length() << std::endl;
    if (input.length() == 0) { return -1; }

    for (int i = 0; i < input.length(); i++) {

        //std::cout << input[i] << " " << std::endl;
        if (!std::isdigit(input[i])) { return -1; }
    }

    // std::cout << "Returned: " << input << std::endl;
    return std::stoi(input);
}


// put mines in the HIDDEN_BOARD in random
void plantMines() {
    srand(time(0));
    while (MINES > 0) {
        int x = rand() % ROWS;
        int y = rand() % COLS;

        if (HIDDEN_BOARD[x][y] == '*') { continue; }
        HIDDEN_BOARD[x][y] = '*';
        MINES--;
    }
}


// check if the position in the array is a valid coord
bool isValid(const int &x, const int &y) {
    return (x >= 0 && x < ROWS && y >= 0 && y < COLS);
}


// check if the cell is a mine
bool isMine(const int &x, const int &y) {
    if (HIDDEN_BOARD[x][y] == '*') { return true; }
    else { return false; }
}


// counts the neighboring mines (the no. of adjacent mines from the cell the user picks)
int countAdjacentMines(const int &x, const int &y) {
    int count = 0;

    if (isValid(x-1, y-1) && isMine(x-1, y-1)) { count++; }
    if (isValid(x-1, y) && isMine(x-1, y)) { count++; }
    if (isValid(x-1, y+1) && isMine(x-1, y+1)) { count++; }
    if (isValid(x, y-1) && isMine(x, y-1)) { count++; }
    if (isValid(x, y+1) && isMine(x, y+1)) { count++; }
    if (isValid(x+1, y-1) && isMine(x+1, y-1)) { count++; }
    if (isValid(x+1, y) && isMine(x+1, y)) { count++; }
    if (isValid(x+1, y+1) && isMine(x+1, y+1)) { count++; }

    return count;
}



// check if a cell is flagged
bool isFlag(const int &x, const int &y) {
    if (PLAYER_BOARD[x][y] == 'F') { 
        return true; 
    }
    return false;
}

// check if the cell is already revealed i.e. the value is not the default '?'
bool AlreadyRevealed(const int &x, const int &y) {
    if (isFlag(x, y)) { return false; }
    if ( PLAYER_BOARD[x][y] != '?') { return true; }
    return false;
}

// reveal the cell ( does recursion if the user cell doesn't contain any neigboring mines)
void revealCell(const int &x, const int &y) {

    // this will ensure that the cell will not be revealed again if it is already revealed
    if (AlreadyRevealed(x, y)) { 
        return; 
    }

    int num_mines = countAdjacentMines(x, y);

    // this works using implicit(automatically) conversion since in ASCII
    // every character has a correponding integer value
    PLAYER_BOARD[x][y] = '0' + num_mines;

    if (PLAYER_BOARD[x][y] == '0') { PLAYER_BOARD[x][y] = ' '; }
    MOVES--;

    // if there is no mines we do recursion to reveal all the neighboring cells
    // here the one that should be check is the PLAYER_BOARD
    // as it is the one whom the value will chage each iteration 
    // and the HIDDEN_BOARD is just a container for the bomb
    // in order to hid the bomb from the user
    if (num_mines == 0) {

        if (isValid(x-1, y-1) && PLAYER_BOARD[x-1][y-1] == '?') { revealCell(x-1, y-1); }
        if (isValid(x-1, y) && PLAYER_BOARD[x-1][y] == '?') { revealCell(x-1, y); }
        if (isValid(x-1, y+1) && PLAYER_BOARD[x-1][y+1] == '?') { revealCell(x-1, y+1); }
        if (isValid(x, y-1) && PLAYER_BOARD[x][y-1] == '?') { revealCell(x, y-1); }
        if (isValid(x, y+1) && PLAYER_BOARD[x][y+1] == '?') { revealCell(x, y+1); }
        if (isValid(x+1, y-1) && PLAYER_BOARD[x+1][y-1] == '?') { revealCell(x+1, y-1); }
        if (isValid(x+1, y) && PLAYER_BOARD[x+1][y] == '?') { revealCell(x+1, y); }
        if (isValid(x+1, y+1) && PLAYER_BOARD[x+1][y+1] == '?') { revealCell(x+1, y+1); }

    }
}

// this is another version of the board which will contains much wider squares to see
// cause i find the space of the previous board crowded and easy to be loss at where the coordinates are
// as when the user puts a large number for the columns and rows there is a lot of square and 
// less space for the tiles to be seen
// though this uses a lots of  for loop
void printBoard(char**& board) {
    
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

/*
// print the board (older version)
// i can still use this if i guess in the normal game though
// it's really small and the characters are almost dikit-dikit na from my what i can see lol
void printBoard(char**& board) {
    for (int i = 0; i < ROWS; i++) {
        std::cout << "| ";
        for (int j = 0; j < COLS; j++) {
            std::cout << board[i][j] << " | ";
        }
        std::cout << std::endl;
    }
}
*/

// the inline there is optional it just say that the function is oneline
inline bool isValidNumMines() { return (ROWS * COLS) > MINES && MINES > 0; }

void printFinalBoard() {

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
            if (HIDDEN_BOARD[i][k] == '*') {
                std::cout << "  " << HIDDEN_BOARD[i][k] << "  |";
            }
            else {
                std::cout << "  " << PLAYER_BOARD[i][k] << "  |";
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

// this will get and return the  x coordinate (the columns)
int coordinate_x() {
    std::string inputy;
    int y;
    while (true) {
        std::cout << "Enter the cell X-coordinate: ";
        std::getline(std::cin, inputy);

        y = checkInput(inputy);
        if (y != -1 && y >= 0 && y < COLS) { return y; } 

        std::cout << "Invalid X-coordinate!\n" << std::endl;
    }

}

// this will get and return the y coordinate (the rows)
int coordinate_y() {
    std::string inputx;
    int x;
    while (true) {
        std::cout << "Enter the cell Y-coordinate: ";
        std::getline(std::cin, inputx);

        x = checkInput(inputx);
        if (x != -1 && x >= 0 && x < ROWS) { return x; }
        std::cout << "Invalid Y-coordinate!\n" << std::endl;
    
    }

}

int moveOptions() {
    std::string input_MoveOption;
    int moveOptionNumber;


    while (true) {
        // default warning message (needs inside of the loop to be reseted)
        std::string warningMessage = "\nInvalid Input! Please Enter A Single Positive Digit Number\n";

        std::cout << "Move Options " << std::endl;
        std::cout << "[1] Reveal Cell" << std::endl;
        std::cout << "[2] Put A Flag" << std::endl;
        std::cout << "[0] Quit" << std::endl;

        std::cout << "MOVE: ";
        std::getline(std::cin, input_MoveOption);

        moveOptionNumber = checkInput(input_MoveOption);
        if (moveOptionNumber != -1) {
            bool isValid = moveOptionNumber >= 0 && moveOptionNumber <= 2;
            if (isValid) {
                return moveOptionNumber;
            } else {
                warningMessage = "Option doesn't exist!\n";
            }
        }
        std::cout << warningMessage << std::endl;
    }
}

void gameloop() {
    MOVES = ROWS * COLS - MINES;
    std::cout << "TOTAL MOVES: " << MOVES << std::endl;
    
    // memory allocation
    allocate_memory(PLAYER_BOARD);
    allocate_memory(HIDDEN_BOARD);

    // initialize the board
    initializeBoard(HIDDEN_BOARD);
    initializeBoard(PLAYER_BOARD);


    plantMines();

    int x, y;
    while (true) {
        system("cls");

        /*// Uncomment to print the HIDDEN_BOARD where the bombs are
        std::cout << std::endl;
        std::cout << "HIDDEN_BOARD:" << std::endl;
        printBoard(HIDDEN_BOARD);
        std::cout << std::endl;
        */
        
        std::cout << "PLAYER_BOARD:" << std::endl;
        std::cout << "MOVES LEFT: "<< MOVES << std::endl;
        printBoard(PLAYER_BOARD);
        std::cout << "\n";

        int moveNumber = moveOptions();
        bool putFlag = false;

        if (moveNumber == 1) {

            std::string inputx, inputy;
            std::cout << "Reveal Cell At: " << std::endl;
            y = coordinate_x();
            x = coordinate_y();

            revealCell(x, y);
        }
        if (moveNumber == 2) {
            putFlag = true;
            y = coordinate_x();
            x = coordinate_y();
            PLAYER_BOARD[x][y] = 'F';
        } 
            
        if(moveNumber == 0) {
            return;
        }
        

        if(isMine(x, y) && putFlag == false) { 
            system("cls");
            bomb_ascii();
            system("pause");

            std::cout << "\nFINAL_BOARD:" << std::endl;
            printFinalBoard();
            std::cout << "You dig the cell at x -> " << x << " ,Y ->" << y << std::endl;
            std::cout << "You Lose!, you detonated the bomb" << std::endl; 
            std::cout << "\nLegend:" << std::endl;
            std::cout << "'*' -> mines" << std::endl;
            std::cout << "'?' -> unrevealed cell" << std::endl;
            std::cout << "The number's (1-8) -> represents the number of bombs adjacent to that cell" << std::endl;
            system("pause");
            return;
        }

        if (MOVES == 0) {
            system("cls");
            win_ascii();
            system("pause");

            std::cout << "\nFINAL_BOARD:" << std::endl;
            printFinalBoard();
            std::cout << "Eeeey...! You Win! Let's Go!" << std::endl;
            std::cout << "\nLegend:" << std::endl;
            std::cout << "'*' -> mines" << std::endl;
            std::cout << "'?' -> unrevealed cell" << std::endl;
            std::cout << "The number's (1-8) -> represents the number of bombs adjacent to that cell" << std::endl;
            system("pause");
            return;
        }

    }
}

// custom game mode -> ask the user to initialize his/her own row, columns (size of the board) and no. of mines
void customGame() {
    // this variable will be place holder until the user input the correct value
    std::string rows, cols, mines;

    while (true) {
        system("cls");
        std::cout << "PLease Enter The Values of Rows, Columns and Mines For The Custom Game\n\n";
        
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
        std::cout << "PLease Enter The Values of Rows, Columns and Mines For The Custom Game\n\n";
        
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
        std::cout << "PLease Enter The Values of Rows, Columns and Mines For The Custom Game\n\n";
        
        std::cout << "Enter MINES: ";
        std::cin >> mines;

        MINES = checkInput(mines);
        if (MINES != -1 && isValidNumMines()) {
            break;
        } 
       
        std::cout << "\nInvalid value for mines" << std::endl;
        system("pause");

    }

    // I found out that system("pause") will leave \n in the input streamsize 
    // if the user enters (since user can enter any key on the keyboard to continue)
    // so this next line will make sure that the \n will be ignored 
    // as the next function in these is the gameloop which also
    // takes input using getline because when getline gets a \n 
    // it means that its already end of the line or the input (which will then put the value in the stream to a variable)
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    gameloop();

}

void normalGame() {
    std::string input_difficulty;
    int difficulty;


    while (true) {
        // default warning message
        std::string warningMessage = "\nInvalid Input! Please Enter A Single Positive Digit Number";

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
                    gameloop();
                    free_memory(PLAYER_BOARD);
                    free_memory(HIDDEN_BOARD);
                    proceded = true;
                    break;
                case 2: 
                    ROWS = 7;
                    COLS = 7;
                    MINES = 20;
                    gameloop();
                    free_memory(PLAYER_BOARD);
                    free_memory(HIDDEN_BOARD);
                    proceded = true;
                    break;
                case 3: 
                    ROWS = 9;
                    COLS = 12;
                    MINES = 50;
                    gameloop();
                    free_memory(PLAYER_BOARD);
                    free_memory(HIDDEN_BOARD);
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

// this function just rely some message to the person who will play this game
void text() {
    std::cout << "\nAUTHOR: ketsup@asura\n";
    std::cout << "GMAIL: alagabanmatt@gmail.com\n\n";

    std::cout << "README:\n";
    std::cout << "Welcome To My Minesweeper Game\n";
    std::cout << "Have Fun With This Simple Game That I Made\n";
    std::cout << "This is a bit rush so if you see in any way this code can still be optimized pls. contact me\n";
    std::cout << "There is still a lot to do in this program but it's already functional, enjoy!\n\n";

    std::cout << "Rules:\n";
    std::cout << "All Values inputed should be positive(includes 0) and no spaces\n";
    std::cout << "There are two game modes:\n";
    std::cout << "1. Normal Game -> where the user should pick one of the three difficulties of the game\n";
    std::cout << "2. Custom Game -> where the user will put his/her own size of the board (the rows and columns)\n";
    std::cout << "               and as well as the number of mines he/she wanted to be in the board\n";
    std::cout << "               The Limit for the rows is 3 - 9 inclusive\n";
    std::cout << "               The Limit for the columns is 3 - 20 inclusive\n";
    std::cout << "               The Limit for the no. of mines should be less than the number of cell within the board (rows * columns) > mines\n";
    std::cout << "The Rest of The rules will be on another file (In progress)\n\n"; 

}

// this will be the starting point of the game (main menu of Minesweeper)
void menuPrompt() {
    std::string input_choice;
    int choice;


    while (true) {
        // default warning message (inside the loop cause needed to be reseted)
        std::string warningMessage = "\nInvalid Input! Please Enter A Single Positive Digit Number";
       
        system("cls");

        text();

        bool proceded = false;

        std::cout << "MINESWEEPER MENU: " << std::endl;
        std::cout << "[1] Normal Game" << std::endl;
        std::cout << "[2] Custom Game" << std::endl;
        std::cout << "[0] Exit" << std::endl;
        std::cout << "CHOICE: ";
        std::getline(std::cin, input_choice);

        choice = checkInput(input_choice);
        if (choice != -1) {

            switch (choice) {
                case 1:
                    normalGame();
                    proceded = true;
                    break;
                case 2: 
                    customGame();
                    free_memory(PLAYER_BOARD);
                    free_memory(HIDDEN_BOARD);
                    proceded = true;
                    break;
                case 0: 
                    std::cout << "\nThank You For Checking My Game!!!" << std::endl;
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
    menuPrompt();
    return 0;
}