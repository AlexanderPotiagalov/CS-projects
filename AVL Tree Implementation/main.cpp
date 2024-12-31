// Alexander Potiagalov (301586871)
// 09/18/2024

#include "PlayList.h"
#include "Song.h"
#include <iostream>
#include <string>
#include <limits>

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::numeric_limits;
using std::ws;
using std::streamsize;

/* Summary of Big-O Notation:

PlayList Methods :
Constructor: O(1) The default constructor just sets head to nullptr and playListSize to 0. These are both constant time operations.
Copy constructor: O(n) The copy constructor goes through the original playlist only once and inserts each node into the new playlist only once. The time complexity is linear
Destructor: O(n) The destructor goes through the entire linked list to delete each node. Since every node is only visited once and then erased, the time complexity is linear.
Assignment operator: O(n) Just like the copy constructor, the assignment operator deletes the current list and makes a deep copy of the playlist pl. Since this only happens once (one iteration), the time complexity is linear
Insert: O(n) The worst case is that the program has to go all the way through the list only once to find the correct location to insert the new node, so the time complexity is linear.
Remove: O(n) Just like the insert method, the worst case is that the program has to go all the way through the list only once in order to remove and delete a song so the time complexity is linear.
Get: O(n) Just like remove, in the worst case is that the method must iterate through all the songs to get to the song in the correct position. Therefore, the time complexity is linear.
Swap: O(n) This method has to find the nodes at positions pos1 and pos2, and traverse the list only once to do that. Even in the worst case, both positionas are at the end of the list, so the time complexity is linear.
Size: O(1) The size method just returns playListSize which is a member variable. This operation happens in constant time.

Main Function Commands:
Enter a song: O(n) In the worst case when inserting a song, the program may need to traverse the whole playlist only once to find the correct insertion position. Therefore, the time complexity is linear.
Remove a song: O(n) In the worst case when inserting a song, the program may need to traverse the whole playlist only once to find the correct insertion position. Therefore, the time complexity is linear.
Swap two songs: O(n) Swapping two songs involves locating both songs in the list. In the worst case, the program will need to traverse all n nodes to locate the two positions. Therefore, the time complexity is linear.
Print all songs: O(n) Printing the songs involves iterating through all n nodes in the playlist, so the time complexity is linear.
*/

// Function to validate the user's input
bool isValidInput() {
    if (cin.fail() || cin.peek() != '\n') {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  
        return false;
    }
    return true;
}
// Function to print playlist
void printPlayList(const PlayList& playlist){
    for (int i = 0; i < playlist.size(); i++){
        Song song_printed = playlist.get(i);
        cout << i + 1 << " " << song_printed.getName() << " (" << song_printed.getArtist() << ") " << song_printed.getLength() << "s" << endl;
    }
    cout << "There are " << playlist.size() << " songs in the play list.\n" << endl;
}

int main() {
    PlayList playlist;
    int choice;
    
    cout << "Menu:" << endl;
    cout << "1 - Enter a song in the play list at a given position" << endl;
    cout << "2 - Remove a song from the play list at a given position" << endl;
    cout << "3 - Swap two songs in the play list" << endl;
    cout << "4 - Print all the songs in the play list" << endl;
    cout << "5 - Quit\n" << endl;
    
    while (true) {
        cout << "Enter 1 (insert), 2 (remove), 3 (swap), 4 (print) or 5 (quit): ";
        cin >> choice;
        
        if (!isValidInput() || choice < 1 || choice > 5) {
            cout << "Invalid choice! Please enter a number between 1 and 5.\n" << endl;
            continue;  
        }
        
        // Choice 1
        if (choice == 1) {
            string name, artist;
            int length, position;
            cout << "Song name: ";
            getline(cin>>ws, name);
            cout << "Artist: ";
            getline(cin>>ws, artist);
            cout << "Length: ";
            cin >> length;
            
            if (!isValidInput() || length <= 0) {
                cout << "Invalid input. Please enter a positive number for the length.\n" << endl;
                continue;  
            }
            
            if (playlist.size() == 0) {
                cout << "Position (1): ";
            } else {
                cout << "Position (1 to " << playlist.size() + 1 << "): ";
            }
            
            cin >> position;

            if (!isValidInput() || position < 1 || position > playlist.size() + 1) {
                cout << "You entered an invalid position.\n" << endl;
                continue;  
            } else {
                Song newSong(name, artist, length);
                playlist.insert(newSong, position - 1);
                cout << "You entered " << name << " at position " << position << " in the play list\n" << endl;
            }
            
        // Choice 2
        } else if (choice == 2) {
            
            if (playlist.size() == 0){
                cout << "The play list is empty.\n" << endl;
                continue;
            }
            
            int position;
            cout << "Position (1 to " << playlist.size() << "): ";
            cin >> position;

            if (!isValidInput() || position < 1 || position > playlist.size()) {
                cout << "You entered an invalid position.\n" << endl;
                continue;  
            } else {
                Song removedSong = playlist.remove(position - 1);
                cout << "You removed " << removedSong.getName() << " from the play list\n" << endl;
            }

        // Choice 3
        } else if (choice == 3) {
            
            if (playlist.size() < 2){
                cout << "Not enough songs in the play list to swap.\n" << endl;
                continue;
            }
            
            int pos1, pos2;
            cout << "Swap song at position (1 to " << playlist.size() << "): ";
            cin >> pos1;
            if (!isValidInput() || pos1 < 1 || pos1 > playlist.size()) {
                cout << "Invalid position for the 1st song being swapped.\n" << endl;
                continue;  
            }
            
            cout << "with the song at position (1 to " << playlist.size() << "): ";
            cin >> pos2;
            if (!isValidInput() || pos2 < 1 || pos2 > playlist.size()) {
                cout << "Invalid position for the 2nd song being swapped.\n" << endl;
                continue;  
            }
            
            if (pos1 == pos2) { 
                cout << "Same positions, no swap needed.\n" << endl;
                continue;  
            }

            playlist.swap(pos1 - 1, pos2 - 1);
            cout << "You swapped the songs at positions " << pos1 << " and " << pos2 << "\n" << endl;
            
        // Choice 4
        } else if (choice == 4) {
            if (playlist.size() == 0) {
                cout << "The play list is empty.\n" << endl;
                continue;
            } else {
                printPlayList(playlist);
            }
        } else {
            // Choice 5
            cout << "You have chosen to quit the program." << endl;
            break;  
        }
    }
    return 0;
}
