// Alexander Potiagalov (301586871)
// Novemeber 22nd, 2024
#pragma once
#include <string>
#include <iostream>
#include <stdexcept>
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::invalid_argument;

class AVLTreeNode {
public:
	// parent - pointer to parent
	AVLTreeNode* parent; 
	// left - pointer to left child
	AVLTreeNode* left;
	// right - pointer to right child
	AVLTreeNode* right;
	// word - node's string data
	string word;
	// count - number of times the word appears
	unsigned int count;
	// height - node's height
    unsigned int height;
	// Constructors ...
	AVLTreeNode(const string& word) : word(word), count(1), parent(nullptr), left(nullptr), right(nullptr), height(0) {}
};

// Wordlist class
class Wordlist
{
private:
	// Class attributes go here
	// Your class MUST have a root node named root (below)
	AVLTreeNode* root; // DO NOT REMOVE
	// unsigned integer attribute that records its size
	unsigned int wordListSize;
	// Total words attribute that records sum of the word counts
	unsigned int totalWordCount;
	// singletons counter 
	unsigned int singleTonsCount;
	
	// Helper Functions
    // update height helper
    void updateHeight(AVLTreeNode* node);
    // get balance factor helper
    int getBalance(AVLTreeNode* node) const;
	// left rotation helper function 
	AVLTreeNode* leftRotate(AVLTreeNode* x); 
	// right rotation helper function
	AVLTreeNode* rightRotate(AVLTreeNode* y); 
	// Insertion Helper
    AVLTreeNode* insertHelper(AVLTreeNode* node, const string& word);
	// Removal Helper
    AVLTreeNode* removeHelper(AVLTreeNode* node, const string& word, bool& removed);
	// copy helper function
	AVLTreeNode* copyHelper(AVLTreeNode* otherNode); 
	// delete helper function
	void deleteHelper(AVLTreeNode* node); 
	// print helper function
	void printHelper(AVLTreeNode* node) const; 
	// most frequent helper
	AVLTreeNode* mostFrequentHelper(AVLTreeNode* node, AVLTreeNode* currentMax) const;
public:
	// public methods go here
	// default constructor
	Wordlist(); 
	// file constructor 
	Wordlist(const string& filename); 
	// copy constructor
	Wordlist(const Wordlist& other);
	// overloaded Assignment operator
	Wordlist& operator=(const Wordlist& other);
	// destructor
	~Wordlist();
	// insert
	void insert(const string& word);
	// remove 
	bool remove(const string& word);
	// getCount
	int getCount(const string& word) const; 
	// contains
	bool contains(const string& word) const; 
	// differentWords
	int differentWords() const; 
	// totalWords
	int totalWords() const; 
	// mostFrequent
	string mostFrequent() const; 
	// singletons
	int singletons() const; 
	// Prints useful statistics about the word list
	void printStatistics() const;
    // printWords
    void printWords() const;
    // getRoot Returns the root of the AVL tree
	AVLTreeNode* getRoot() const { return root; }; // DO NOT REMOVE
};
