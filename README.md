Author: ketsup@asura

### Code Mine Digger 
Is an exciting variation of the classic Minesweeper game.
Offering a fresh take on the original concept. 
With a range of engaging game modes and challenges.
Are you up for the challenge!

The following is just a short description for the program. 
Please play the game to find out more of its functions.

### Project Folder Tree Structure
``````
Code Mine Digger/
│
│
├── data/ 
│     -> (contain the data for the leaderboard)
│     -> (files are automatically added as the game start to recieve the data from the game) 
│     -> (the data is used by the ranking library to create the leaderboard)
│
├── include/
│   ├── assets.h      (ASCII Designs interface) 
│   └── rankings.h    (Leaderboard && Sorting interface)
│
│
├── src/
│   ├── assets.cpp    (ASCII Designs Implementation)
│   └── helper.cpp    (Leaderboard && Sorting Implementation)
│
│
└── main.cpp (Array Impementation -> through minesweeper game and modes)
``````

### Instructions to Run and Play the Program

Make sure that the Code Mine Digger folder is downloaded before continuing ...

Compiling (this assumes that you have mingw as your c++ compiler):
1. First please open you terminal (cmd, powershell, etc.), 
   And make sure you are at the directory where the program is located, 
   i.e in the Code Mine Digger folder that you downloaded. 
   You can check the directory you are in using the command: pwd
2. To move to a directory you can use the command: cd [programDirectory]
3. Compile the two libraries into object using:
``````
g++ -c src/assets.cpp -I include -o assets.o
g++ -c src/rankings.cpp -I include -o rankings.o
``````
Building:
4. After turning the two files to object link it together with the main files:  
   (note: you can name the excutable mines with any name you want)      
``````
g++ main.cpp assets.o rankings.o -I include -o mines
``````
Run and play the game:
5. The run the executable using: (or if you change the name of the excutable please use that)   
If you are using powershell:  
``````
./mines
``````
If you are using command prompt:
``````
mines
``````

If you don't have MINGW installed please refer to this link to download...
``````
https://sourceforge.net/projects/mingw/
``````

### How to Play Minesweeper

1. Objective: The goal of Minesweeper is to clear the board without detonating any mines.
2. Game Board: You are presented with a grid of cells. Some cells contain mines, and others are safe.
3. Game Rules:  
       - First move is safe.  
       - Click a cell to reveal its content.  
       - If a mine is revealed, you lose the game.  
       - If a number is revealed, it indicates the number of adjacent mines.  
       - Use the numbers to deduce the locations of mines.  
       - Put a flag in a cell that is a potential mine.  

4. Winning: You win when all safe cells are uncovered and all mines are correctly flagged.  
5. Losing: You lose if you click on a mine.  
7. Flagging: You can put a flag at a cell with potential mine, 
             when a cell is flag the player cannot dig/reveal the cell,
             it need to be unflage first.
8. Enjoy the Game!: Play and have fun in playing the modes in this game!


### Game modes (short description for the game modes)
1. Difficulty Levels mode  
       - The board size and number of mines will be determined based on the players.  
       - chosen difficulty (easy, medium, and hard).  
2. Custom mode  
       - The board size and the number of mines is determined by the players.  
       - The minimum board size is: rows = 3 and columns = 3.  
       - The number of mines should be less than the board size.  
3. Infinite Roulette mode  
       - The board size and the number of mines is random.  
       - The player will continue playing until he/she quits or lose the game.  
       
### Leaderboard
1. Difficulty Levels mode  
       - The player's rank is based on the time it took the player's chosen difficulty is completed(win the game).  
       - The shorter the time the higher the rank.  
2. Infinite Roulette mode  
       - The player's rank is based on how many win streak the player's did.  
       - The more winning streak the higher the rank.  

If you encounter any unprecented behaviour in the program please feel free notify.  
- To suggest a new feature or report a bug, please [create an issue](https://github.com/ketsupAsura/Code-Mine-Digger/issues).
- If you'd like to contribute code, you can also [submit a pull request](https://github.com/ketsupAsura/Code-Mine-Digger/pulls).

By the way I'm just a begginner in programming, and i'm sure there is still alot to improve in this program.
Thanks you for checking the game, I hope you have fun playing!
