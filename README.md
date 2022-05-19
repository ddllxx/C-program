# XJCO 1921 Programming Project - Coursework 2- Game of life 

## URL
https://github.com/ddllxx/C-program

## Submission History Screenshot
![Image text]()
![Image text]()
![Image text]()

## Name
Game of life

## Run description
First of all, you need to unzip the downloaded zip package, there are three folders in the whole project (include, resources, src) and a Makefile, you need to put these files in a file directory under Linux and then open a command line window to run it. 
You first need to use the command 'make' or 'make all' to compile the code, where it will generate a grid.txt (an initial 10 rows and 10 columns, run at a rate of 500 milliseconds per generation, run for 10 generations) Of course you can also customize a text file, the first line of the text file is the number of generations to be performed respectively the interval between generations (in milliseconds) the number of rows the number of columns, and then 0 for no cells and 1 for yes cells.
When initializing, the initialization can be achieved in two ways, either by setting the initial state based on reading the file, or by completing the state initialization based on random user input clicks.
The first way of initialization means that you can type '. /game_of_life plus any file name you want', e.g. '. /game_of_life grid.txt'
The second way to initialize means you need to type '. /game_of_life Number of generations to be performed Number of generations (in milliseconds) Number of rows Number of columns', it is recommended that the number of rows and columns be the same, and then it will generate a blank screen that you can initialize by clicking on it at random.
When running,You can press 'n' to make the whole lifeworld evolve in one generation, you can press 's' to stop the evolution of the whole lifeworld, you can press 'r' to automatically start the evolution of the whole lifeworld at a set You can press 'r' to automatically start the evolution of the entire lifeworld at a set rate, and it will automatically pause after a set number of generations and generate an end-state text file with the name 'output_shot'. At any generation you can press 'd' to record the state at that moment, and the program will generate a state text file with the file name 'output_shot'.
In addition, you can also change the life state of that cell at any time by clicking on the grid in the life world, it is recommended to do this in the paused state.
After running, you can use the command 'make clean' to remove all compiled products of the code.

