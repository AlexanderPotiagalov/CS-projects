#include "StringList.h"
#include <stdexcept>
#include <iostream>
using std::out_of_range;
using std::cout;
using std::endl;

// Default constructor - makes an empty list of capacity 10
StringList::StringList()
{
	capacity = 10;
	n = 0;
	arr = new string[capacity];
}

// Copy constructor
StringList::StringList(const StringList& other)
{
	copyList(other);
}

// ***UNDOABLE
// Overloaded assignment operator
StringList& StringList::operator=(const StringList& other)
{
	if(&other != this)
	{
	    assignoperatorCounter = n;
	    assignoperatorL2Counter = other.n; 
        for (int i = n-1; i >= 0; i--) {
            string removedValue = arr[i];
            UndoAction action = {"unoperated", removedValue, i};
            undoStack.push(action);
        }
		delete[] arr;
		copyList(other);
	}
	return *this;
}

// Destructor
StringList::~StringList()
{
	delete[] arr;
}

// ACCESSORS
// Returns the number of elements in the list
int StringList::size() const
{
	return n;
}

// Returns true if the list is empty, false otherwise
bool StringList::empty() const
{
	return n == 0;
}

// Returns the string at the given index
string StringList::get(int i) const
{
	checkBounds(i, "get");
	return arr[i];
}

// Returns the index of the first occurrence of the given string
int StringList::index(string s) const
{
	int i = 0;
	while (i < n && s != arr[i]) {
		i++;
	}
	if (i == n) {
		return -1;
	}
	else {
		return i;
	}
}

// Returns true iff the given string is in the list
bool StringList::contains(string str) const
{
	return !(index(str) == -1);
}

// Returns true if the two lists are equal, false otherwise.
// Does *not* consider any undo information when comparing two Stringlists. All
// that matters is that they have the same strings in the same order.
bool StringList::operator==(const StringList& sl) const
{
	if (size() != sl.size())
	{
		return false;
	}
	for (int i = 0; i < size(); i++)
	{
		if (get(i) != sl.get(i))
		{
			return false;
		}
	}
	return true;
}

// Returns true if the two lists are not equal, false otherwise
bool StringList::operator!=(const StringList& sl) const
{
	return !(*this == sl);
}

// Returns a string representation of the list.
string StringList::toString() const
{
	string result = "{";
	for (int i = 0; i < size(); i++)
	{
		if (i > 0) {
			result += ", ";
		}
		result += "\"" + get(i) + "\"";
	}
	return result + "}";
}


// MUTATORS

// ***UNDOABLE
// Sets the value at the given index
void StringList::set(int i, string str)
{
	checkBounds(i, "set");
	string unsetValue = arr[i];
	UndoAction action = {"unset", unsetValue, i};
    undoStack.push(action);
	arr[i] = str;
}

// ***UNDOABLE
// Inserts the given string *before* the given index
void StringList::insertBefore(int pos, string str)
{
	// Doesn't use checkBounds because it's okay to insert at the end
	if (pos < 0 || pos > size()) {
		throw out_of_range("StringList::insertBefore index out of bounds");
	}
	checkCapacity();
	for (int i = n; i > pos; i--) {
		arr[i] = arr[i-1];
	}
	arr[pos] = str;
	n++;
	UndoAction action = {"remove", str, pos};
    undoStack.push(action);
}

// ***UNDOABLE
// Inserts the given string at the front of the list
void StringList::insertFront(string str)
{
	checkCapacity();
	insertBefore(0, str);
	UndoAction action = {"removefront", str, 0};
	undoStack.push(action);
}

// ***UNDOABLE
// Inserts the given string at the back of the list
void StringList::insertBack(string str)
{
	checkCapacity();
	insertBefore(n, str);
	UndoAction action = {"removeback", str, n-1};
	undoStack.push(action);
}

