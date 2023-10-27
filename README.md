*** Feature Update
1. The first move of the player will be always safe
2. A new mode (Random mode) which is still in progress, need to add the continues gameplay 
3. Combined the putting and removing of flag in one option 
4. Leaderboard for Difficulty Level Mode

*** Bug Fixed
1. fixed the game timer (HH:MM:SS)

*** To Compile 
Put the following commands in your terminal
1. First make sure you are at the right directory where the game is located i.e in the minesweeper folder that you downloaded 
you can check the directory you are in using the command: pwd
2. To move to a directory you can use the command: cd<space><minesweeper_directory>
3. Compile the two libraries into object using:
       * g++ -c src/assets.cpp -I include -o assets.o
       * g++ -c src/rankings.cpp -I include -o rankings.o
4. After turning the two files to object link it together with the main files:
       * g++ minesweeper.cpp assets.o rankings.o -I include -o mines
5. The run the executable using: 
       * ./mines
       



