/////////////////////////////////////////////////////////////////////////////////////////
//Programmer:	John Marcus Richmond
//Instructor:	Professor Streller
//Course:		CS132
//Date:			4/29/19
//Program Name:	Project 3 Driver
//Program File:	CS132_P3_Driver.cpp
//Input Files:	A specially formatted text file containing a maze 1 means maze wall, 0
//				means empty space, and E means exit.
//Output Files:	None
//Modules Used: fstream, iostream, fstream, Maze.h
//Purpose:		Inputs a specially formatted maze text file then asks the user to enter
//				the starting position of the pathfinding algorithm then attempts to
//				pathfind through it using the depth first search. It will either show a
//				path or tell you its trapped. Then it allows you to do it again solving
//				another maze.
/////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include "Maze.h"

using namespace std;


/////////////////////////////////////////////////////////////////////////////////////////
//Function Name:	main()
//Purpose:			The driver of the program. Utilizes the maze class to traverse a
//					maze we opened from a specially formatted text file. Uses a depth
//					first search to traverse the maze.
//Parameters:		None
//Return Value:		int
//Non-Local Variables Used:	None
//Functions Called:	istream.open(), maze.canMoveHere(), maze.push(), maze.CheckIfFree()
//					maze.emptyStack(), maze.addToVisited(), maze.checkIfVisited(),
//					maze.pop(), istream.close()
/////////////////////////////////////////////////////////////////////////////////////////
int main() {
	//Variable Declerations
	//maze _maze; //The maze we are traversing
	ifstream input; //input stream we want to extract from
	char pathToMaze[100] = " "; //C-string that holds the path to the text file holding
	
	//While the user has not entered a q keep looping over opening and finding paths 
	//through mazes
	while (strcmp(pathToMaze, "q")) {
		Position currentPosition; //The current position we are looking at.
		//Prompt the user toenter the path to the maze or 
		cout << "Enter the path to the maze enter q to quit: ";
		cin >> pathToMaze; //Input the path to the maze
		input.open(pathToMaze); //Try to open the file with the path given

		if (input) { //If the input file is opened and valid
			maze _maze; //the maze we are traversing.
			input >> _maze; //Input the maze into our _maze object from the input stream
			cout << endl << endl; //endl for formatting output
			cout << "Maze is: \n" << _maze; //Output the maze
			
			do {
				int x, y; //ints to store the starting position of the maze search
				//Prompt the user to choose a position to start the maze search
				cout << "Enter where you would like to start the maze pathfinding row then column 1-10: ";
				cin >> x >> y; //Input the coordinates of the starting position
				if (x > 0 && x <= 10) { //If x is inside our rows
					if (y > 0 && y <= 10) { //If y is inside out columns
						currentPosition.SetPos(x, y); //Set the current positions position to those values
					}
				}
				cin.clear(); //Clear the input stream
				cin.ignore(200, '\n'); //Ignore the next 200 characters or until you find a new line
				x = 0; //Reset the x coordinate so that when we loop back over it won't have a value to protect from invalid input
				y = 0; //Reset the y coordinate so that when we loop back over it won't have a value to protect from invalid input
			} while (!_maze.canMoveHere(currentPosition)); //While we can't move to this location keep
														   //prompting the user to enter coordinates.

			_maze.push(currentPosition); //Push the current position onto the _maze stack

			//While we are not free from the maze and not trapped keep looking for a way out
			while (!_maze.checkIfFree(_maze.peek()) && !_maze.emptyStack()) {
				currentPosition = _maze.pop(); //Make the current position the top of the STL stack
				_maze.addToVisited(currentPosition); //Add that position to visited
				_maze.push(currentPosition); //Push back on
				Position temp; //Temp position used to check all the adjacent locations in the maze
				//Set the temp position to one row greater than the current position
				temp.SetPos(currentPosition.getXPos() + 1, currentPosition.getYPos());
				//If we can move there and its not visisted
				if (_maze.canMoveHere(temp) && !_maze.checkIfVisited(temp)) {
					_maze.push(temp); //push it onto the _maze STL stack
				}
				//Set the temp position to one column greater than the current position
				temp.SetPos(currentPosition.getXPos(), currentPosition.getYPos() + 1);
				//If we can move there and its not visisted
				if (_maze.canMoveHere(temp) && !_maze.checkIfVisited(temp)) {
					_maze.push(temp); //push it onto the _maze STL stack
				}
				//Set the temp position to one row less than the current position
				temp.SetPos(currentPosition.getXPos() - 1, currentPosition.getYPos());
				//If we can move there and its not visisted
				if (_maze.canMoveHere(temp) && !_maze.checkIfVisited(temp)) {
					_maze.push(temp); //push it onto the _maze STL stack
				}
				//Set the temp position to one column less than the current position
				temp.SetPos(currentPosition.getXPos(), currentPosition.getYPos() - 1);
				//If we can move there and its not visisted
				if (_maze.canMoveHere(temp) && !_maze.checkIfVisited(temp)) {
					_maze.push(temp); //push it onto the _maze STL stack
				}

				//If we don't have an empty stack and the top is visited
				while (!_maze.emptyStack() && _maze.checkIfVisited(_maze.peek())) {
					_maze.pop(); //Pop the top of the _maze STL stack
				}

				//If the _maze STL stack is empty tell the user we are stuck
				if (_maze.emptyStack()) {
					//Tell the user we are stuck
					cout << "Help we are trapped :(\n";
				} else if (_maze.checkIfFree(_maze.peek())) { //Else check if we are free from the maze
					cout << "I AM FREE!!\n\n"; //Tell the user we are free
					_maze.outputMazeWithPath(_maze.getPositionStack()); //Output the maze with the path
				}
			}
		}
		input.close(); //Close the input stream
	}
	
	cout << "Quiting the program\n\n"; //Inform the user that the program is quitting
	return 0;
}