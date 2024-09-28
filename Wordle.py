import random

# List of possible words (you can add more)
word_list = ["apple", "grape", "lemon", "mango", "peach", "berry", "melon", "cherry", "plums"]

def choose_word():
    """Randomly chooses a word from the list."""
    return random.choice(word_list).lower()

def get_feedback(guess, secret_word):
    """Provides feedback on the guessed word."""
    feedback = []
    for i in range(len(guess)):
        if guess[i] == secret_word[i]:
            feedback.append("🟩")  # Correct letter in the correct position
        elif guess[i] in secret_word:
            feedback.append("🟨")  # Correct letter, wrong position
        else:
            feedback.append("⬛")  # Incorrect letter
    return "".join(feedback)

def valid_guess(guess):
    """Check if the guess is valid (5 letters and alphabetical)."""
    return len(guess) == 5 and guess.isalpha()

def wordle_game():
    secret_word = choose_word()
    attempts = 6
    print("\nWelcome to Wordle! Guess the 5-letter word.")
    print("-----------------------------------------")

    while attempts > 0:
        guess = input(f"\nYou have {attempts} attempts left. Enter your guess: ").lower()

        if not valid_guess(guess):
            print("Invalid input! Please enter a valid 5-letter word.")
            continue

        feedback = get_feedback(guess, secret_word)
        print("Feedback:", feedback)

        if guess == secret_word:
            print("\n🎉 Congratulations! You've guessed the word correctly!")
            break
        else:
            attempts -= 1

    if attempts == 0:
        print(f"\nSorry, you've run out of attempts. The correct word was '{secret_word}'.")

# Run the game
if __name__ == "__main__":
    wordle_game()
