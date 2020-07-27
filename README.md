# Green vs. Red Game

Green vs. Red is a zero-player game played on a 2D grid. In this implementation the grid is limited to 999 cells in width and height. There are two types of cells - green and red. 
Given an initial grid state (called Generation Zero), a cell to be observed as well as the number of generations to observe (*N*), the program calculates the number of generations (including Generation Zero and generation *N*) in which the observed cell was green. Generations *evolve* according to a simple set of rules.

## Usage
1. Game game; # Create an object of class Game
2. game.Initialize(); # Initialize the game - read the width (**x**) and the height (**y**) of the game grid from std::cin, read the initial state of the grid (*y* rows of length **x** that consist of 0s and 1s), read the observed cell coordinates and the number of generations to simulate.
3. game.Play() # Simulate the game up to generation *N* included.
4. game.getTrackedCellGreenTimes() # Returns the number of times (generations) the observed (tracked) cell was green. 
