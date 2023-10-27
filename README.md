Author: ketsup@asura


To play:
1. Compile (assumes that you already have mingw as your c++ compiler)

2. Copy the command on your terminal/console:  g++ minesweeper.cpp assets.cpp assets.h -o mines

3. The run the mines.exe using this command: ./mines

4. That's it enjoy playing the game!!!

Minesweeper is a game where mines are hidden in a grid of squares. 
Safe squares have numbers telling you how many mines touch the square. 
You can use the number clues to solve the game by opening all of the safe squares. 
If you click on a mine you lose the game!

Flagging System:
# Flag can only be put in an unrevealed tile
# If a tile is flagged it cannot be revealed/dig
# To reveal/dig the tile the flag needs to be unflag
# But when revealing a cell the flag will be removed



