// Alexander Potiagalov (301586871)
// Novemeber 22nd, 2024
#include "Wordlist.h"
#include <iomanip>
#include <stdexcept>
#include <fstream> 
#include <string>
using std::string;
using std::to_string;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::setprecision;
using std::fixed;
using std::invalid_argument;
using std::max;

// Wordlist Public Method Implementations:
// Default Constructor
Wordlist::Wordlist()
{
    root = nullptr;
    wordListSize = 0;
    totalWordCount = 0;
    singleTonsCount = 0;
}

// File Constructor
Wordlist::Wordlist(const string& filename)
{
    root = nullptr;
    wordListSize = 0;
    totalWordCount = 0;
    singleTonsCount = 0;
    
    ifstream myFile;
    myFile.open(filename);
    if (!myFile) {
        throw invalid_argument("Error: Could not open file " + filename);
    }
    string word;
    while (myFile >> word) {
        insert(word); 
    }
    myFile.close();
}

// Copy Constructor
Wordlist::Wordlist(const Wordlist& other) {
    root = nullptr; 
    wordListSize = other.wordListSize;
    totalWordCount = other.totalWordCount;
    singleTonsCount = other.singleTonsCount;

    if (other.root != nullptr) {
        root = copyHelper(other.root);
    }
}

// Overloaded Assignment operator
Wordlist& Wordlist::operator=(const Wordlist& other){
    if(this != &other){
        deleteHelper(root);
        root = nullptr; 
        wordListSize = other.wordListSize;
        totalWordCount = other.totalWordCount;
        singleTonsCount = other.singleTonsCount;

        if (other.root != nullptr) {
            root = copyHelper(other.root);
        }
        
    } return *this;
}
// Destructor 
Wordlist::~Wordlist()
{
    deleteHelper(root);
}
// Insert
void Wordlist::insert(const string& word) 
{
    root = insertHelper(root, word);
}

// Remove
bool Wordlist::remove(const string& word)
{
    bool removed = false;
    root = removeHelper(root, word, removed);
    if (removed){
        wordListSize--;
    }
    return removed;
}

