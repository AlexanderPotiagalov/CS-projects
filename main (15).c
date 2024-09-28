/* Robots : Game 2 */
/* Alexander Potiagalov (301586871) */
/* February 27th, 2024 */

#include <stdio.h>
#include <stdlib.h>

/* Global Constants used throughout the code */
const int Directions = 4;
const int Colours = 4;
const int White = 1;
const int Red = 2;

/* Enumeration for initialization type */
enum initTypeList { Random = 1, Checkerboard, AllWhite };

/* Structure for representing robots */
struct Robot {
    int x;
    int y;
    int direction;
    int paintColour;
};

/* Function prototypes */
int InitBoard(int **boardpp, int numRows, int numCols, enum initTypeList mylist, unsigned int seed);
void InitBoardRand(int **board, int numRows, int numCols, unsigned int seed);
void InitBoardChecker(int **board, int numRows, int numCols);
void InitBoardAllWhite(int **board, int numRows, int numCols);
void PlaceRobots(struct Robot *robots, int numRobots, int numRows, int numCols, unsigned int seed);
void RunGame(struct Robot *robots, int numRobots, int numRows, int numCols, int numTurns, int interval, FILE *outputFile, int **board);

/* Main function */
int main() {
    /* constants specific for this function */
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

    /* Step 1: Read the name of the input file */
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
            fprintf(stderr, "ERROR: Failed to open the input file correctly. Attempt %d\n", attempts + 1);
            attempts++;
        }
    }

    /* Check if the file was opened successfully after maximum attempts */
    if (input_file == NULL) {
        fprintf(stderr, "ERROR: Failed to open the input file %d times. Terminating the program.\n", Max_Attempts);
        free(filename);
        exit(EXIT_FAILURE);
    }

    /* Step 2: Read input parameters from the file */
    int numRows, numCols, numRobots, initTypeValue, initSeed, numTurns, interval;
    char *outputFilename = malloc(200 * sizeof(char));
    if (outputFilename == NULL) {
        fprintf(stderr, "ERROR: Memory allocation failed\n");
        fclose(input_file);
        free(filename);
        exit(EXIT_FAILURE);
    }

    if (fscanf(input_file, "%d", &numRows) != 1 || numRows < Min_Rows || numRows > Max_Rows) {
        fprintf(stderr, "ERROR: The number of rows was not in the input file (reached eof) \n");
        fprintf(stderr, "ERROR: The number of rows could not be read due to corrupt data in the file  \n");
        fprintf(stderr, "ERROR: The number of rows was outside the specified range (20 to 300 inclusive)  \n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    if (fscanf(input_file, "%d", &numCols) != 1 || numCols < Min_Coloums || numCols > Max_Coloums) {
        fprintf(stderr, "ERROR: The number of columns was not in the input file (reached eof) \n");
        fprintf(stderr, "ERROR: The number of columns could not be read due to corrupt data in the file\n");
        fprintf(stderr, "ERROR: The number of columns was outside the specified range (20 to 300 inclusive) \n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    if (fscanf(input_file, "%d", &numRobots) != 1 || numRobots < Min_Robots || numRobots > Max_Robots) {
        fprintf(stderr, "ERROR: The number of robots was not in the input file (reached eof) \n");
        fprintf(stderr, "ERROR: The number of robots could not be read due to corrupt data in the file \n");
        fprintf(stderr, "ERROR: The number of robots was outside the specified range (1 to 10 inclusive) \n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    if (fscanf(input_file, "%d", &initTypeValue) != 1 || initTypeValue < Min_initTypeValue || initTypeValue > Max_initTypeValue) {
        fprintf(stderr, "ERROR: The initTypeValue was not in the input file (reached eof) \n");
        fprintf(stderr, "ERROR: The initTypeValue could not be read due to corrupt data in the file \n");
        fprintf(stderr, "ERROR: The initTypeValue was outside the specified range (1 to 3 inclusive) \n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    if (fscanf(input_file, "%d", &initSeed) != 1 || initSeed < Min_Seed || initSeed > Max_Seed) {
        fprintf(stderr, "ERROR: The initSeed was not in the input file (reached eof) \n");
        fprintf(stderr, "ERROR: The initSeed could not be read due to corrupt data in the file \n");
        fprintf(stderr, "ERROR: The initSeed was outside the specified range (10 to 32767 inclusive) \n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    if (fscanf(input_file, "%d", &numTurns) != 1 || numTurns < Min_Turns || numTurns > Max_Turns) {
        fprintf(stderr, "ERROR: The number of turns was not in the input file (reached eof) \n");
        fprintf(stderr, "ERROR: The number of turns could not be read due to corrupt data in the file \n");
        fprintf(stderr, "ERROR: The number of turns was outside the specified range (10 to 5000 inclusive) \n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    if (fscanf(input_file, "%d", &interval) != 1 || interval < Min_Intervals || interval > numTurns) {
        fprintf(stderr, "ERROR: The number of intervals was not in the input file (reached eof) \n");
        fprintf(stderr, "ERROR: The number of intervals could not be read due to corrupt data in the file \n");
        fprintf(stderr, "ERROR: The number of intervals was outside the specified range (1 to 5000 inclusive) \n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    /* Read the output filename */
    if (fscanf(input_file, "%200s", outputFilename) != 1) {
        fprintf(stderr, "ERROR: Invalid output filename\n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    /* Step 3 : Initiliaze the boards */
    /* Initialization of the board */
    int **boardpp = (int **)malloc(numRows * sizeof(int *));
    if (boardpp == NULL) {
        fprintf(stderr, "ERROR: array of pointers for 2-D array could not be allocated \n");
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < numRows; i++) {
        boardpp[i] = (int *)malloc(numCols * sizeof(int));
        if (boardpp[i] == NULL) {
            fprintf(stderr, "ERROR: Array storage could not be allocated \n");
            /* Free allocated memory */
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
    
    /* Type of board */
    int initResult = InitBoard(boardpp, numRows, numCols, (enum initTypeList)initTypeValue, initSeed);

    /* Dynamically allocate one 1-D array of structures of length numRobots */
    struct Robot *robots = (struct Robot *)malloc(numRobots * sizeof(struct Robot));
    if (robots == NULL) {
        fprintf(stderr, "ERROR: Memory allocation failed\n");
        /* Free allocated memory */
        for (int i = 0; i < numRows; i++) {
            free(boardpp[i]);
        }
        free(boardpp);
        fclose(input_file);
        free(filename);
        free(outputFilename);
        exit(EXIT_FAILURE);
    }

    /* Place robots on board */
    PlaceRobots(robots, numRobots, numRows, numCols, initSeed);

    /* Open output file */
    FILE *outputFile = fopen(outputFilename, "w");
    if (outputFile == NULL) {
        fprintf(stderr, "ERROR: Failed to open output file.\n");
        /* Free allocated memory */
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

    /* Run the game */
    RunGame(robots, numRobots, numRows, numCols, numTurns, interval, outputFile, boardpp);

    /* Final Step: Free allocated memory and close files */
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

/* Step 4: */
/* Function InitBoard */
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
            fprintf(stderr, "ERROR: Invalid InitBoard type\n");
            return -1;
        }
    return 0;
    }

/* Function InitBoardRand */
void InitBoardRand(int **board, int numRows, int numCols, unsigned int seed) {
    srand(seed);
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            board[i][j] = rand() % Colours + 1; 
        }
    }
}

/* Function InitBoardChecker */
void InitBoardChecker(int **board, int numRows, int numCols) {
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            if ((i + j) % 2 == 0) {
                board[i][j] = White; /* White */
            } else {
                board[i][j] = Red; /* Red */
            }
        }
    }
}

/* Function InitBoardAllWhite */
void InitBoardAllWhite(int **board, int numRows, int numCols) {
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            board[i][j] = White; /* White */
        }
    }
}

/* Step 5: */
/* Function PlaceRobots */
void PlaceRobots(struct Robot *robots, int numRobots, int numRows, int numCols, unsigned int seed) {
    /* Initialize the random number generator */
    srand(seed);

    for (int i = 0; i < numRobots; i++) {
        /* Randomly generate x and y coordinates for each robot */
        robots[i].x = rand() % numCols;
        robots[i].y = rand() % numRows;

        /* Randomly assign direction (1 to 4) */
        robots[i].direction = rand() % Directions + 1;

        /* Randomly assign colour (1 to 4) */
        robots[i].paintColour = rand() % Colours + 1;
    }
}

/* Step 6: Function RunGame */
void RunGame(struct Robot *robots, int numRobots, int numRows, int numCols, int numTurns, int interval, FILE *outputFile, int **board) {
    /* Main game loop */
    for (int turn = 0; turn < numTurns; turn++) {

        /* Move each robot forward and update board */
        for (int i = 0; i < numRobots; i++) {
            /* Store previous position */
            int prevY = robots[i].y;
            int prevX = robots[i].x;

            /* Move robot forward based on direction with wraparound */
            switch (robots[i].direction) {
                case 1: /* Up */
                    robots[i].y = (robots[i].y - 1 + numRows) % numRows;
                    break;
                case 2: /* Right */
                    robots[i].x = (robots[i].x + 1) % numCols;
                    break;
                case 3: /* Down */
                    robots[i].y = (robots[i].y + 1) % numRows;
                    break;
                case 4: /* Left */
                    robots[i].x = (robots[i].x - 1 + numCols) % numCols;
                    break;
                default:
                    /* Invalid direction */
                    break;
            }

            /* Update the board with the robot's paint color */
            board[prevY][prevX] = robots[i].paintColour;
        }

        /* Update robots based on board conditions and wraparound */
        for (int j = 0; j < numRobots; j++) {
            int color = board[robots[j].y][robots[j].x];
            switch (robots[j].direction) {
                case 1: /* Up */
                    robots[j].direction = (color == 1) ? 2 : (color == 2) ? 3 : (color == 3) ? 4 : 1;
                    break;
                case 2: /* Right */
                    robots[j].direction = (color == 1) ? 3 : (color == 2) ? 4 : (color == 3) ? 1 : 2;
                    break;
                case 3: /* Down */
                    robots[j].direction = (color == 1) ? 4 : (color == 2) ? 1 : (color == 3) ? 2 : 3;
                    break;
                case 4: /* Left */
                    robots[j].direction = (color == 1) ? 1 : (color == 2) ? 2 : (color == 3) ? 3 : 4;
                    break;
                default:
                    /* Invalid direction */
                    break;
            }
        }

        /* Step 7 : */
        /* Print the board state at every interval turn, original state and final state */
        if (turn % interval == 0 || turn == numTurns - 1) {
            fprintf(outputFile, "Turn: %d:\n", turn);
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