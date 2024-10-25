#include "PlayList.h"
#include "Song.h"
#include <iostream>
#include <string>
#include <limits>

using namespace std;

void printPlayList(const PlayList& playlist){
    int count = 0;
    for (int i = 0; i < playlist.size(); i++){
        Song song_printed = playlist.get(i);
        cout << i + 1 << " " << song_printed.getName() << " (" << song_printed.getArtist() << ") " << song_printed.getLength() << "s" << endl;
        count++;
    }
    cout << "There are " << count << " songs in the play list.\n" << endl;
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
    
    do {
        cout << "Enter 1 (insert), 2 (remove), 3 (swap), 4 (print) or 5 (quit): ";
        cin >> choice;
        
        if (cin.fail() || cin.peek() != '\n') {
            // Clear the failbit and ignore the remaining
            // input
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Invalid choice! Please enter a number between 1 and 5.\n" << endl;
            continue; // Restart the loop to prompt the user again
        }
        
        // Choice 1
        if (choice == 1) {
            // Insert a song
            string name, artist;
            int length, position;
            cout << "Song name: ";
            getline(cin>>ws, name);
            cout << "Artist: ";
            getline(cin>>ws, artist);
            cout << "Length: ";
            cin >> length;
            
            // If the input for length fails (i.e., a letter is entered instead of a number)
            if (cin.fail() || cin.peek() != '\n') {
                cin.clear();  // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore invalid input
                cout << "Invalid input. Please enter a number for the length.\n" << endl;
                continue;  // Restart the loop to prompt for input again
            }
            
            // Check if playlist is empty
            if (playlist.size() == 0) {
                cout << "Position (1): ";
            } else {
                cout << "Position (1 to " << playlist.size() + 1 << "): ";
            }
            
            cin >> position;

            if (cin.fail() || position < 1 || position > playlist.size() + 1 || cin.peek() != '\n') {
                cin.clear();  // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore invalid input
                cout << "You entered an invalid position.\n" << endl;
                continue;  // Restart the loop to prompt for input again
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

            if (cin.fail() || position < 1 || position > playlist.size() || cin.peek() != '\n') {
                cin.clear();  // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore invalid input
                cout << "You entered an invalid position\n" << endl;
                continue;  // Restart the loop to prompt for input again
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
            if (cin.fail() || pos1 > playlist.size() || pos1 < 1 || cin.peek() != '\n') {
                cin.clear();  // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore invalid input
                cout << "Invalid position for 1st song being swapped.\n" << endl;
                continue;  // Restart the loop to prompt for input again
            }
            
            cout << "with the song at position (1 to " << playlist.size() << "): ";
            cin >> pos2;
            if (cin.fail() || pos2 > playlist.size() || pos2 < 1 || cin.peek() != '\n') {
                cin.clear();  // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore invalid input
                cout << "Invalid position for 2nd song being swapped.\n" << endl;
                continue;  // Restart the loop to prompt for input again
            }

            playlist.swap(pos1 - 1, pos2 - 1);
            cout << "You swapped the songs at positions " << pos1 << " and " << pos2 << "\n" << endl;
            
        // Choice 4
        } else if (choice == 4) {
            // Print the playlist
            if (playlist.size() == 0) {
                cout << "The play list is empty.\n" << endl;
                continue;
            } else {
                printPlayList(playlist);
            }

        } else if (choice < 0 || choice != 5) {
            cout << "Invalid choice! Please enter a number between 1 and 5.\n" << endl;
            continue;
        }

    } while (choice != 5);
    // Choice 5
    cout << "You have chosen to quit the program." << endl;
    return 0;
}
