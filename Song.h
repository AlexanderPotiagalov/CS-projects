// Song class definition for CMPT 225 assignment
// Author: John Edgar
// Date: May 2022

#pragma once
#include <string>
using std::string;

class Song
{
public:
	// Constructor
	Song(string nm, string art, int len);

	// Accessors
	string getName();
	string getArtist();
	int getLength();

private:
	string name;
	string artist;
	int length;
};