// ***UNDOABLE
// Removes the element at the given index and moves elements after it down
void StringList::remove(int pos)
{
	checkBounds(pos, "remove");
	string removedValue = arr[pos];
	UndoAction action = {"insert", removedValue, pos};
    undoStack.push(action);
	for (int i = pos; i < n; i++) {
		arr[i] = arr[i + 1];
	}
	n--;
}

// ***UNDOABLE
// Empties the list
void StringList::removeAll()
{
    removeAllCounter = n;
    for (int i = n-1; i >= 0; i--) {
        string removedValue = arr[i];
        arr[i] = " ";
        UndoAction action = {"insertall", removedValue, i};
        undoStack.push(action);
    }
	n = 0;
}

// Undoes the last operation that modified the list
void StringList::undo()
{
	if (undoStack.getTop() == -1) {
        cout << "No operation to undo!" << endl;
        return;
    }
    UndoAction action = undoStack.pop();
    
    // Insert, Insertfront and InsertBack Functions
    if (action.operation == "remove" || action.operation == "removefront" || action.operation == "removeback") {
        remove(action.position);

    // Remove functions
    } else if (action.operation == "insert") {
        insertBefore(action.position, action.value);
        
    // Overloaded Assignment Operator Function 
    } else if (action.operation == "unoperated") {
        for (int i = 0; i < assignoperatorL2Counter; i++) {
            n--;
        }
        for (int i = 0; i < assignoperatorCounter; i++) {
            insertBefore(action.position, action.value);
            action = undoStack.pop();
            if (i < assignoperatorCounter - 1) {
                action = undoStack.pop();
            }
        }
    
    // Set Function 
    } else if (action.operation == "unset"){
        set(action.position, action.value);
        
    // RemoveAll Funciton 
    } else if (action.operation == "insertall") {
        for (int i = 0; i < removeAllCounter; i++) {
            if (action.operation == "insertall") {
                insertBefore(action.position, action.value);
            }
            action = undoStack.pop();
            if (undoStack.getTop() != -1) {
                action = undoStack.pop();
            }
        }
    } 
}

// Prints the list
void StringList::print() const
{
	for (int i = 0; i < n; i++) {
		cout << arr[i] << endl;
	}
}

// Helper function for checking index bounds.
void StringList::checkBounds(int i, string s) const
{
	if (i < 0 || i >= size()) {
		throw out_of_range("StringList::" + s + " index out of bounds");
	}
}

// POST: Doubles the capacity of the list if n == capacity
void StringList::checkCapacity()
{
	if (n == capacity) {
		capacity *= 2;
		string* temp = new string[capacity];
		
		for (int i = 0; i < n; i++) {
			temp[i] = arr[i];
		}
		delete[] arr;
		arr = temp;
	}
}

// Helper function to copy the contents of another list
void StringList::copyList(const StringList& lst)
{
	capacity = lst.capacity;
	n = lst.n;
	arr = new string[capacity];

	for (int i = 0; i < n; i++) {
		arr[i] = lst.arr[i];
	}
}


// UndoStack Implementation (Constructor, Destructor, Push, Pop, GetTop)
// UndoStack Constructor
StringList::UndoStack::UndoStack() {
    capacity = 4;
    top = -1;
    stack = new UndoAction[capacity];
}

// UndoStack Destructor
StringList::UndoStack::~UndoStack() {
    delete[] stack;
}

// UndoStack Push
void StringList::UndoStack::push(const UndoAction& action) {
    if (top + 1 == capacity) {
        capacity *= 2;
        UndoAction* newStack = new UndoAction[capacity];
        for (int i = 0; i <= top; i++) {
            newStack[i] = stack[i];
        }
        delete[] stack;
        stack = newStack;
    }
    stack[++top] = action;
}

// UndoStack Pop
StringList::UndoAction StringList::UndoStack::pop() {
    if (top == -1) {
        throw std::out_of_range("UndoStack::pop: Stack is empty");
    }
    return stack[top--];
}

// UndoStack GetTop
int StringList::UndoStack::getTop() const {
    return top;
}
