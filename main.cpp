#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include "hangman.h"

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(0)));

    vector<WordEntry> library = getLibrary();
    WordEntry selected = library[rand() % library.size()];
    string targetWord = selected.word;
    string guessedWord(targetWord.length(), '_');

    int tries = 6;
    int hintsLeft = 2;
    vector<char> usedLetters;

    cout << "===========================================" << endl;
    cout << "   HANGMAN: MODULAR EDITION (^_^)v   " << endl;
    cout << "===========================================" << endl;

    while (tries > 0 && guessedWord != targetWord) {
        drawGallows(6 - tries);
        printStatus(guessedWord, tries, hintsLeft, usedLetters);

        cout << "Guess a letter (or '!' for hint): ";
        string input;
        cin >> input;
        if (input.empty()) continue;
        char guess = tolower(input[0]);

        if (guess == '!') {
            if (hintsLeft == 2) {
                cout << " (o_o)7 HINT 1 (Category): " << selected.category << endl;
                hintsLeft--;
            } else if (hintsLeft == 1) {
                for (int i = 0; i < targetWord.length(); i++) {
                    if (guessedWord[i] == '_') {
                        cout << " (O_O)! HINT 2 (Letter): Try '" << targetWord[i] << "'" << endl;
                        hintsLeft--;
                        break;
                    }
                }
            } else {
                cout << " (X_X) No more hints!" << endl;
            }
            continue;
        }

        if (find(usedLetters.begin(), usedLetters.end(), guess) != usedLetters.end()) {
            cout << " (-_-) Already tried that!" << endl;
            continue;
        }

        usedLetters.push_back(guess);

        if (targetWord.find(guess) != string::npos) {
            for (int i = 0; i < targetWord.length(); i++) {
                if (targetWord[i] == guess) guessedWord[i] = guess;
            }
            cout << " d(^o^)b YES!" << endl;
        } else {
            cout << " (T_T) WRONG!" << endl;
            tries--;
        }
    }

    if (guessedWord == targetWord) {
        cout << "\n \\(^O^)/ VICTORY! The word was: " << targetWord << endl;
    } else {
        drawGallows(6);
        cout << "\n (x_x) GAME OVER. The word was: " << targetWord << endl;
    }

    return 0;
}
