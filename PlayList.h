// Write your name and date here
#pragma once
#include "Song.h"

// Definition of the PlayListNode class - *do not change*
class PlayListNode {
public:
	Song song; //data representing a song
	PlayListNode* next; //pointer to next node in list

	// Constructors

	// PARAM: sng = song data, nxt = pointer to next node
	// POST: Sets song to sng and next to nxt
	PlayListNode(Song sng, PlayListNode* nxt) : song(sng), next(nxt) {}

	// PARAM: sng = song data
	// POST: Sets song to sng and next to nullptr
	PlayListNode(Song sng) : song(sng), next(nullptr) {}

};

// Complete class definition here
// Class should implement a linked list of nodes
// See assignment description for detailed requirements
class PlayList
{
public:
	// Constructors and destructor
	// POST: head of list is set to nullptr
	PlayList();

	// PARAM: pl - PlayList to be copied
	// POST: new PlayList is created that is a deep copy of pl
	PlayList(const PlayList& pl);
	
	// POST: dynamic memory associated with object is deallocated
	~PlayList();

	// PARAM: pl - PlayList to be copied
	// POST: dynamic memory of calling object deallocated (except
	//       under self-assignment), calling object is set to a
	//       a deep copy of pl
	PlayList& operator=(const PlayList & pl);

	// Mutators
	// PRE: 0 <= i <= length of list
	// PARAM: pos - 0-based insertion position
	//        sng - Song to be insertedpos
	void insert(Song sng, unsigned int pos);

	// PRE: 0 <= pos <= length of list-1
	// PARAM: pos - 0-based position of element to be removed and returned
	// POST: Song at position pos is removed and returned
	Song remove(unsigned int pos);

	// PRE: 0 <= pos1, pos2 <= length of list-1
	// PARAM: pos1, pos2 - 0-based positions of elements to be swapped
	// POST: Songs at positions pos1 and pos2 are swapped
	void swap(unsigned int pos1, unsigned int pos2);

	// Accessor
	// PRE: 0 <= pos <= length of list-1
	// PARAM: pos - 0-based position of element to be removed and returned
	// POST: returns the Song at position pos
	Song get(unsigned int pos) const;

	// POST: returns the number of songs in the PlayList
	unsigned int size() const;

private:
	// TO DO
	PlayListNode* head;   // Pointer to the head of the list
    unsigned int playListSize;
};

