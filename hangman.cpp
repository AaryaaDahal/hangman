#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <array>
#include <fstream>
#include <sstream>
#include <limits>

using namespace std;

class Hangman {
public:
    Hangman() : maxIncorrectGuesses(6) {
        srand(static_cast<unsigned int>(time(nullptr)));
        loadWordsFromFile("words.txt");
    }

    void play() {
        do {
            resetGame();
            while (incorrectGuessCount < maxIncorrectGuesses && !isWordGuessed()) {
                clearScreen();
                displayHangman();
                displayCurrentState();
                displayIncorrectGuesses();
                displayHint(); // Show hint
                handleUserGuess();
            }
            displayEndGameMessage();
        } while (askToPlayAgain());
    }

private:
    vector<string> words;
    vector<string> hints;
    string word;
    string guessedWord;
    vector<char> incorrectGuesses;
    int incorrectGuessCount;
    const int maxIncorrectGuesses;

    void loadWordsFromFile(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }
        
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string word, hint;
            if (getline(iss, word, ',') && getline(iss, hint)) {
                words.push_back(word);
                hints.push_back(hint);
            }
        }
        file.close();
    }

    void resetGame() {
        word = getRandomWord();
        guessedWord = string(word.size(), '_');
        for (size_t i = 0; i < word.size(); ++i) {
            if (word[i] == ' ') {
                guessedWord[i] = ' ';
            }
        }
        incorrectGuesses.clear();
        incorrectGuessCount = 0;
    }

    void clearScreen() const {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    void displayHangman() const {
        static const array<string, 7> hangmanStages = {
            "  +---+\n      |\n      |\n      |\n      |\n      |\n========= \n",
            "  +---+\n  O   |\n      |\n      |\n      |\n      |\n========= \n",
            "  +---+\n  O   |\n  |   |\n      |\n      |\n      |\n========= \n",
            "  +---+\n  O   |\n /|   |\n      |\n      |\n      |\n========= \n",
            "  +---+\n  O   |\n /|\\  |\n      |\n      |\n      |\n========= \n",
            "  +---+\n  O   |\n /|\\  |\n /    |\n      |\n      |\n========= \n",
            "  +---+\n  O   |\n /|\\  |\n / \\  |\n      |\n      |\n========= \n"
        };
        cout << hangmanStages[incorrectGuessCount] << endl;
    }

    void displayCurrentState() const {
        cout << "Current word: ";
        for (char c : guessedWord) {
            cout << c << ' ';
        }
        cout << endl;
    }

    void displayIncorrectGuesses() const {
        cout << "Incorrect guesses: ";
        for (char guess : incorrectGuesses) {
            cout << guess << ' ';
        }
        cout << endl;
    }

    void displayHint() const {
        auto it = find(words.begin(), words.end(), word);
        if (it != words.end()) {
            size_t index = distance(words.begin(), it);
            cout << "Hint: " << hints[index] << endl;
        }
    }

    void handleUserGuess() {
        while (true) {
            cout << "Enter your guess: ";
            string input;
            cin >> input;

            // Check if input is a single character and alphabetic
            if (input.length() != 1 || (!isalpha(input[0]) && input[0] != ' ')) {
                cout << "Invalid input. Please enter a single alphabetic character or a space." << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the input buffer
                continue;  // Prompt for input again
            }

            char guess = tolower(input[0]);

            // Check if the letter has already been guessed
            if (find(incorrectGuesses.begin(), incorrectGuesses.end(), guess) != incorrectGuesses.end() || 
                guessedWord.find(guess) != string::npos) {
                cout << "You've already guessed that letter. Try again." << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the input buffer
                continue;  // Prompt for input again
            }

            // Process the valid guess
            if (isGuessCorrect(guess)) {
                updateGuessedWord(guess);
            } else {
                incorrectGuesses.push_back(guess);
                ++incorrectGuessCount;
            }
            
            break;  // Exit the loop if the guess was valid
        }
    }

    bool isGuessCorrect(char guess) const {
        return word.find(guess) != string::npos;
    }

    void updateGuessedWord(char guess) {
        for (size_t i = 0; i < word.size(); ++i) {
            if (word[i] == guess) {
                guessedWord[i] = guess;
            }
        }
    }

    bool isWordGuessed() const {
        return guessedWord.find('_') == string::npos;
    }

    string getRandomWord() const {
        return words[rand() % words.size()];
    }

    void displayEndGameMessage() const {
        clearScreen();
        displayHangman();
        if (isWordGuessed()) {
            cout << "Congratulations! You guessed the word: " << word << endl;
        } else {
            cout << "Sorry, you've run out of guesses. The word was: " << word << endl;
        }
    }

    bool askToPlayAgain() const {
        while (true) {
            cout << "Do you want to play again? (y/n): ";
            char response;
            cin >> response;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the input buffer

            if (response == 'y' || response == 'Y') {
                return true;
            } else if (response == 'n' || response == 'N') {
                return false;
            } else {
                cout << "Invalid response. Please enter 'y' or 'n'." << endl;
            }
        }
    }
};

int main() {
    Hangman game;
    game.play();
    return 0;
}
