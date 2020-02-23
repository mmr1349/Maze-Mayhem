/////////////////////////////////////////////////////////////////////////////////////////
//Programmer:	John Marcus Richmond
//Instructor:	Professor Streller
//Course:		CS 132
//Date:			4/29/19
//Class Name:	Maze
//Class File:	Maze.h
//Data Elements:
//				
//Structure:	Has a two dimensional array of chars that represents our maze. Can input
//				a maze from a speical text file into the array. Uses a two dimensional array
//				of bools to store what positions have been visited. And finally a STL 
//				stack to store the positions we are moving to. Then has a bunch of helper
//				functions to output the maze, check the STL stack, check the visited array etc.
//Purpose:		Class that is used to store and traverse a maze using any path finding
//				algorithm that utilizes a stack. In this class we use the STL stack.
//Other Classes Used:	position, iostream, stack
//Data Members:	stack<Position> positionStack Stack that holds all the positions we use
//				char mazeArray[SIZE + 2][SIZE + 2] Array that holds the maze we input from 
//				a text file
//				bool visitedPositions[SIZE + 2][SIZE + 2] Array that matches the mazeArray 
//				and stores wether that position has been visited or not
//				const int SIZE The size of the maze.
//Member Functions:	maze(); //Default constructor
//					friend istream& operator >> (istream& input, maze& right) Overload for 
//					stream extraction operator extracts characters to put in the mazeArray
//					friend ostream& operator << (ostream& output, const maze& right) Overload 
//					for stream insertion operator outputs the maze with the nice looking walls
//					bool checkIfFree(Position) Checks the given position to see if it is the 
//					same as the exit if so we have freed ourselves from the maze
//					bool checkIfVisited(Position) Checks the visitedPositions array to see if
//					the given position has been visited.
//					void addToVisited(Position) Adds the given position to the visited array
//					void push(Position) Push poistion onto the stack
//					Position pop() Pop off and returns the top of the stack
//					Position peek() Peek at the top of the stack without removing it
//					bool emptyStack() Returns wether the stack is empty or not
//					void outputMazeWithPath(stack<Position>) Outputs the maze along with 
//					the path gotten from the stack
//					stack<Position> getPositionStack() Gets the position stack and 
//					returns a copy of it
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef _MAZE_H
#define _MAZE_H
#include "position.h"
#include <iostream>
#include <stack>

const int SIZE = 10; //const int to store the size of the maze

using namespace std; //have to use std for cin and what not

class maze {
public:
	maze(); //Default constructor
	~maze(); //Destructor for the class
	friend istream& operator >> (istream& input, maze& right); //Overload for stream extraction operator
	friend ostream& operator << (ostream& output, const maze& right); //Overload for stream insertion operator
	bool checkIfFree(Position); //Checks the given position to see if we have freed ourselves from the maze
	bool checkIfVisited(Position); //Checks the given position to see if it has been visited
	bool canMoveHere(Position); //Checks the given position tells whether its wall or not
	void addToVisited(Position); //Adds the given position to the visited array
	void push(Position); //Push onto the stack
	Position pop(); //Pop off the top of the stack
	Position peek(); //Peek at the top of the stack
	bool emptyStack(); //Returns wether the stack is empty or not
	void outputMazeWithPath(stack<Position>); //Outputs the maze along with the path
	stack<Position> getPositionStack(); //Gets the position stack and returns a copy of it
private:
	stack<Position> positionStack; //Stack that holds all the positions we use
	char mazeArray[SIZE+2][SIZE+2]; //Array that holds the maze we input from a text file
	bool visitedPositions[SIZE+2][SIZE+2]; //Array that matches the mazeArray and stores wether 
										   //that position has been visited or not
};



#endif
