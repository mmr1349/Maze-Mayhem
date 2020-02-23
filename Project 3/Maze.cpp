#ifndef _Maze_CPP
#define _MAZE_CPP


#include "Maze.h"


/////////////////////////////////////////////////////////////////////////////////////////
//Function Name:	maze()
//Purpose:			Default constructor for the maze class. makes a border around the
//					maze and sets all the visisted positions to false.
//Parameters:		None
//Return Value:		None
//Data Members Accessed:	visitedPositions[][], mazeArray[][], SIZE
//Data Memebers Modified:	visitedPositions[][], mazeArray[][]
//Non-Local Variables Used:	None
//Functions Called:	None
/////////////////////////////////////////////////////////////////////////////////////////
maze::maze() {
	for (int i = 0; i < SIZE+2; i++) { //Loop over the rows
		for (int j = 0; j < SIZE+2; j++) { //Loop over the columns
			this->visitedPositions[i][j] = false; //Make all the position not visited
			if (i == 0 || j == 0 || i == SIZE+1 || j == SIZE+1) { //If the position is on the edge
				this->mazeArray[i][j] = '1'; //Make that maze position a wall
			} else { //If its not a edge
				this->mazeArray[i][j] = ' '; //Just make it empty space
			}
		}
	}
}


/////////////////////////////////////////////////////////////////////////////////////////
//Function Name:	operator >>()
//Purpose:			Overlaods the stream extraction operator so we can get a maze from
//					a text file easily.
//Parameters:		istream &input   The input stream we are extracting from by reference
//					maze& right    The maze we are putting the data into.
//Return Value:		istream&   Returns the stream once we have removed all the data we 
//					want from it.
//Data Members Accessed:	mazeArray[][], SIZE
//Data Memebers Modified:	mazeArray[][]
//Non-Local Variables Used:	None
//Functions Called:	istream.get(char)
/////////////////////////////////////////////////////////////////////////////////////////
istream& operator >> (istream& input, maze& right) {
	char temp; //Temp char that holds the char we just inputted.

	for (int i = 0; i < SIZE; i++) { //Loop over rows
		for (int j = 0; j < SIZE; j++) { //Loop over columns
			input.get(temp); //Get the char and place it into temp
			right.mazeArray[i + 1][j + 1] = temp; //Set that position plus one to the temp
												  //character
		}
	}
	return input; //return the input stream
}


/////////////////////////////////////////////////////////////////////////////////////////
//Function Name:	operator <<()
//Purpose:			Overlaods the stream insertion operator so we can output the maze to
//					the console.
//Parameters:		ostream &input   The stream we are outputting to.
//					maze& right    The maze we are outputting to the stream.
//Return Value:		ostream&   Returns the stream once we have outputted the maze.
//Data Members Accessed:	mazeArray[][], SIZE
//Data Memebers Modified:	None
//Non-Local Variables Used:	const maze& right
//Functions Called:	None
/////////////////////////////////////////////////////////////////////////////////////////
ostream& operator << (ostream& output, const maze& right) {
	char mazeSquare; //Char that holds the current maze tile character
	for (int i = 0; i < SIZE+2; i++) { //Loop over rows
		for (int j = 0; j < SIZE+2; j++) { //Loop over columns
			mazeSquare = right.mazeArray[i][j]; //Set the mazeSquare to the right 
												//mazeArrays character at this position 
			if (mazeSquare == '1') { //if its the 1 character
				output << (char)178; //Output a wall character
			} else if (mazeSquare == '0') { //If its a 0
				output << ' '; //Output a space
			} else { //Otherwise
				output << mazeSquare; //Just output whatever the character is.
			}
		}
		output << endl;
	}
	return output; //return the output stream
}


