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
arr = new string[capacity];
arr.size() = 0;
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
return arr.size();
}
// Returns true if the list is empty, false otherwise
bool StringList::empty() const
{
return arr.empty();
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
while (i < arr.size() && s != arr[i]) {
i++;
}
if (i == arr.size()) {
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
    return arr == sl.arr;
/*if (size() != sl.size())
{
return false;
}
for (int i = 0; i < size(); i++)
{
if (get(i) != sl.get(i))
{
return false;
}*/
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
for (int i = arr.size(); i > pos; i--) {
arr[i] = arr[i-1];
}
arr[pos] = str;
}
// ***UNDOABLE
// Inserts the given string at the front of the list
void StringList::insertFront(string str)
{
checkCapacity();
arr.push_front(str);
}
// ***UNDOABLE
// Inserts the given string at the back of the list
void StringList::insertBack(string str)
{
checkCapacity();
arr.push_back(str);
}
// ***UNDOABLE
// Removes the element at the given index and moves elements after it down
void StringList::remove(int pos)
{
checkBounds(pos, "remove");
for (int i = pos; i < arr.size(); i++) {
arr[i] = arr[i + 1];
}
}
// ***UNDOABLE
// Empties the list
void StringList::removeAll()
{
for (int i = 0; i < n; i++) {
arr[i] = "";
}
arr.size() = 0;
}
// Undoes the last operation that modified the list
void StringList::undo()
{
// TO DO
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
    arr = lst.arr;
}
