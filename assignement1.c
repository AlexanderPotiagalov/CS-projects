GAME 1 : 

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void evaluate_guess(int *chosenanswer, int *guess, int *exact_match, int *partial_match) {
    int *answer_digits_count = (int *)calloc(10, sizeof(int)); // Array to count each digit in the chosen answer
    int *guess_digits_count = (int *)calloc(10, sizeof(int));  // Array to count each digit in the guess

    // Check if memory allocation was successful
    if (answer_digits_count == NULL || guess_digits_count == NULL) {
        printf("Memory allocation failed. Exiting.\n");
        exit(EXIT_FAILURE);
    }

    *exact_match = 0;
    *partial_match = 0;

    // Count each digit in the chosen answer and the guess
    for (int i = 0; i < 6; i++) {
        answer_digits_count[chosenanswer[i]]++;
        guess_digits_count[guess[i]]++;
    }

    // Exact matches
    for (int i = 0; i < 6; i++) {
        if (chosenanswer[i] == guess[i]) {
            (*exact_match)++;
            // Decrement the count for the exact match
            guess_digits_count[guess[i]]--;
        }
    }

    // Partial matches
    for (int i = 0; i < 6; i++) {
        if (chosenanswer[i] != guess[i] && guess_digits_count[chosenanswer[i]] > 0) {
            (*partial_match)++;
            // Decrement the count for the partial match
            guess_digits_count[chosenanswer[i]]--;
        }
    }

    // Free dynamically allocated memory
    free(answer_digits_count);
    free(guess_digits_count);
}

void store_and_display_guess_history(int **guess_history, int *exact_match_history, int *partial_match_history, int *guess, int exact_match, int partial_match, int guess_count) {
    // Store the guess and its feedback in the corresponding arrays
    for (int i = 0; i < 6; i++) {
        guess_history[guess_count][i] = guess[i];
    }
    exact_match_history[guess_count] = exact_match;
    partial_match_history[guess_count] = partial_match;

    // Display guess history
    for (int i = 0; i <= guess_count; i++) {
        printf("Guess %d: ", i + 1);
        for (int j = 0; j < 6; j++) {
            printf("%d", guess_history[i][j]);
        }
        printf(" - %d correct, %d partially correct\n", exact_match_history[i], partial_match_history[i]);
    }
}

void read_guess(int *guess_array) {
    char c;
    int digit_count = 0;
    printf("Enter your guess: \n");
    while (1) {
        c = getchar();
        if (isdigit(c)) {
            if (digit_count < 6) {
                guess_array[digit_count++] = c - '0'; // Convert char to int
            }
        } else if (c == ' ' || c == '\t') {
            // Ignore spaces and tabs
            continue;
        } else if (c == '\n') {
            if (digit_count < 6) {
                printf("Please enter %d more digits.\n", 6 - digit_count);
            } else {
                break;
            }
        } else {
            printf("Invalid character detected. Please enter digits only.\n");
            // Clear remaining characters in the stream
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Enter your guess again: \n");
            digit_count = 0; // Reset digit count
            continue;
        }
    }
}