// getCount
int Wordlist::getCount(const string& word) const
{
    AVLTreeNode* current = root;
    while(current != nullptr){
        if (word == current->word){
            return current->count;
        } else if (word < current->word){
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return 0;
}

// Contains
bool Wordlist::contains(const string& word) const
{
    return getCount(word) > 0;
}

// differentWords
int Wordlist::differentWords() const
{
    return wordListSize;
}

// totalWords
int Wordlist::totalWords() const
{
    return totalWordCount;
}

// mostFrequent
string Wordlist::mostFrequent() const {
    if (root == nullptr){
        throw invalid_argument("Word List is empty.");
    } 
    AVLTreeNode* mostFrequentNode = mostFrequentHelper(root, root);
    if (mostFrequentNode == nullptr) {
        throw invalid_argument("Word List is empty."); 
    }
    return mostFrequentNode->word + " " + to_string(mostFrequentNode->count);
}

// singletons
int Wordlist::singletons() const{
    return singleTonsCount;
}

// Prints useful statistics about the word list
void Wordlist::printStatistics() const
{
	cout << "Number of different words: " << differentWords() << endl;
	cout << "    Total number of words: " << totalWords() << endl;
	cout << "       Most frequent word: " << mostFrequent() << endl;
	cout << "     Number of singletons: " << singletons()
		<< setprecision(0) << fixed
		<< " (" << 100.0 * singletons() / differentWords() << "%)"
		<< endl;
}

// printWords
void Wordlist::printWords() const 
{
    printHelper(root);
}
// getRoot
// Already implemented in the header file


// Private Helper Functions:
// update height helper
void Wordlist::updateHeight(AVLTreeNode* node) {
    if (node == nullptr) return;

    int leftHeight = node->left ? node->left->height : -1;
    int rightHeight = node->right ? node->right->height : -1;
    node->height = 1 + max(leftHeight, rightHeight);
}

// get balance factor helper
int Wordlist::getBalance(AVLTreeNode* node) const {
    if (node == nullptr) return 0;

    int leftHeight = node->left ? node->left->height : -1;
    int rightHeight = node->right ? node->right->height : -1;
    return leftHeight - rightHeight;
}
// left rotation helper function 
AVLTreeNode* Wordlist::leftRotate(AVLTreeNode* x)
{
    AVLTreeNode* y = x->right;
    x->right = y->left;
    if (y->left != nullptr){
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr){
        root = y;
    } else if (x == x->parent->left){
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
    updateHeight(x);
    updateHeight(y);
    return y;
} 

// right rotation helper function
AVLTreeNode* Wordlist::rightRotate(AVLTreeNode* y)
{
    AVLTreeNode* x = y->left;
    y->left = x->right;
    if (x->right != nullptr){
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == nullptr){
        root = x;
    } else if (y == y->parent->right){
        y->parent->right = x;
    } else {
        y->parent->left = x;
    }
    x->right = y;
    y->parent = x;
    updateHeight(y);
    updateHeight(x);
    return x;
} 
	
// Insertion Helper
AVLTreeNode* Wordlist::insertHelper(AVLTreeNode* node, const string& word) 
{
    if (node == nullptr) {
        wordListSize++;  
        totalWordCount++; 
        singleTonsCount++;
        AVLTreeNode* newNode = new AVLTreeNode(word);  
        return newNode;
    }

    if (word < node->word) {
        node->left = insertHelper(node->left, word);
        node->left->parent = node; 
    } else if (word > node->word) {
        node->right = insertHelper(node->right, word);
        node->right->parent = node;
    } else {
        if (node->count == 1) {
            singleTonsCount--; 
        }
        node->count++;
        totalWordCount++;
    }

    // AVL implementation 
    updateHeight(node);
    int balance = getBalance(node);
    // Left Left (LL) Case
    if (balance > 1 && word < node->left->word) {
        return rightRotate(node);
    }
    // Right Right (RR) Case
    if (balance < -1 && word > node->right->word) {
        return leftRotate(node);
    }
    // Left Right (LR) Case
    if (balance > 1 && word > node->left->word) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // Right Left (RL) Case
    if (balance < -1 && word < node->right->word) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;  
}


// Removal Helper
AVLTreeNode* Wordlist::removeHelper(AVLTreeNode* node, const string& word, bool& removed) 
{
    if (node == nullptr) return nullptr;

    if (word < node->word) {
        node->left = removeHelper(node->left, word, removed);
        if (node->left != nullptr) node->left->parent = node;
    } else if (word > node->word) {
        node->right = removeHelper(node->right, word, removed);
        if (node->right != nullptr) node->right->parent = node;
    } else { 
        removed = true;
        totalWordCount -= node->count;
        if (node->count == 1) {
            singleTonsCount--;
        }
        
        // Case 1: Node is a leaf node
        if (node->left == nullptr && node->right == nullptr) {
            if (node == root) root = nullptr;
            delete node;
            return nullptr;
        }

        // Case 2: Node has only one child
        if (node->left == nullptr) {
            AVLTreeNode* temp = node->right;
            if (node == root) root = temp; 
            temp->parent = node->parent;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            AVLTreeNode* temp = node->left;
            if (node == root) root = temp;
            temp->parent = node->parent;
            delete node;
            return temp;
        }

        // Case 3: Node has two children
        AVLTreeNode* predecessor = node->left;
        while (predecessor->right != nullptr) {
            predecessor = predecessor->right;
        }
        node->word = predecessor->word;
        node->count = predecessor->count;
        node->height = predecessor->height;
        totalWordCount += predecessor->count;
        node->left = removeHelper(node->left, predecessor->word, removed);
        
    }

    // AVL implementation 
    updateHeight(node);
    int balance = getBalance(node);
    // Left-Left (LL) Case
    if (balance > 1 && getBalance(node->left) >=0 ){
        return rightRotate(node);
    }
    // Right-Right (RR) Case
    if (balance < -1 && getBalance(node->right) <= 0){
        return leftRotate(node);
    }
    // Left-Right (LR) Case
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // Right-Left (RL) Case
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

// copy helper function
AVLTreeNode* Wordlist::copyHelper(AVLTreeNode* otherNode) 
{
    if (otherNode == nullptr) return nullptr;

    AVLTreeNode* node = new AVLTreeNode(otherNode->word);
    node->count = otherNode->count;
    node->height = otherNode->height;
    node->parent = nullptr;
    node->left = nullptr;
    node->right = nullptr;
    
    node->left = copyHelper(otherNode->left);
    if (node->left != nullptr) node->left->parent = node;
    node->right = copyHelper(otherNode->right);
    if (node->right != nullptr) node->right->parent = node;

    return node;
}

// delete helper function
void Wordlist::deleteHelper(AVLTreeNode* node)
{
    if (node == nullptr) return;
    deleteHelper(node->left);
    deleteHelper(node->right);
    delete node;
}
// print helper function
void Wordlist::printHelper(AVLTreeNode* node) const 
{
    if (node == nullptr) return;
    printHelper(node->left); 
    cout << node->word << " " << node->count << endl;
    printHelper(node->right);
}

// most frequent word helper
AVLTreeNode* Wordlist::mostFrequentHelper(AVLTreeNode* node, AVLTreeNode* currentMax) const {
    if (node == nullptr) return currentMax;
    if (node->count > currentMax->count || (node->count == currentMax->count && node->word < currentMax->word)) {
        currentMax = node;
    }
    currentMax = mostFrequentHelper(node->left, currentMax);
    return mostFrequentHelper(node->right, currentMax);
}
