// ketsup@asura
// Implementation of the assets.h which is the interface

#include <iostream>
#include "assets.h"

void bomb_ascii() {

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

    std::cout << "  **    **  *******   **     **     **     **  ******  ***    **   *****  " << std::endl;
    std::cout << "   **  **  **     **  **     **     ** *** **    **    ****   **    ***   " << std::endl;
    std::cout << "    ****   **     **  **     **     **** ****    **    ** **  **     *    " << std::endl;
    std::cout << "     **    **     **  **     **     ***   ***    **    **  ** **          " << std::endl;
    std::cout << "     **     *******    *******      **     **  ******  **   ****     *    " << std::endl;
    std::cout << "\n\n";

}
