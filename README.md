# Ultimate Chess

## Submission Information

Testing is done via unit tests. If the program doesn't blow up upon building and running, the tests pass.

The sample output is done using preset values of:

Maximum number of turns per piece: 400
Number of each type of piece to generate: 80
Length of grid: 60

These can be changed in Test.cpp

## Coursework Information 

### Aims

To practice implementation of an inheritance hierarchy and use of polymorphism in C++ and introduce ideas of collision detection in computer games.

### Specification

An important topic in many computer games is determining when 2 objects collide with one another. Games looks poor if a car appears to drive into a wall or appears to collide with thin air. Physics Engines devote considerable effort to solving this problem. In this project we will start to consider this issue.

Implement an abstract base class `Piece` to represent moving chess pieces in a game. Derive classes `Rook`, `Bishop` and `Queen` in an appropriate inheritance hierarchy from `Piece` with appropriate information to store the positions on a flat, square 2_D surface. The classes should provide methods to move the position of the piece. A `Rook` moves vertically or horizontally across the grid. A `Bishop` moves diagonally (at 45 degrees to the movement of the `Rook`) in any direction. A `Queen` can move either like a `Rook` or a `Bishop` (as in real chess). Distances moved need not be integers.

In this game pieces capture by colliding with another piece during the course of their move. For the purposes of capture, pieces have a 2 dimensional shapes (a circle for `Bishop`s and `Queen` and a Square for `Rook`s). All pieces have a radius of 1 unit or a side length of 2 units in the case of the `Rook`. You will need to provide functions to detect when two pieces overlap whereupon the non-moving piece is removed from the board. You will need to deal with overlap of 2 circles, 2 squares and circle and square separately.

Write a test game program that creates several pieces and stores them in an array or list or other data structure of your choosing. The program should then iterate through the data structure, moving each piece by a small random amount (but keeping them within a grid of a given size) and check to see if there are any captures. Keep a score of the number of captures made by each of the 3 types of piece. If a capture is detected then the non-moving piece should be removed from the data structure and the moving piece should stop at the position where the capture is detected. The game should continue for a given number of moves by each piece (say 100 or whatever you deem appropriate) but should terminate earlier if at most one piece remains.

NO GRAPHICAL OUTPUT is expected or required. You may choose whichever method you want for keeping the shapes within a grid but a piece should always move some distance at each turn. You should output (using operator<< appropriately) information about each capture in the game and present the final scores for each category of piece at the end of the game.

Note that, unlike real chess, there are no squares on the board but simply distances.