int main() {
    int seedvalue;
    printf("Enter the integer value of the seed for the game: ");
    scanf("%d", &seedvalue);
    getchar(); // Consume the newline character left in the input buffer

    int *chosenanswer = (int *)malloc(6 * sizeof(int));

    srand(seedvalue);
    printf("The array of the number is:\n");
    for (int i = 0; i < 6; ++i) {
        chosenanswer[i] = rand() % 10; // Generate random number between 0 and 9
        printf("%d", chosenanswer[i]);
    }
    printf("\n");

    int **guess_history = (int **)malloc(10 * sizeof(int *)); // Array to store previous guesses
    int *exact_match_history = (int *)malloc(10 * sizeof(int)); // Array to store the number of exact matches for each guess
    int *partial_match_history = (int *)malloc(10 * sizeof(int)); // Array to store the number of partial matches for each guess
    int guess_count = 0;

    if (guess_history == NULL || exact_match_history == NULL || partial_match_history == NULL) {
        printf("Memory allocation failed. Exiting.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 10; ++i) {
        guess_history[i] = (int *)malloc(6 * sizeof(int));
        if (guess_history[i] == NULL) {
            printf("Memory allocation failed. Exiting.\n");
            exit(EXIT_FAILURE);
        }
    }
    
    while (1) {
        int guess[6];
        read_guess(guess);

        int exact_match, partial_match;
        evaluate_guess(chosenanswer, guess, &exact_match, &partial_match);
        store_and_display_guess_history(guess_history, exact_match_history, partial_match_history, guess, exact_match, partial_match, guess_count);

        // Check if the user has guessed the sequence correctly
        if (exact_match == 6) {
            printf("Congratulations! You've guessed the sequence of digits correctly.\n");
            break;
        }

        guess_count++;

        if (guess_count >= 10) {
            printf("You've reached the maximum number of guesses.\n");
            break;
        }
    }

    // Free dynamically allocated memory
    free(chosenanswer);
    free(exact_match_history);
    free(partial_match_history);
    free(guess_history);

    return 0;
}

GAME 2 : Version 1 

#include <stdio.h>
#include <stdlib.h>

// Enumeration for initialization type
enum initTypeList { Random = 1, Checkerboard, AllWhite };
// Structure for representing robots
struct Robot {
    int x;
    int y;
    int direction;
    int paintColour;
};

int InitBoard(int **boardpp, int numRows, int numCols, enum initTypeList mylist, unsigned int seed);
void InitBoardRand(int **board, int numRows, int numCols, unsigned int seed);
void InitBoardChecker(int **board, int numRows, int numCols);
void InitBoardAllWhite(int **board, int numRows, int numCols);
void PlaceRobots(struct Robot *robots, int numRobots, int numRows, int numCols, unsigned int seed);
void RunGame(struct Robot *robots, int numRobots, int numRows, int numCols, int numTurns);

int main() {
    // Step 1: Read the name of the input file
    char *filename = malloc(256 * sizeof(char));
    if (filename == NULL) {
        fprintf(stderr, "ERROR: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    FILE *input_file = NULL;
    int attempts = 0;
    const int MAX_ATTEMPTS = 5;

    while (input_file == NULL && attempts < MAX_ATTEMPTS) {
        printf("Enter the name of the input file: ");
        if (scanf("%255s", filename) != 1) {
            fprintf(stderr, "ERROR: Input file not opened correctly.\n");
            exit(EXIT_FAILURE);
        }

        input_file = fopen(filename, "r");
        if (input_file == NULL) {
            fprintf(stderr, "ERROR: Failed to open the input file. Attempt %d\n", attempts + 1);
            attempts++;
        }
    }

    // Check if the file was opened successfully after maximum attempts
    if (input_file == NULL) {
        fprintf(stderr, "ERROR: Failed to open the input file %d times. Terminating the program.\n", MAX_ATTEMPTS);
        free(filename);
        exit(EXIT_FAILURE);
    }

    /* Step 2 */
    int numRows, numCols, numRobots, initTypeValue, initSeed, numTurns, interval;
    char *outputFilename = NULL;
    outputFilename = malloc(256 * sizeof(char));
    if (outputFilename == NULL) {
        fprintf(stderr, "ERROR: Memory allocation failed\n");
        fclose(input_file);
        free(filename);
        exit(EXIT_FAILURE);
    }

    if (fscanf(input_file, "%d", &numRows) != 1 || numRows < 20 || numRows > 300) {
        fprintf(stderr, "ERROR: Invalid value for number of rows\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    if (fscanf(input_file, "%d", &numCols) != 1 || numCols < 20 || numCols > 300) {
        fprintf(stderr, "ERROR: Invalid value for number of columns\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    if (fscanf(input_file, "%d", &numRobots) != 1 || numRobots < 1 || numRobots > 10) {
        fprintf(stderr, "ERROR: Invalid value for number of robots\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    if (fscanf(input_file, "%d", &initTypeValue) != 1 || initTypeValue < 1 || initTypeValue > 3) {
        fprintf(stderr, "ERROR: Invalid value for initialization type\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    if (fscanf(input_file, "%d", &initSeed) != 1 || initSeed < 10 || initSeed > 32767) {
        fprintf(stderr, "ERROR: Invalid value for seed\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    if (fscanf(input_file, "%d", &numTurns) != 1 || numTurns < 10 || numTurns > 5000) {
        fprintf(stderr, "ERROR: Invalid value for number of turns\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    if (fscanf(input_file, "%d", &interval) != 1 || interval < 1 || interval > numTurns) {
        fprintf(stderr, "ERROR: Invalid value for interval\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    // Concatenate output filename
    if (fscanf(input_file, "%255s", outputFilename) != 1) {
        fprintf(stderr, "ERROR: Invalid output filename\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }
    // Proceed with further processing using obtained values
    // ...
    
    // Step 3: Dynamically allocate 2-D integer array boardpp
    int **boardpp = (int **)malloc(numRows * sizeof(int *));
    if (boardpp == NULL) {
        fprintf(stderr, "ERROR: Array of pointers for boardpp could not be allocated\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < numRows; i++) {
        boardpp[i] = (int *)malloc(numCols * sizeof(int));
        if (boardpp[i] == NULL) {
            fprintf(stderr, "ERROR: Array storage could not be allocated\n");
            // Free allocated memory
            for (int j = 0; j < i; j++) {
                free(boardpp[j]);
            }
            free(boardpp);
            fclose(input_file);
            free(filename);
            free(outputFilename);
            exit(EXIT_FAILURE);
        }
    }

    // Step 4: Dynamically allocate 1-D array of structures for robots
    struct Robot *robots = (struct Robot *)malloc(numRobots * sizeof(struct Robot));
    if (robots == NULL) {
        fprintf(stderr, "ERROR: Array of structures for robots could not be allocated\n");
        // Free allocated memory
        for (int i = 0; i < numRows; i++) {
            free(boardpp[i]);
        }
        free(boardpp);
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }
    
    int initResult = InitBoard(boardpp, numRows, numCols, (enum initTypeList)initTypeValue, initSeed);
    if (initResult != 0) {
        switch (initResult) {
            case -1:
                fprintf(stderr, "ERROR: Array of pointers for board could not be allocated\n");
                break;
            case -2:
                fprintf(stderr, "ERROR: Array storage could not be allocated\n");
                break;
            default:
                fprintf(stderr, "ERROR: Unknown error occurred during initialization\n");
                break;
        }
    }
    
    PlaceRobots(robots, numRobots, numRows, numCols, initSeed);
    RunGame(robots, numRobots, numRows, numCols, numTurns);
    
    // Final Step: Free allocated memory and close files
    for (int i = 0; i < numRows; i++) {
        free(boardpp[i]);
    }
    free(boardpp);
    free(robots);
    free(outputFilename);
    fclose(input_file);
    free(filename);

    return 0;
}

int InitBoard(int **boardpp, int numRows, int numCols, enum initTypeList mylist, unsigned int seed) {
    switch (mylist) {
        case Random:
            InitBoardRand(boardpp, numRows, numCols, seed);
            break;
        case Checkerboard:
            InitBoardChecker(boardpp, numRows, numCols);
            break;
        case AllWhite:
            InitBoardAllWhite(boardpp, numRows, numCols);
            break;
        default:
            fprintf(stderr, "ERROR: Invalid initialization type\n");
            return -1;
    }
    return 0;
}

void InitBoardRand(int **board, int numRows, int numCols, unsigned int seed) {
    srand(seed);
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            board[i][j] = rand() % 4 + 1; // Randomly choose a colour (1 to 4)
        }
    }
}

void InitBoardChecker(int **board, int numRows, int numCols) {
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            if ((i + j) % 2 == 0) {
                board[i][j] = 1; // White
            } else {
                board[i][j] = 2; // Red
            }
        }
    }
}

void InitBoardAllWhite(int **board, int numRows, int numCols) {
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            board[i][j] = 1; // White
        }
    }
}

void PlaceRobots(struct Robot *robots, int numRobots, int numRows, int numCols, unsigned int seed) {
    // Initialize the random number generator
    srand(seed);

    for (int i = 0; i < numRobots; i++) {
        // Randomly generate x and y coordinates for each robot
        robots[i].x = rand() % numCols;
        robots[i].y = rand() % numRows;

        // Randomly assign direction (1 to 4)
        robots[i].direction = rand() % 4 + 1;

        // Randomly assign paint color (1 to 4)
        robots[i].paintColour = rand() % 4 + 1;
    }
}

void RunGame(struct Robot *robots, int numRobots, int numRows, int numCols, int numTurns) {
    // Run the game for the specified number of turns
    for (int turn = 1; turn <= numTurns; turn++) {
        printf("Turn %d\n", turn);

        // Move each robot forward
        for (int i = 0; i < numRobots; i++) {
            switch (robots[i].direction) {
                case 1: // Up
                    robots[i].y = (robots[i].y - 1 + numRows) % numRows; // Ensure wraparound
                    break;
                case 2: // Right
                    robots[i].x = (robots[i].x + 1) % numCols; // Ensure wraparound
                    break;
                case 3: // Down
                    robots[i].y = (robots[i].y + 1) % numRows; // Ensure wraparound
                    break;
                case 4: // Left
                    robots[i].x = (robots[i].x - 1 + numCols) % numCols; // Ensure wraparound
                    break;
                default:
                    // Handle invalid direction
                    break;
            }
        }

        // Rotate each robot (for example, clockwise rotation)
        for (int i = 0; i < numRobots; i++) {
            robots[i].direction = (robots[i].direction % 4) + 1; // Wrap around from 4 to 1
        }

        // Change the color of the square each robot has moved onto
        // For example:
        // board[robots[i].y][robots[i].x] = robots[i].paintColour;

        // Print the board or relevant information about the game state if needed
    }
}

VERSION 2 : 

#include <stdio.h>
#include <stdlib.h>

// Enumeration for initialization type
enum initTypeList { Random = 1, Checkerboard, AllWhite };
// Structure for representing robots
struct Robot {
    int x;
    int y;
    int direction;
    int paintColour;
};

int InitBoard(int **boardpp, int numRows, int numCols, enum initTypeList mylist, unsigned int seed);
void InitBoardRand(int **board, int numRows, int numCols, unsigned int seed);
void InitBoardChecker(int **board, int numRows, int numCols);
void InitBoardAllWhite(int **board, int numRows, int numCols);
void PlaceRobots(struct Robot *robots, int numRobots, int numRows, int numCols, unsigned int seed);
void RunGame(struct Robot *robots, int numRobots, int numRows, int numCols, int numTurns, int interval, FILE *outputFile);

int main() {
    // Step 1: Read the name of the input file
    char *filename = malloc(256 * sizeof(char));
    if (filename == NULL) {
        fprintf(stderr, "ERROR: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    FILE *input_file = NULL;
    int attempts = 0;
    const int MAX_ATTEMPTS = 5;

    while (input_file == NULL && attempts < MAX_ATTEMPTS) {
        printf("Enter the name of the input file: ");
        if (scanf("%255s", filename) != 1) {
            fprintf(stderr, "ERROR: Input file not opened correctly.\n");
            exit(EXIT_FAILURE);
        }

        input_file = fopen(filename, "r");
        if (input_file == NULL) {
            fprintf(stderr, "ERROR: Failed to open the input file. Attempt %d\n", attempts + 1);
            attempts++;
        }
    }

    // Check if the file was opened successfully after maximum attempts
    if (input_file == NULL) {
        fprintf(stderr, "ERROR: Failed to open the input file %d times. Terminating the program.\n", MAX_ATTEMPTS);
        free(filename);
        exit(EXIT_FAILURE);
    }

    /* Step 2 */
    int numRows, numCols, numRobots, initTypeValue, initSeed, numTurns, interval;
    char *outputFilename = NULL;
    outputFilename = malloc(256 * sizeof(char));
    if (outputFilename == NULL) {
        fprintf(stderr, "ERROR: Memory allocation failed\n");
        fclose(input_file);
        free(filename);
        exit(EXIT_FAILURE);
    }

    if (fscanf(input_file, "%d", &numRows) != 1 || numRows < 20 || numRows > 300) {
        fprintf(stderr, "ERROR: Invalid value for number of rows\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    if (fscanf(input_file, "%d", &numCols) != 1 || numCols < 20 || numCols > 300) {
        fprintf(stderr, "ERROR: Invalid value for number of columns\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    if (fscanf(input_file, "%d", &numRobots) != 1 || numRobots < 1 || numRobots > 10) {
        fprintf(stderr, "ERROR: Invalid value for number of robots\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    if (fscanf(input_file, "%d", &initTypeValue) != 1 || initTypeValue < 1 || initTypeValue > 3) {
        fprintf(stderr, "ERROR: Invalid value for initialization type\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    if (fscanf(input_file, "%d", &initSeed) != 1 || initSeed < 10 || initSeed > 32767) {
        fprintf(stderr, "ERROR: Invalid value for seed\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    if (fscanf(input_file, "%d", &numTurns) != 1 || numTurns < 10 || numTurns > 5000) {
        fprintf(stderr, "ERROR: Invalid value for number of turns\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    if (fscanf(input_file, "%d", &interval) != 1 || interval < 1 || interval > numTurns) {
        fprintf(stderr, "ERROR: Invalid value for interval\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    // Concatenate output filename
    if (fscanf(input_file, "%255s", outputFilename) != 1) {
        fprintf(stderr, "ERROR: Invalid output filename\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }
    // Proceed with further processing using obtained values
    // ...
    
    // Step 3: Dynamically allocate 2-D integer array boardpp
    int **boardpp = (int **)malloc(numRows * sizeof(int *));
    if (boardpp == NULL) {
        fprintf(stderr, "ERROR: Array of pointers for boardpp could not be allocated\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < numRows; i++) {
        boardpp[i] = (int *)malloc(numCols * sizeof(int));
        if (boardpp[i] == NULL) {
            fprintf(stderr, "ERROR: Array storage could not be allocated\n");
            // Free allocated memory
            for (int j = 0; j < i; j++) {
                free(boardpp[j]);
            }
            free(boardpp);
            fclose(input_file);
            free(filename);
            free(outputFilename);
            exit(EXIT_FAILURE);
        }
    }

    // Step 4: Dynamically allocate 1-D array of structures for robots
    struct Robot *robots = (struct Robot *)malloc(numRobots * sizeof(struct Robot));
    if (robots == NULL) {
        fprintf(stderr, "ERROR: Array of structures for robots could not be allocated\n");
        // Free allocated memory
        for (int i = 0; i < numRows; i++) {
            free(boardpp[i]);
        }
        free(boardpp);
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }
    
    int initResult = InitBoard(boardpp, numRows, numCols, (enum initTypeList)initTypeValue, initSeed);
    if (initResult != 0) {
        switch (initResult) {
            case -1:
                fprintf(stderr, "ERROR: Array of pointers for board could not be allocated\n");
                break;
            case -2:
                fprintf(stderr, "ERROR: Array storage could not be allocated\n");
                break;
            default:
                fprintf(stderr, "ERROR: Unknown error occurred during initialization\n");
                break;
        }
    }
    
    PlaceRobots(robots, numRobots, numRows, numCols, initSeed);
    
    // Open output file
    FILE *outputFile = fopen(outputFilename, "w");
    if (outputFile == NULL) {
        fprintf(stderr, "ERROR: Failed to open output file.\n");
        // Free allocated memory
        for (int i = 0; i < numRows; i++) {
            free(boardpp[i]);
        }
        free(boardpp);
        free(robots);
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    RunGame(robots, numRobots, numRows, numCols, numTurns, interval, outputFile);
    
    // Final Step: Free allocated memory and close files
    for (int i = 0; i < numRows; i++) {
        free(boardpp[i]);
    }
    free(boardpp);
    free(robots);
    free(outputFilename);
    fclose(outputFile);
    fclose(input_file);
    free(filename);

    return 0;
}

int InitBoard(int **boardpp, int numRows, int numCols, enum initTypeList mylist, unsigned int seed) {
    switch (mylist) {
        case Random:
            InitBoardRand(boardpp, numRows, numCols, seed);
            break;
        case Checkerboard:
            InitBoardChecker(boardpp, numRows, numCols);
            break;
        case AllWhite:
            InitBoardAllWhite(boardpp, numRows, numCols);
            break;
        default:
            fprintf(stderr, "ERROR: Invalid initialization type\n");
            return -1;
    }
    return 0;
}

void InitBoardRand(int **board, int numRows, int numCols, unsigned int seed) {
    srand(seed);
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            board[i][j] = rand() % 4 + 1; // Randomly choose a colour (1 to 4)
        }
    }
}

void InitBoardChecker(int **board, int numRows, int numCols) {
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            if ((i + j) % 2 == 0) {
                board[i][j] = 1; // White
            } else {
                board[i][j] = 2; // Red
            }
        }
    }
}

void InitBoardAllWhite(int **board, int numRows, int numCols) {
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            board[i][j] = 1; // White
        }
    }
}

void PlaceRobots(struct Robot *robots, int numRobots, int numRows, int numCols, unsigned int seed) {
    // Initialize the random number generator
    srand(seed);

    for (int i = 0; i < numRobots; i++) {
        // Randomly generate x and y coordinates for each robot
        robots[i].x = rand() % numCols;
        robots[i].y = rand() % numRows;

        // Randomly assign direction (1 to 4)
        robots[i].direction = rand() % 4 + 1;

        // Randomly assign paint color (1 to 4)
        robots[i].paintColour = rand() % 4 + 1;
    }
}

void RunGame(struct Robot *robots, int numRobots, int numRows, int numCols, int numTurns, int interval, FILE *outputFile) {
    int **board = (int **)malloc(numRows * sizeof(int *));
    if (board == NULL) {
        fprintf(stderr, "ERROR: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < numRows; i++) {
        board[i] = (int *)malloc(numCols * sizeof(int));
        if (board[i] == NULL) {
            fprintf(stderr, "ERROR: Memory allocation failed\n");
            // Free allocated memory
            for (int j = 0; j < i; j++) {
                free(board[j]);
            }
            free(board);
            exit(EXIT_FAILURE);
        }
    }

    for (int turn = 0; turn < numTurns; turn++) {
        printf("Turn %d\n", turn);

        // Move each robot forward
        for (int i = 0; i < numRobots; i++) {
            switch (robots[i].direction) {
                case 1: // Up
                    robots[i].y = (robots[i].y - 1 + numRows) % numRows; // Ensure wraparound
                    break;
                case 2: // Right
                    robots[i].x = (robots[i].x + 1) % numCols; // Ensure wraparound
                    break;
                case 3: // Down
                    robots[i].y = (robots[i].y + 1) % numRows; // Ensure wraparound
                    break;
                case 4: // Left
                    robots[i].x = (robots[i].x - 1 + numCols) % numCols; // Ensure wraparound
                    break;
                default:
                    // Handle invalid direction
                    break;
            }
        }

        // Rotate each robot (for example, clockwise rotation)
        for (int i = 0; i < numRobots; i++) {
            robots[i].direction = (robots[i].direction % 4) + 1; // Wrap around from 4 to 1
        }

        // Change the color of the square each robot has moved onto
        for (int i = 0; i < numRobots; i++) {
            board[robots[i].y][robots[i].x] = robots[i].paintColour;
        }

        // Print the board to the screen and output file every interval turns
        if (turn % interval == 0 || turn == numTurns - 1) {
            printf("Board state at turn %d:\n", turn);
            fprintf(outputFile, "Board state at turn %d:\n", turn);
            for (int i = 0; i < numRows; i++) {
                for (int j = 0; j < numCols; j++) {
                    printf("%d ", board[i][j]);
                    fprintf(outputFile, "%d ", board[i][j]);
                }
                printf("\n");
                fprintf(outputFile, "\n");
            }
            printf("\n");
            fprintf(outputFile, "\n");
        }
    }

    // Free allocated memory
    for (int i = 0; i < numRows; i++) {
        free(board[i]);
    }
    free(board);
}

VERSION 3:

#include <stdio.h>
#include <stdlib.h>

// Constants
const int Directions = 4;
const int Colours = 4;
const int White = 1;
const int Red = 2;

// Enumeration for initialization type
enum initTypeList { Random = 1, Checkerboard, AllWhite };

// Structure for representing robots
struct Robot {
    int x;
    int y;
    int direction;
    int paintColour;
};

// Function prototypes
int InitBoard(int **boardpp, int numRows, int numCols, enum initTypeList mylist, unsigned int seed);
void InitBoardRand(int **board, int numRows, int numCols, unsigned int seed);
void InitBoardChecker(int **board, int numRows, int numCols);
void InitBoardAllWhite(int **board, int numRows, int numCols);
void PlaceRobots(struct Robot *robots, int numRobots, int numRows, int numCols, unsigned int seed);
void RunGame(struct Robot *robots, int numRobots, int numRows, int numCols, int numTurns, int interval, FILE *outputFile, int **board);

int main() {
    // Input validation constants
    const int Max_Attempts = 5;
    const int Min_Rows = 20;
    const int Max_Rows = 300;
    const int Min_Coloums = 20;
    const int Max_Coloums = 300;
    const int Min_Robots = 1;
    const int Max_Robots = 10;
    const int Min_initTypeValue = 1;
    const int Max_initTypeValue = 3;
    const int Min_Seed = 10;
    const int Max_Seed = 32767;
    const int Min_Turns = 10;
    const int Max_Turns = 5000;
    const int Min_Intervals = 1;

    // Step 1: Read the name of the input file
    char *filename = malloc(200 * sizeof(char));
    if (filename == NULL) {
        fprintf(stderr, "ERROR: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    FILE *input_file = NULL;
    int attempts = 0;

    while (input_file == NULL && attempts < Max_Attempts) {
        printf("Enter the name of the input file: ");
        if (scanf("%255s", filename) != 1) {
            fprintf(stderr, "ERROR: Input file not opened correctly.\n");
            exit(EXIT_FAILURE);
        }

        input_file = fopen(filename, "r");
        if (input_file == NULL) {
            fprintf(stderr, "ERROR: Failed to open the input file. Attempt %d\n", attempts + 1);
            attempts++;
        }
    }

    // Check if the file was opened successfully after maximum attempts
    if (input_file == NULL) {
        fprintf(stderr, "ERROR: Failed to open the input file %d times. Terminating the program.\n", Max_Attempts);
        free(filename);
        exit(EXIT_FAILURE);
    }

    // Step 2: Read input parameters from the file
    int numRows, numCols, numRobots, initTypeValue, initSeed, numTurns, interval;
    char *outputFilename = malloc(200 * sizeof(char));
    if (outputFilename == NULL) {
        fprintf(stderr, "ERROR: Memory allocation failed\n");
        fclose(input_file);
        free(filename);
        exit(EXIT_FAILURE);
    }

    if (fscanf(input_file, "%d", &numRows) != 1 || numRows < Min_Rows || numRows > Max_Rows) {
        fprintf(stderr, "ERROR: Invalid value for number of rows\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    if (fscanf(input_file, "%d", &numCols) != 1 || numCols < Min_Coloums || numCols > Max_Coloums) {
        fprintf(stderr, "ERROR: Invalid value for number of columns\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    if (fscanf(input_file, "%d", &numRobots) != 1 || numRobots < Min_Robots || numRobots > Max_Robots) {
        fprintf(stderr, "ERROR: Invalid value for number of robots\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    if (fscanf(input_file, "%d", &initTypeValue) != 1 || initTypeValue < Min_initTypeValue || initTypeValue > Max_initTypeValue) {
        fprintf(stderr, "ERROR: Invalid value for initialization type\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    if (fscanf(input_file, "%d", &initSeed) != 1 || initSeed < Min_Seed || initSeed > Max_Seed) {
        fprintf(stderr, "ERROR: Invalid value for seed\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    if (fscanf(input_file, "%d", &numTurns) != 1 || numTurns < Min_Turns || numTurns > Max_Turns) {
        fprintf(stderr, "ERROR: Invalid value for number of turns\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    if (fscanf(input_file, "%d", &interval) != 1 || interval < Min_Intervals || interval > numTurns) {
        fprintf(stderr, "ERROR: Invalid value for interval\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    // Read the output filename
    if (fscanf(input_file, "%200s", outputFilename) != 1) {
        fprintf(stderr, "ERROR: Invalid output filename\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    // Initialize the board
    int **boardpp = (int **)malloc(numRows * sizeof(int *));
    if (boardpp == NULL) {
        fprintf(stderr, "ERROR: Memory allocation failed\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < numRows; i++) {
        boardpp[i] = (int *)malloc(numCols * sizeof(int));
        if (boardpp[i] == NULL) {
            fprintf(stderr, "ERROR: Memory allocation failed\n");
            // Free allocated memory
            for (int j = 0; j < i; j++) {
                free(boardpp[j]);
            }
            free(boardpp);
            fclose(input_file);
            free(filename);
            free(outputFilename);
            exit(EXIT_FAILURE);
        }
    }

    int initResult = InitBoard(boardpp, numRows, numCols, (enum initTypeList)initTypeValue, initSeed);

    // Initialize robots and place them on the board
    struct Robot *robots = (struct Robot *)malloc(numRobots * sizeof(struct Robot));
    if (robots == NULL) {
        fprintf(stderr, "ERROR: Memory allocation failed\n");
        // Free allocated memory
        for (int i = 0; i < numRows; i++) {
            free(boardpp[i]);
        }
        free(boardpp);
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    PlaceRobots(robots, numRobots, numRows, numCols, initSeed);

    // Open output file
    FILE *outputFile = fopen(outputFilename, "w");
    if (outputFile == NULL) {
        fprintf(stderr, "ERROR: Failed to open output file.\n");
        // Free allocated memory
        for (int i = 0; i < numRows; i++) {
            free(boardpp[i]);
        }
        free(boardpp);
        free(robots);
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    // Run the game
    RunGame(robots, numRobots, numRows, numCols, numTurns, interval, outputFile, boardpp);

    // Final Step: Free allocated memory and close files
    for (int i = 0; i < numRows; i++) {
        free(boardpp[i]);
    }
    free(boardpp);
    free(robots);
    free(outputFilename);
    fclose(outputFile);
    fclose(input_file);
    free(filename);

    return 0;
}

int InitBoard(int **boardpp, int numRows, int numCols, enum initTypeList mylist, unsigned int seed) {
    switch (mylist) {
        case Random:
            InitBoardRand(boardpp, numRows, numCols, seed);
            break;
        case Checkerboard:
            InitBoardChecker(boardpp, numRows, numCols);
            break;
        case AllWhite:
            InitBoardAllWhite(boardpp, numRows, numCols);
            break;
        default:
            fprintf(stderr, "ERROR: Invalid initialization type\n");
            return -1;
        }
    return 0;
    }

void InitBoardRand(int **board, int numRows, int numCols, unsigned int seed) {
    srand(seed);
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            board[i][j] = rand() % Colours + 1; 
        }
    }
}

void InitBoardChecker(int **board, int numRows, int numCols) {
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            if ((i + j) % 2 == 0) {
                board[i][j] = White; // White
            } else {
                board[i][j] = Red; // Red
            }
        }
    }
}

void InitBoardAllWhite(int **board, int numRows, int numCols) {
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            board[i][j] = White; // White
        }
    }
}

void PlaceRobots(struct Robot *robots, int numRobots, int numRows, int numCols, unsigned int seed) {
    // Initialize the random number generator
    srand(seed);

    for (int i = 0; i < numRobots; i++) {
        // Randomly generate x and y coordinates for each robot
        robots[i].x = rand() % numCols;
        robots[i].y = rand() % numRows;

        // Randomly assign direction (1 to 4)
        robots[i].direction = rand() % Directions + 1;

        // Randomly assign paint color (1 to 4)
        robots[i].paintColour = rand() % Colours + 1;
    }
}

void RunGame(struct Robot *robots, int numRobots, int numRows, int numCols, int numTurns, int interval, FILE *outputFile, int **board) {
    // Main game loop
    for (int turn = 0; turn < numTurns; turn++) {
        printf("Turn %d\n", turn);

        // Move each robot forward and update board
        for (int i = 0; i < numRobots; i++) {
            switch (robots[i].direction) {
                case 1: // Up
                    robots[i].y = (robots[i].y - 1 + numRows) % numRows; // Ensure wraparound
                    break;
                case 2: // Right
                    robots[i].x = (robots[i].x + 1) % numCols; // Ensure wraparound
                    break;
                case 3: // Down
                    robots[i].y = (robots[i].y + 1) % numRows; // Ensure wraparound
                    break;
                case 4: // Left
                    robots[i].x = (robots[i].x - 1 + numCols) % numCols; // Ensure wraparound
                    break;
                default:
                    // Handle invalid direction
                    break;
            }

            int color = board[robots[i].y][robots[i].x];
            switch (color) {
                case 1: // White
                    robots[i].direction = (robots[i].direction + 1) % Directions;
                    break;
                case 2: // Red
                    robots[i].direction = (robots[i].direction + 2) % Directions;
                    break;
                case 3: // Green
                    robots[i].direction = (robots[i].direction + 3) % Directions;
                    break;
                case 4: // Blue
                    break; // No rotation needed for blue
            }

            // Update the board with the robot's paint color
            board[robots[i].y][robots[i].x] = robots[i].paintColour;
        }

        // Print the board state every interval turns
        if (turn % interval == 0 || turn == numTurns - 1) {
            fprintf(outputFile, "Board state at turn %d:\n", turn);
            for (int i = 0; i < numRows; i++) {
                for (int j = 0; j < numCols; j++) {
                    printf("%d ", board[i][j]);
                    fprintf(outputFile, "%d ", board[i][j]);
                }
                printf("\n");
                fprintf(outputFile, "\n");
            }
            printf("\n");
            fprintf(outputFile, "\n");
        }
    }
}

VERSION 4 (DO NOT CHANGE): 

#include <stdio.h>
#include <stdlib.h>

// Constants
const int Directions = 4;
const int Colours = 4;
const int White = 1;
const int Red = 2;

// Enumeration for initialization type
enum initTypeList { Random = 1, Checkerboard, AllWhite };

// Structure for representing robots
struct Robot {
    int x;
    int y;
    int direction;
    int paintColour;
};

// Function prototypes
int InitBoard(int **boardpp, int numRows, int numCols, enum initTypeList mylist, unsigned int seed);
void InitBoardRand(int **board, int numRows, int numCols, unsigned int seed);
void InitBoardChecker(int **board, int numRows, int numCols);
void InitBoardAllWhite(int **board, int numRows, int numCols);
void PlaceRobots(struct Robot *robots, int numRobots, int numRows, int numCols, unsigned int seed);
void RunGame(struct Robot *robots, int numRobots, int numRows, int numCols, int numTurns, int interval, FILE *outputFile, int **board);

int main() {
    // Input validation constants
    const int Max_Attempts = 5;
    const int Min_Rows = 20;
    const int Max_Rows = 300;
    const int Min_Coloums = 20;
    const int Max_Coloums = 300;
    const int Min_Robots = 1;
    const int Max_Robots = 10;
    const int Min_initTypeValue = 1;
    const int Max_initTypeValue = 3;
    const int Min_Seed = 10;
    const int Max_Seed = 32767;
    const int Min_Turns = 10;
    const int Max_Turns = 5000;
    const int Min_Intervals = 1;

    // Step 1: Read the name of the input file
    char *filename = malloc(200 * sizeof(char));
    if (filename == NULL) {
        fprintf(stderr, "ERROR: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    FILE *input_file = NULL;
    int attempts = 0;

    while (input_file == NULL && attempts < Max_Attempts) {
        printf("Enter the name of the input file: ");
        if (scanf("%255s", filename) != 1) {
            fprintf(stderr, "ERROR: Input file not opened correctly.\n");
            exit(EXIT_FAILURE);
        }

        input_file = fopen(filename, "r");
        if (input_file == NULL) {
            fprintf(stderr, "ERROR: Failed to open the input file. Attempt %d\n", attempts + 1);
            attempts++;
        }
    }

    // Check if the file was opened successfully after maximum attempts
    if (input_file == NULL) {
        fprintf(stderr, "ERROR: Failed to open the input file %d times. Terminating the program.\n", Max_Attempts);
        free(filename);
        exit(EXIT_FAILURE);
    }

    // Step 2: Read input parameters from the file
    int numRows, numCols, numRobots, initTypeValue, initSeed, numTurns, interval;
    char *outputFilename = malloc(200 * sizeof(char));
    if (outputFilename == NULL) {
        fprintf(stderr, "ERROR: Memory allocation failed\n");
        fclose(input_file);
        free(filename);
        exit(EXIT_FAILURE);
    }

    if (fscanf(input_file, "%d", &numRows) != 1 || numRows < Min_Rows || numRows > Max_Rows) {
        fprintf(stderr, "ERROR: Invalid value for number of rows\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    if (fscanf(input_file, "%d", &numCols) != 1 || numCols < Min_Coloums || numCols > Max_Coloums) {
        fprintf(stderr, "ERROR: Invalid value for number of columns\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    if (fscanf(input_file, "%d", &numRobots) != 1 || numRobots < Min_Robots || numRobots > Max_Robots) {
        fprintf(stderr, "ERROR: Invalid value for number of robots\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    if (fscanf(input_file, "%d", &initTypeValue) != 1 || initTypeValue < Min_initTypeValue || initTypeValue > Max_initTypeValue) {
        fprintf(stderr, "ERROR: Invalid value for initialization type\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    if (fscanf(input_file, "%d", &initSeed) != 1 || initSeed < Min_Seed || initSeed > Max_Seed) {
        fprintf(stderr, "ERROR: Invalid value for seed\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    if (fscanf(input_file, "%d", &numTurns) != 1 || numTurns < Min_Turns || numTurns > Max_Turns) {
        fprintf(stderr, "ERROR: Invalid value for number of turns\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    if (fscanf(input_file, "%d", &interval) != 1 || interval < Min_Intervals || interval > numTurns) {
        fprintf(stderr, "ERROR: Invalid value for interval\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    // Read the output filename
    if (fscanf(input_file, "%200s", outputFilename) != 1) {
        fprintf(stderr, "ERROR: Invalid output filename\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    // Initialize the board
    int **boardpp = (int **)malloc(numRows * sizeof(int *));
    if (boardpp == NULL) {
        fprintf(stderr, "ERROR: Memory allocation failed\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < numRows; i++) {
        boardpp[i] = (int *)malloc(numCols * sizeof(int));
        if (boardpp[i] == NULL) {
            fprintf(stderr, "ERROR: Memory allocation failed\n");
            // Free allocated memory
            for (int j = 0; j < i; j++) {
                free(boardpp[j]);
            }
            free(boardpp);
            fclose(input_file);
            free(filename);
            free(outputFilename);
            exit(EXIT_FAILURE);
        }
    }

    int initResult = InitBoard(boardpp, numRows, numCols, (enum initTypeList)initTypeValue, initSeed);

    // Initialize robots and place them on the board
    struct Robot *robots = (struct Robot *)malloc(numRobots * sizeof(struct Robot));
    if (robots == NULL) {
        fprintf(stderr, "ERROR: Memory allocation failed\n");
        // Free allocated memory
        for (int i = 0; i < numRows; i++) {
            free(boardpp[i]);
        }
        free(boardpp);
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    PlaceRobots(robots, numRobots, numRows, numCols, initSeed);

    // Open output file
    FILE *outputFile = fopen(outputFilename, "w");
    if (outputFile == NULL) {
        fprintf(stderr, "ERROR: Failed to open output file.\n");
        // Free allocated memory
        for (int i = 0; i < numRows; i++) {
            free(boardpp[i]);
        }
        free(boardpp);
        free(robots);
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    // Run the game
    RunGame(robots, numRobots, numRows, numCols, numTurns, interval, outputFile, boardpp);

    // Final Step: Free allocated memory and close files
    for (int i = 0; i < numRows; i++) {
        free(boardpp[i]);
    }
    free(boardpp);
    free(robots);
    free(outputFilename);
    fclose(outputFile);
    fclose(input_file);
    free(filename);

    return 0;
}

int InitBoard(int **boardpp, int numRows, int numCols, enum initTypeList mylist, unsigned int seed) {
    switch (mylist) {
        case Random:
            InitBoardRand(boardpp, numRows, numCols, seed);
            break;
        case Checkerboard:
            InitBoardChecker(boardpp, numRows, numCols);
            break;
        case AllWhite:
            InitBoardAllWhite(boardpp, numRows, numCols);
            break;
        default:
            fprintf(stderr, "ERROR: Invalid initialization type\n");
            return -1;
        }
    return 0;
    }

void InitBoardRand(int **board, int numRows, int numCols, unsigned int seed) {
    srand(seed);
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            board[i][j] = rand() % Colours + 1; 
        }
    }
}

void InitBoardChecker(int **board, int numRows, int numCols) {
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            if ((i + j) % 2 == 0) {
                board[i][j] = White; // White
            } else {
                board[i][j] = Red; // Red
            }
        }
    }
}

void InitBoardAllWhite(int **board, int numRows, int numCols) {
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            board[i][j] = White; // White
        }
    }
}

void PlaceRobots(struct Robot *robots, int numRobots, int numRows, int numCols, unsigned int seed) {
    // Initialize the random number generator
    srand(seed);

    for (int i = 0; i < numRobots; i++) {
        // Randomly generate x and y coordinates for each robot
        robots[i].x = rand() % numCols;
        robots[i].y = rand() % numRows;

        // Randomly assign direction (1 to 4)
        robots[i].direction = rand() % Directions + 1;

        // Randomly assign paint color (1 to 4)
        robots[i].paintColour = rand() % Colours + 1;
    }
}

void RunGame(struct Robot *robots, int numRobots, int numRows, int numCols, int numTurns, int interval, FILE *outputFile, int **board) {
    // Main game loop
    for (int turn = 0; turn < numTurns; turn++) {
        printf("Turn %d\n", turn);

        // Move each robot forward and update board
        for (int i = 0; i < numRobots; i++) {
            // Store previous position
            int prevY = robots[i].y;
            int prevX = robots[i].x;

            // Move robot forward based on direction with wraparound
            switch (robots[i].direction) {
                case 1: // Up
                    robots[i].y = (robots[i].y - 1 + numRows) % numRows;
                    break;
                case 2: // Right
                    robots[i].x = (robots[i].x + 1) % numCols;
                    break;
                case 3: // Down
                    robots[i].y = (robots[i].y + 1) % numRows;
                    break;
                case 4: // Left
                    robots[i].x = (robots[i].x - 1 + numCols) % numCols;
                    break;
                default:
                    // Handle invalid direction
                    break;
            }

            // Update the board with the robot's paint color
            board[prevY][prevX] = robots[i].paintColour;
        }

        // Update robots based on board conditions and wraparound
        for (int j = 0; j < numRobots; j++) {
            int color = board[robots[j].y][robots[j].x];
            switch (robots[j].direction) {
                case 1: // Up
                    robots[j].direction = (color == 1) ? 2 : (color == 2) ? 3 : (color == 3) ? 4 : 1;
                    break;
                case 2: // Right
                    robots[j].direction = (color == 1) ? 3 : (color == 2) ? 4 : (color == 3) ? 1 : 2;
                    break;
                case 3: // Down
                    robots[j].direction = (color == 1) ? 4 : (color == 2) ? 1 : (color == 3) ? 2 : 3;
                    break;
                case 4: // Left
                    robots[j].direction = (color == 1) ? 1 : (color == 2) ? 2 : (color == 3) ? 3 : 4;
                    break;
                default:
                    // Handle invalid direction
                    break;
            }
        }

        // Print the board state every interval turns
        if (turn % interval == 0 || turn == numTurns - 1) {
            fprintf(outputFile, "Board state at turn %d:\n", turn);
            for (int i = 0; i < numRows; i++) {
                for (int j = 0; j < numCols; j++) {
                    printf("%d ", board[i][j]);
                    fprintf(outputFile, "%d ", board[i][j]);
                }
                printf("\n");
                fprintf(outputFile, "\n");
            }
            printf("\n");
            fprintf(outputFile, "\n");
        }
    }
}

Version 5 : 
#include <stdio.h>
#include <stdlib.h>

// Constants
const int Directions = 4;
const int Colours = 4;
const int White = 1;
const int Red = 2;

// Enumeration for initialization type
enum initTypeList { Random = 1, Checkerboard, AllWhite };

// Structure for representing robots
struct Robot {
    int x;
    int y;
    int direction;
    int paintColour;
};

// Function prototypes
int InitBoard(int **boardpp, int numRows, int numCols, enum initTypeList mylist, unsigned int seed);
void InitBoardRand(int **board, int numRows, int numCols, unsigned int seed);
void InitBoardChecker(int **board, int numRows, int numCols);
void InitBoardAllWhite(int **board, int numRows, int numCols);
void PlaceRobots(struct Robot *robots, int numRobots, int numRows, int numCols, unsigned int seed);
void RunGame(struct Robot *robots, int numRobots, int numRows, int numCols, int numTurns, int interval, FILE *outputFile, int **board);

int main() {
    // Input validation constants
    const int Max_Attempts = 5;
    const int Min_Rows = 20;
    const int Max_Rows = 300;
    const int Min_Coloums = 20;
    const int Max_Coloums = 300;
    const int Min_Robots = 1;
    const int Max_Robots = 10;
    const int Min_initTypeValue = 1;
    const int Max_initTypeValue = 3;
    const int Min_Seed = 10;
    const int Max_Seed = 32767;
    const int Min_Turns = 10;
    const int Max_Turns = 5000;
    const int Min_Intervals = 1;

    // Step 1: Read the name of the input file
    char *filename = malloc(200 * sizeof(char));
    if (filename == NULL) {
        fprintf(stderr, "ERROR: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    FILE *input_file = NULL;
    int attempts = 0;

    while (input_file == NULL && attempts < Max_Attempts) {
        printf("Enter the name of the input file: ");
        if (scanf("%255s", filename) != 1) {
            fprintf(stderr, "ERROR: Input file not opened correctly.\n");
            exit(EXIT_FAILURE);
        }

        input_file = fopen(filename, "r");
        if (input_file == NULL) {
            fprintf(stderr, "ERROR: Failed to open the input file. Attempt %d\n", attempts + 1);
            attempts++;
        }
    }

    // Check if the file was opened successfully after maximum attempts
    if (input_file == NULL) {
        fprintf(stderr, "ERROR: Failed to open the input file %d times. Terminating the program.\n", Max_Attempts);
        free(filename);
        exit(EXIT_FAILURE);
    }

    // Step 2: Read input parameters from the file
    int numRows, numCols, numRobots, initTypeValue, initSeed, numTurns, interval;
    char *outputFilename = malloc(200 * sizeof(char));
    if (outputFilename == NULL) {
        fprintf(stderr, "ERROR: Memory allocation failed\n");
        fclose(input_file);
        free(filename);
        exit(EXIT_FAILURE);
    }

    if (fscanf(input_file, "%d", &numRows) != 1 || numRows < Min_Rows || numRows > Max_Rows) {
        fprintf(stderr, "ERROR: Invalid value for number of rows\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    if (fscanf(input_file, "%d", &numCols) != 1 || numCols < Min_Coloums || numCols > Max_Coloums) {
        fprintf(stderr, "ERROR: Invalid value for number of columns\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    if (fscanf(input_file, "%d", &numRobots) != 1 || numRobots < Min_Robots || numRobots > Max_Robots) {
        fprintf(stderr, "ERROR: Invalid value for number of robots\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    if (fscanf(input_file, "%d", &initTypeValue) != 1 || initTypeValue < Min_initTypeValue || initTypeValue > Max_initTypeValue) {
        fprintf(stderr, "ERROR: Invalid value for initialization type\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    if (fscanf(input_file, "%d", &initSeed) != 1 || initSeed < Min_Seed || initSeed > Max_Seed) {
        fprintf(stderr, "ERROR: Invalid value for seed\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    if (fscanf(input_file, "%d", &numTurns) != 1 || numTurns < Min_Turns || numTurns > Max_Turns) {
        fprintf(stderr, "ERROR: Invalid value for number of turns\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    if (fscanf(input_file, "%d", &interval) != 1 || interval < Min_Intervals || interval > numTurns) {
        fprintf(stderr, "ERROR: Invalid value for interval\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    // Read the output filename
    if (fscanf(input_file, "%200s", outputFilename) != 1) {
        fprintf(stderr, "ERROR: Invalid output filename\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    // Initialize the board
    int **boardpp = (int **)malloc(numRows * sizeof(int *));
    if (boardpp == NULL) {
        fprintf(stderr, "ERROR: Memory allocation failed\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < numRows; i++) {
        boardpp[i] = (int *)malloc(numCols * sizeof(int));
        if (boardpp[i] == NULL) {
            fprintf(stderr, "ERROR: Memory allocation failed\n");
            // Free allocated memory
            for (int j = 0; j < i; j++) {
                free(boardpp[j]);
            }
            free(boardpp);
            fclose(input_file);
            free(filename);
            free(outputFilename);
            exit(EXIT_FAILURE);
        }
    }

    int initResult = InitBoard(boardpp, numRows, numCols, (enum initTypeList)initTypeValue, initSeed);

    // Initialize robots and place them on the board
    struct Robot *robots = (struct Robot *)malloc(numRobots * sizeof(struct Robot));
    if (robots == NULL) {
        fprintf(stderr, "ERROR: Memory allocation failed\n");
        // Free allocated memory
        for (int i = 0; i < numRows; i++) {
            free(boardpp[i]);
        }
        free(boardpp);
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    PlaceRobots(robots, numRobots, numRows, numCols, initSeed);

    // Open output file
    FILE *outputFile = fopen(outputFilename, "w");
    if (outputFile == NULL) {
        fprintf(stderr, "ERROR: Failed to open output file.\n");
        // Free allocated memory
        for (int i = 0; i < numRows; i++) {
            free(boardpp[i]);
        }
        free(boardpp);
        free(robots);
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    // Run the game
    RunGame(robots, numRobots, numRows, numCols, numTurns, interval, outputFile, boardpp);

    // Final Step: Free allocated memory and close files
    for (int i = 0; i < numRows; i++) {
        free(boardpp[i]);
    }
    free(boardpp);
    free(robots);
    free(outputFilename);
    fclose(outputFile);
    fclose(input_file);
    free(filename);

    return 0;
}

int InitBoard(int **boardpp, int numRows, int numCols, enum initTypeList mylist, unsigned int seed) {
    switch (mylist) {
        case Random:
            InitBoardRand(boardpp, numRows, numCols, seed);
            break;
        case Checkerboard:
            InitBoardChecker(boardpp, numRows, numCols);
            break;
        case AllWhite:
            InitBoardAllWhite(boardpp, numRows, numCols);
            break;
        default:
            fprintf(stderr, "ERROR: Invalid initialization type\n");
            return -1;
        }
    return 0;
    }

void InitBoardRand(int **board, int numRows, int numCols, unsigned int seed) {
    srand(seed);
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            board[i][j] = rand() % Colours + 1; 
        }
    }
}

void InitBoardChecker(int **board, int numRows, int numCols) {
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            if ((i + j) % 2 == 0) {
                board[i][j] = White; // White
            } else {
                board[i][j] = Red; // Red
            }
        }
    }
}

void InitBoardAllWhite(int **board, int numRows, int numCols) {
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            board[i][j] = White; // White
        }
    }
}

void PlaceRobots(struct Robot *robots, int numRobots, int numRows, int numCols, unsigned int seed) {
    // Initialize the random number generator
    srand(seed);

    for (int i = 0; i < numRobots; i++) {
        // Randomly generate x and y coordinates for each robot
        robots[i].x = rand() % numCols;
        robots[i].y = rand() % numRows;

        // Randomly assign direction (1 to 4)
        robots[i].direction = rand() % Directions + 1;

        // Randomly assign paint color (1 to 4)
        robots[i].paintColour = rand() % Colours + 1;
    }
}

void RunGame(struct Robot *robots, int numRobots, int numRows, int numCols, int numTurns, int interval, FILE *outputFile, int **board) {
    // Main game loop
    for (int turn = 0; turn < numTurns; turn++) {

        // Move each robot forward and update board
        for (int i = 0; i < numRobots; i++) {
            // Store previous position
            int prevY = robots[i].y;
            int prevX = robots[i].x;

            // Move robot forward based on direction with wraparound
            switch (robots[i].direction) {
                case 1: // Up
                    robots[i].y = (robots[i].y - 1 + numRows) % numRows;
                    break;
                case 2: // Right
                    robots[i].x = (robots[i].x + 1) % numCols;
                    break;
                case 3: // Down
                    robots[i].y = (robots[i].y + 1) % numRows;
                    break;
                case 4: // Left
                    robots[i].x = (robots[i].x - 1 + numCols) % numCols;
                    break;
                default:
                    // Handle invalid direction
                    break;
            }

            // Update the board with the robot's paint color
            board[prevY][prevX] = robots[i].paintColour;
        }

        // Update robots based on board conditions and wraparound
        for (int j = 0; j < numRobots; j++) {
            int color = board[robots[j].y][robots[j].x];
            switch (robots[j].direction) {
                case 1: // Up
                    robots[j].direction = (color == 1) ? 2 : (color == 2) ? 3 : (color == 3) ? 4 : 1;
                    break;
                case 2: // Right
                    robots[j].direction = (color == 1) ? 3 : (color == 2) ? 4 : (color == 3) ? 1 : 2;
                    break;
                case 3: // Down
                    robots[j].direction = (color == 1) ? 4 : (color == 2) ? 1 : (color == 3) ? 2 : 3;
                    break;
                case 4: // Left
                    robots[j].direction = (color == 1) ? 1 : (color == 2) ? 2 : (color == 3) ? 3 : 4;
                    break;
                default:
                    // Handle invalid direction
                    break;
            }
        }

        // Print the board state every interval turns
        if (turn % interval == 0 || turn == numTurns - 1) {
            fprintf(outputFile, "Board state at turn %d:\n", turn);
            printf("Turn: %d\n", turn);
            for (int i = 0; i < numRows; i++) {
                for (int j = 0; j < numCols; j++) {
                    printf("%d ", board[i][j]);
                    fprintf(outputFile, "%d ", board[i][j]);
                }
                printf("\n");
                fprintf(outputFile, "\n");
            }
            printf("\n");
            fprintf(outputFile, "\n");
        }
    }
}