/////////////////////////////////////////////////////////////////////////////////////////
//Function Name:	outputWithPath(stack<Position>)
//Purpose:			Outputs the maze along with the path we followed to escape it.
//Parameters:		stack<Position> path STL stack that holds the path we followed.
//Return Value:		void
//Data Members Accessed:	mazeArray[][], SIZE
//Data Memebers Modified:	None
//Non-Local Variables Used:	None
//Functions Called:	stack.top(), stack.pop(), 
/////////////////////////////////////////////////////////////////////////////////////////
void maze::outputMazeWithPath(stack<Position> path) {
	char pathArr[SIZE+2][SIZE+2]; //Two dimensional array that holds all the positions
								  //on the path. We do it this way so it directly
								  //corresponds with the mazeArray.
	while (!path.empty()) { //While the STL stack path isn't empty
		if (this->checkIfVisited(path.top())) { //Check if the top of the stack is visited
			pathArr[path.top().getXPos()][path.top().getYPos()] = '*'; //If so make the
																	   //pathArr character
																	   //at that location
																	   //a '*'
		}
		path.pop(); //Pop off the top of the STL stack
	}

	char mazeSquare;//Char that holds the maze square we are processing.
	for (int i = 0; i < SIZE + 2; i++) { //Loop over the rows of the maze
		for (int j = 0; j < SIZE + 2; j++) { //Loop over the columns of the maze
			mazeSquare = this->mazeArray[i][j]; //mazeSquare equals the mazeArrays char 
												//at our current loop position
			if (pathArr[i][j] != '*') { //If the pathArr at this position doesn't equal '*'
				if (mazeSquare == '1') { //If the mazeSquare is a 1
					cout << (char)178; //Ouput a wall
				} else if (mazeSquare == '0') { //If the mazeSquare is a 
					cout << ' '; //Ouput a space
				} else { //Otherwise
					cout << '*'; //Ouput a * at the exit 
				}
			} else { //Otherwise
				cout << '*'; //output a * to represent the path
			}
		}
		cout << endl;
	}
}


/////////////////////////////////////////////////////////////////////////////////////////
//Function Name:	checkIfFree(Position pos)
//Purpose:			Compares the given position to the E position in the maze array. If
//					the given position is the E position in the maze we are free.
//Parameters:		Position pos  The position we are checking to see if we are free.
//Return Value:		bool true if free, false if not
//Data Members Accessed:	mazeArray[][]
//Data Memebers Modified:	None
//Non-Local Variables Used:	None
//Functions Called:	Position.getXPos(), Position.getYPos() 
/////////////////////////////////////////////////////////////////////////////////////////
bool maze::checkIfFree(Position pos) {
	if (this->mazeArray[pos.getXPos()][pos.getYPos()] == 'E') { //if the position we are
																//at is the exit position
		return true; //Return true because we have escaped and are free.
	} else { //Otherwise
		return false; //Return false because we are still trapped.
	}
}


/////////////////////////////////////////////////////////////////////////////////////////
//Function Name:	checkIfVisited(Position pos)
//Purpose:			Returns true if the given maze position is visited, false if not
//Parameters:		Position pos  The position we are checking to see if visited
//Return Value:		bool true if visited, false if not
//Data Members Accessed:	visitedPositions[][]
//Data Memebers Modified:	None
//Non-Local Variables Used:	None
//Functions Called:	Position.getXPos(), Position.getYPos() 
/////////////////////////////////////////////////////////////////////////////////////////
bool maze::checkIfVisited(Position pos) {
	//Just return the bool at that position.
	return this->visitedPositions[pos.getXPos()][pos.getYPos()];
}


/////////////////////////////////////////////////////////////////////////////////////////
//Function Name:	addToVisited(Position pos)
//Purpose:			Mark the given position as visited
//Parameters:		Position pos  The position we are marking as visisted
//Return Value:		void
//Data Members Accessed:	visitedPositions[][]
//Data Memebers Modified:	visitedPositions[][]
//Non-Local Variables Used:	None
//Functions Called:	Position.getXPos(), Position.getYPos() 
/////////////////////////////////////////////////////////////////////////////////////////
void maze::addToVisited(Position pos) {
		this->visitedPositions[pos.getXPos()][pos.getYPos()] = true;
}


/////////////////////////////////////////////////////////////////////////////////////////
//Function Name:	addToVisited(Position pos)
//Purpose:			Push the given position onto the stack
//Parameters:		Position pos  The position we want to push onto the stack
//Return Value:		void
//Data Members Accessed:	positionStack
//Data Memebers Modified:	positionStack
//Non-Local Variables Used:	None
//Functions Called:	stack.push()
/////////////////////////////////////////////////////////////////////////////////////////
void maze::push(Position pos) {
	this->positionStack.push(pos); //Push the position onto the STL stack
}


