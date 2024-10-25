#pragma once

#include <string>
using std::string;

class StringList
{
public:
	// Default constructor - makes an empty list of capacity 10
	StringList();
	
	// Copy constructor
	StringList(const StringList& other);

	// ***UNDOABLE
	// Overloaded assignment operator
	StringList& operator=(const StringList& other);

	// Destructor
	~StringList();

	// ACCESSORS
	// POST: Returns the number of elements in the list
	int size() const;

	// POST: Returns true if the list is empty, false otherwise
	bool empty() const;

	// Returns the string at the given index
	// PRE: 0 <= i < size()
	// PARAM: i = index to access
	// POST: Returns the element at index i
	string get(int i) const;

	// Returns the index of the first occurrence of the given string
	// PARAM: str = string to search for
	// POST: Returns the index of the first occurrence of s, or -1 if not found
	int index(string str) const;

	// Returns true iff the given string is in the list
	// PARAM: str = string to search for
	// POST: Returns true iff s is in the list
	bool contains(string str) const;

	// Returns true if the two lists are equal, false otherwise.
	// Does *not* consider any undo information when comparing two Stringlists. All
	// that matters is that they have the same strings in the same order.
	// PARAM: sl = list to compare with calling object
	// POST: Returns true iff calling object and sl are equal
	bool operator==(const StringList& sl) const;

	// Returns true if the two lists are not equal, false otherwise
	// Does *not* consider any undo information when comparing two Stringlists.
	// PARAM: sl = list to compare with calling object
	// POST: Returns true iff calling object and sl are *not* equal
	bool operator!=(const StringList& sl) const;

	// POST: Returns a string representation of the list
	string toString() const;

	// MUTATORS
	 
	// ***UNDOABLE
	// Sets the value at the given index
	// PRE: 0 <= i < size()
	// PARAM: i = index to set value at
	//		  str = value to set
	// POST: Sets list[i] to str
	void set(int i, string str);

	// ***UNDOABLE //done
	// Inserts the given string *before* the string at the given index
	// PRE: 0 <= pos < size()
	// PARAM: pos = index of insertion point
	//		  str = value of inserted string
	// POST: Sets list[pos] to str and moves all other elements up
	void insertBefore(int pos, string str);

	// ***UNDOABLE // done
	// Inserts the given string at the front of the list
	// PARAM: str = value of inserted string
	// POST: Sets list[0] to str and moves all other elements up
	void insertFront(string str);

	// ***UNDOABLE // done
	// Inserts the given string at the back of the list
	// PARAM: str = value of inserted string
	// POST: Sets list[size()] to str
	void insertBack(string str);
	
	// ***UNDOABLE //Done
	// Removes the element at the given index
	// PRE: 0 <= pos < size()
	// PARAM:pos = index of element to remove
	// POST: Removes list[pos] and moves all other elements down
	void remove(int pos);

	// ***UNDOABLE
	// Empties the list
	// POST: Removes all strings from the list without changing capacity
	void removeAll();

	// Undoes the last operation that modified the list
	// POST: Reverts the list to its state before the last operation
	void undo();

	// Prints the list
	// POST: Prints the list to the console
	void print() const;

private:
    int assignoperatorCounter;
    int assignoperatorL2Counter;
    int removeAllCounter;
	int n;
	int capacity;
	string* arr;
    
        // Undo mechanism
    struct UndoAction {
        string operation;
        string value;
        int position;
    };

    class UndoStack {
    public:
        UndoStack();
        ~UndoStack();
        void push(const UndoAction& action);
        UndoAction pop();
        int getTop() const;

    private:
        UndoAction* stack;
        int top;
        int capacity;
    };

    UndoStack undoStack;
	// Helper function for checking index bounds
	// PARAM: i = index to check
	// POST: Throws an out_of_range exception if i is out of bounds
	void checkBounds(int i, string s) const;

	// Helper function to check capacity and double list size if necessary
	// POST: Doubles the capacity of the list if n == capacity
	void checkCapacity();

	// Helper function to copy the contents of another list
	// PARAM: lst = list to copy
	// POST: Makes a deep copy of lst
	void copyList(const StringList& lst);

};

