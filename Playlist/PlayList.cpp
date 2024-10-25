// Write your name and date here
//Alexander Potiagalov (301586871)
//09/10/2024

#include "PlayList.h"
#include <stdexcept>

// PlayList method implementations go here
// Default Constructor
PlayList::PlayList() : head(nullptr), playListSize(0) {}

// Deep copy constructor
PlayList::PlayList(const PlayList& pl) : head(nullptr), playListSize(0) {
    PlayListNode* current = pl.head;
    while(current != nullptr){
        insert(current->song, playListSize);  // Insert each song at the end of the new list
        current = current->next;
    }
}
// Destructor
PlayList::~PlayList() {
    while(head != nullptr){
        PlayListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

// Overloaded assignment operator
PlayList& PlayList::operator=(const PlayList & pl){

    if (this != &pl) {
        // Deallocate current linked list
        while (head != nullptr) {
            PlayListNode* temp = head;
            head = head->next;
            delete temp;
        }
        // Reset the playlist size to 0
        playListSize = 0;

        // Deep copy from the other playlist
        PlayListNode* current = pl.head;
        while (current != nullptr) {
            insert(current->song, playListSize);  // Inserting at the end of the list
            current = current->next;
        }
    }
    return *this;  // Return reference to the calling object
}


// Insert
void PlayList::insert(Song sng, unsigned int pos){
    if (pos > playListSize){
        throw std::out_of_range("Invalid Position");
    }
    
    PlayListNode* newNode = new PlayListNode(sng);

    if (pos == 0){
        newNode->next = head;
        head = newNode;
    } else { 
        PlayListNode* current = head;
        PlayListNode* prev = nullptr;
        for (int i = 0; i < pos; i++){
            prev = current;
            current = current->next;
        }
        prev->next = newNode;
        newNode->next = current;
    }
    playListSize++;
}

// Get
Song PlayList::get(unsigned int pos) const {
    PlayListNode* current = head;
    if (pos >= playListSize){
        throw std::out_of_range("Invalid Position");
    }
    if (head == nullptr){
        throw std::out_of_range("Empty Playlist");
    }
    for (int i = 0; i < pos; i++){
        current = current->next;
    }
    return current->song;
} 

// Remove
Song PlayList::remove(unsigned int pos) {
    if (pos >= playListSize || head == nullptr) {
        throw std::out_of_range("Invalid Position");
    }
    
    PlayListNode* current = head;
    PlayListNode* prev = nullptr;
    //Song removedSong("", "", 0);  // Initialize with empty strings and 0 length
    
    if (pos == 0) {
        removedSong = current->song;
        head = current->next;
        delete current;
        playListSize--;
        return removedSong;
    }
    for (unsigned int i = 0; i < pos; i++) {
        prev = current;
        current = current->next;
    }
    removedSong = current->song;    
    prev->next = current->next;     
    delete current;                 
    playListSize--;                 
    return removedSong;
}

// Swap
void PlayList::swap(unsigned int pos1, unsigned int pos2){
    if (pos1 >= playListSize || pos2 >= playListSize || pos1 == pos2) {
        throw std::out_of_range("Invalid Position");
    }
    if (head == nullptr){
        throw std::out_of_range("Empty Playlist");
    }
    PlayListNode* prev1 = nullptr;
    PlayListNode* prev2 = nullptr;
    PlayListNode* node1 = head;
    PlayListNode* node2 = head;

    // Find node1 and its previous node
    for (unsigned int i = 0; i < pos1; i++) {
        prev1 = node1;
        node1 = node1->next;
    }
    // Find node2 and its previous node
    for (unsigned int i = 0; i < pos2; i++) {
        prev2 = node2;
        node2 = node2->next;
    }

    // Checking if node1 is the head
    if (prev1 == nullptr){ 
        head = node2; 
    } else {
        prev1->next = node2;
    }

    // Checking if node2 is the head
    if (prev2 == nullptr) {
        head = node1;
    } else {
        prev2->next = node1;
    }

    PlayListNode* temp = node1->next;
    node1->next = node2->next;
    node2->next = temp;

}

unsigned int PlayList::size() const {
    return playListSize;
}