/////////////////////////////////////////////////////////////////////////////////////////
//Function Name:	pop()
//Purpose:			Return and pop off the top of the STL stack positionStack
//Parameters:		None
//Return Value:		Position    The position on the top of the stack
//Data Members Accessed:	positionStack
//Data Memebers Modified:	positionStack
//Non-Local Variables Used:	None
//Functions Called:	stack.pop(), stack.top()
/////////////////////////////////////////////////////////////////////////////////////////
Position maze::pop() {
	if (!this->emptyStack()) { //Make sure the stack has values in it
		Position top = this->positionStack.top(); //Create a copy of the top
		this->positionStack.pop(); //Pop the top off
		return top; //Return our copy of the top
	}
}


/////////////////////////////////////////////////////////////////////////////////////////
//Function Name:	peek()
//Purpose:			Return the position at the top of the STL stack without popping it off.
//Parameters:		None
//Return Value:		Position    The position on the top of the stack
//Data Members Accessed:	positionStack
//Data Memebers Modified:	None
//Non-Local Variables Used:	None
//Functions Called:	stack.top()
/////////////////////////////////////////////////////////////////////////////////////////
Position maze::peek() {
	if (!this->emptyStack()) { //Make sure the STL stack has values in it
		return this->positionStack.top(); //Return the top position
	} else { //Otherwise
		Position pos; //Create temporary position
		pos.SetPos(0, 0); //Set it to 0, 0
		return pos; //Return that position which will never be the exit
	}
}


/////////////////////////////////////////////////////////////////////////////////////////
//Function Name:	emptyStack()
//Purpose:			Bool telling wether the stack is empty or not.
//Parameters:		None
//Return Value:		bool  Wether true if empty, false if not
//Data Members Accessed:	positionStack
//Data Memebers Modified:	None
//Non-Local Variables Used:	None
//Functions Called:	stack.empty()
/////////////////////////////////////////////////////////////////////////////////////////
bool maze::emptyStack() {
	return this->positionStack.empty(); //Return the wether it is empty or not.
}


/////////////////////////////////////////////////////////////////////////////////////////
//Function Name:	canMoveHere(Position pos)
//Purpose:			Check the given position in the maze to see wether there is a wall
//					there or not.
//Parameters:		Position pos  The position we are checking to see if we can move there
//Return Value:		bool  Wether true if we can move there, false if we cannot.
//Data Members Accessed:	mazeArray[][]
//Data Memebers Modified:	None
//Non-Local Variables Used:	None
//Functions Called:	Position.getXPos(), Position.getYPos()
/////////////////////////////////////////////////////////////////////////////////////////
bool maze::canMoveHere(Position pos) {
	char mazeTile = this->mazeArray[pos.getXPos()][pos.getYPos()]; //Get the character
																   //at the position
																   //we are checking
	if (mazeTile != '1') //If this position is not a 1
		return true; //Return true we can move here
	else //Otherwise
		return false; //Return false
}


/////////////////////////////////////////////////////////////////////////////////////////
//Function Name:	getPositionStack()
//Purpose:			Return a copy of the position stack.
//Parameters:		None
//Return Value:		STL stack<Position>  The stack containing the path
//Data Members Accessed:	positionStack
//Data Memebers Modified:	None
//Non-Local Variables Used:	None
//Functions Called:	None
/////////////////////////////////////////////////////////////////////////////////////////
stack<Position> maze::getPositionStack() {
	return this->positionStack;
}


/////////////////////////////////////////////////////////////////////////////////////////
//Function Name:	~maze()
//Purpose:			Default destructor for the maze class just emptys the STL stack.
//Parameters:		None
//Return Value:		None
//Data Members Accessed:	positionStack
//Data Memebers Modified:	positionStack
//Non-Local Variables Used:	None
//Functions Called:	stack.empty(), stack.pop()
/////////////////////////////////////////////////////////////////////////////////////////
maze::~maze() {
	while (!this->positionStack.empty()) { //As long as the STL stack is not empty
		this->positionStack.pop(); //Empty the stack
	}
}

#endif