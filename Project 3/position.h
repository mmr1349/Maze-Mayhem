/////////////////////////////////////////////////////////////////////////////////////////
//Programmer:	John Marcus Richmond
//Instructor:	Professor Streller
//Course:		CS 132
//Date:			3/7/19
//Class Name:	Position
//Class File:	position.h
//Data Elements:int x stores the x coordinate
//				int y stores the y coordinate
//Structure:	Holds an x and y coordinate of something as an int so only will
//				work if that thing is locked to a grid. Accessing the coordinates
//				is done through getters and there is a setter that set both coordinates.
//Purpose:		Class that can be used to store and track the position of something
//Other Classes Used:	None
//Data Members:	int x the x coordinate
//				int y the y coordinate
//Member Functions:		Position() Default constructor for the Position class
//						~Position() Destructor for the Position class
//						int getXPos() Returns the current x postiion
//						int getYPos()Returns the current y position
//						void SetPos(int newX, int newY) Sets the x and y positions
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef POSITION_H_
#define POSITION_H_

class Position {
public:
	Position(); //Constructor
	~Position(); //Destructor
	int getXPos() const; //Returns the current x position
	int getYPos() const; //Returns the current y position
	void SetPos(int newX, int newY); //Sets the x and y positions
	bool operator == (const Position& right);
private:
	int x, y; //Variables that hold the x and y coordinate of the object.
};

#endif
