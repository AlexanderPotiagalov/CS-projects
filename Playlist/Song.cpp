// Song method implementations for CMPT 225 assignment
// Author: John Edgar
// Date: May 2022

#include "Song.h"
#include<stdexcept>

using std::out_of_range;
using std::runtime_error;

// Constructor
Song::Song(string nm, string art, int len) : name(nm), artist(art), length(len)
{
	if (length < 1) {
		throw out_of_range("negative run time");
	}
	if (name == "") {
		throw runtime_error("a song must have a name");
	}
	if (artist == "") {
		throw runtime_error("a song must have an artist");
	}
}

// Accessors
// POST: returns name of song
string Song::getName()
{
	return name;

}

// POST: returns recording artist of song
string Song::getArtist()
{
	return artist;
}

// POST: returns length in seconds of song
int Song::getLength()
{
	return length;
}