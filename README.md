# Hangman Game

This is a simple command-line Hangman game implemented in C++. The game randomly selects a word from a list and challenges the player to guess it one letter at a time. The player has a limited number of incorrect guesses before the game ends.

## Features

- Random word selection from a predefined list (`words.txt`).
- ASCII art representation of the hangman.
- Hints provided for each word.
- Input validation to ensure only single alphabetic characters are accepted.
- Detection of repeated guesses with a prompt to enter a new guess.
- Option to play multiple rounds.

## Files

- **`hangman.cpp`**: The main source code file for the Hangman game.
- **`words.txt`**: A file containing a list of words and their corresponding hints, used by the game.

### Prerequisites

- A C++ compiler (e.g., g++, clang++)
- A terminal or command prompt

### Running the Game

1. Clone the repository or download the files `hangman.cpp` and `words.txt` to your local machine.
2. Compile the `hangman.cpp` file:
   ```bash
   g++ -o hangman hangman.cpp
3. Run the game:
  ./hangman
   
## Game Instructions

The game will randomly select a word from the words.txt file.
- The word will be displayed with underscores (_) representing each letter.
- A hint for the word will be provided.
- You will be prompted to guess one letter at a time.
- If you guess a correct letter, it will be revealed in the word.
- If you guess an incorrect letter, it will be added to the list of incorrect guesses.
- You have a maximum of 6 incorrect guesses before the game ends.
- If you guess all letters correctly before reaching the maximum incorrect guesses, you win!
- After the game ends, you will be asked if you want to play again.
- Example words.txt Format
- The words.txt file should contain words and their corresponding hints, separated by a comma. Each word-hint pair should be on a new line.

## Customization

- You can customize the word list by editing the words.txt file. Each line should contain a word and its corresponding hint, separated by a comma.

## License

This project is open source and available under the MIT License.
