# BillBoard Top 100 Songs Charts
# Alexander Potiagalov (301586871)
# November 1st, 2023

#Part 1
print("Welcome to the Billboard top 100 app!")
print(" ")
print("PART 1")
print("======")
print(" ")

number_of_songs_including_love = 0
number_of_songs_in_rank_1_or_2 = 0
songs_less_in_rank_wrt_pw = 0
total_weeks_on_board_all_songs = 0
count_line_in_file = 0
list_rank_songs = []
list_names_A = []
file1 = open('charts (2).csv', 'r')
next(file1)

for line in file1:
        line = line.split(",") 
        if "love" in line[2].lower():
            number_of_songs_including_love += 1
        if line[1] == '1' or line[1] == '2':
            number_of_songs_in_rank_1_or_2 += 1
            list_rank_songs.append(line[2])
        if line[3][0].lower() == "a":
            list_names_A.append(line[3])
        if int(line[1]) < int(line[4]):
            songs_less_in_rank_wrt_pw += 1
        total_weeks_on_board_all_songs += int(line[6])
        count_line_in_file += 1 


print(f"Number of songs in rank 1 or 2 : {number_of_songs_in_rank_1_or_2}")    
for song in list_rank_songs:
     print(song)

print(" ")

print("Artists names starting with 'A':")
for name in list_names_A:
     print(name)

print(" ")
print(f"Number of songs containing the word 'love': {number_of_songs_including_love}")
print(" ")
print(f"Number of songs that are less in the rank wrt previous week : {songs_less_in_rank_wrt_pw}")
print(" ")
average_weeks_on_board_all_songs = total_weeks_on_board_all_songs/count_line_in_file
print(("Average weeks on board all songs: {:.2f} ").format(average_weeks_on_board_all_songs))

#Part 2
print(" ")
print("PART 2")
print("======")
print(" ")
print("First query: Individual artist songs")
artist_name = input("Artist name (may be part of the name) --> ").strip(".,?!").lower()
file1.seek(0)
print()

#Only works with Ed sheeran/ try justing beiber and its messy af
"""print("Artist", end = ' ')
print("Song".rjust(33), end = ' ')
print("Date".rjust(35), end = ' ')
print("Rank".rjust(41), end = ' ')
print("Previous rank".rjust(35))
print()"""

"""for line in file1:
    line = line.split(",")
    if artist_name in line[3].lower():
        print("{:<10}".format(line[3]), end = ' ')
        print("{:>35}".format(line[2]), end = ' ')
        print("{:>35}".format(line[0]), end = ' ')
        print("{:>35}".format(line[1]), end = ' ')
        print("{:>35}".format(line[4]))"""

artist = "Artist"
song = "Song"
date = "Date"
rank = "Rank"
previous_rank = "Previous Rank"

print(f"{artist : <60}{song : <30}{date : <30}{rank : <25}{previous_rank}")

count = 0
for line in file1:
    line = line.split(",")
    if artist_name in line[3].lower():
        print(f"{line[3] : <60}{line[2] : <30}{line[0] : <30}{line[1] : <25}{line[4]}")
        count = 1
else:
    if count == 0:
        print()
        print("There is no such artist in the file")

print()
print("Second query: Songs and weeks on board")
song_title = input("Song title (may be part of the title) ----> ").strip(".,?!").lower()
file1.seek(0)
print()

requested_song = "Requested song"
date = "Date"
weeks_on_board = "Weeks on board"
print(f"{requested_song : <60}{date : <30}{weeks_on_board}")
print()
for line in file1:
    line = line.split(",")
    if song_title in line[2].lower():
        print(f"{line[2] : <60}{line[0] : <30}{line[6]}")
        weeks_on_board = int(line[6])
        break
file1.close()

file2 = open('charts (2).csv', 'r')
next(file2)
print("Songs with more weeks on board than the requested song")
print()

song = "Song"
date = "Date"
extra_weeks_on_board = "Extra weeks on board"
print(f"{song : <60}{date : <30}{extra_weeks_on_board}")

for line in file2:
    line = line.split(",")
    if weeks_on_board < int(line[6]):
        print(f"{line[2] : <60}{line[0] : <30}{int(line[6]) - weeks_on_board}")

file2.close()
print()
print("Bye! End of app!")

