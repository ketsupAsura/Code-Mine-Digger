// ketsup@asura
#include <iostream>
#include <thread>
#include <chrono>
#include "assets.h"

void bomb_ascii() {

    std::cout << "\n\n";
    std::cout << "\t\t           *          \n";    
    std::cout << "\t\t          /|          \n";
    std::cout << "\t\t         / |          \n";
    std::cout << "\t\t         | |          \n";
    std::cout << "\t\t       *  *  *        \n";
    std::cout << "\t\t    *           *     \n";
    std::cout << "\t\t  *               *   \n";
    std::cout << "\t\t *      BOOM!      *  \n";
    std::cout << "\t\t *    GAME OVER!   *  \n";
    std::cout << "\t\t  *               *   \n";
    std::cout << "\t\t    *           *     \n";
    std::cout << "\t\t       *  *  *        \n";
    std::cout << "\n\n";

}

void win_ascii() {

    std::cout << "\n\n";
    std::cout << "  **    **  *******   **     **     **     **  ******  ***    **   *****  " << std::endl;
    std::cout << "   **  **  **     **  **     **     ** *** **    **    ****   **    ***   " << std::endl;
    std::cout << "    ****   **     **  **     **     **** ****    **    ** **  **     *    " << std::endl;
    std::cout << "     **    **     **  **     **     ***   ***    **    **  ** **          " << std::endl;
    std::cout << "     **     *******    *******      **     **  ******  **   ****     *    " << std::endl;
    std::cout << "\n\n";

}

// please don't touch 
// it gives me a hard time pin pointing where to put the escape characters just to print '\' lol
void game_title() {
    std::cout << "\n\n";
    std::cout << "        ________     ______ ______       ________           \n";
    std::cout << "       |\\   ____\\   |\\   _ \\  _   \\     |\\   ___ \\          \n";
    std::cout << "       \\ \\  \\___|   \\ \\  \\\\ __\\ \\  \\    \\ \\  \\_|\\ \\         \n";
    std::cout << "        \\ \\  \\       \\ \\  \\\\|__| \\  \\    \\ \\  \\ \\\\ \\        \n";
    std::cout << "         \\ \\  \\_____  \\ \\  \\\\   \\ \\  \\    \\ \\  \\_\\\\ \\       \n";
    std::cout << "          \\ \\_______\\  \\ \\__\\\\   \\ \\__\\    \\ \\_______\\      \n";
    std::cout << "           \\|_______|   \\|__|/    \\|__|     \\|_______|      \n";
    std::cout << "\n                     \"CODE MINE DIGGER\"                    \n";
    std::cout << "\n\n";
}

// this feature will unlock after i learn how to work with threads
// this can be useful if the database is large and much more longer to read
// this will ensure that the this animation will end after the program
// reads and process all the data in the file
void loading_animation() {
    // Define a sequence of characters for the loading animation
    const char loadingChars[] = { '|', '\\', '-', '/' };

    // The number of iterations for the loading animation
    const int iterations = 20;

    for (int i = 0; i < iterations; ++i) {
        // Print the current loading character
        std::cout << "Loading " << loadingChars[i % 4] << '\r' << std::flush;

        // Simulate some work (you can replace this with actual work)
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

}
