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
