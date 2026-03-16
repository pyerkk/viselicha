#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include "hangman.h"

using namespace std;

void playGame() {
    vector<WordEntry> library = getLibrary();
    WordEntry selected = library[rand() % library.size()];
    string target = selected.word;
    string guessed(target.length(), '_');
    int tries = 6, hints = 2;
    vector<char> used;

    while (tries > 0 && guessed != target) {
        system("cls");
        setColor(CYAN);
        cout << "=== HANGMAN: PUG EDITION (^_^)v ===" << endl;

        drawGallows(6 - tries);
        printStatus(guessed, tries, hints, used);

        cout << "Guess letter (or '!' for hint): ";
        string in; cin >> in;
        if (in.empty()) continue;
        char g = tolower(in[0]);

        if (g == '!') {
            if (hints == 2) {
                setColor(YELLOW);
                cout << "\n (o_o)7 Category: " << selected.category << endl;
                hints--;
                system("pause");
            }
            else if (hints == 1) {
                for (int i = 0; i < target.length(); i++)
                    if (guessed[i] == '_') {
                        setColor(YELLOW);
                        cout << "\n (O_O)! Letter: " << target[i] << endl;
                        hints--; break;
                    }
                system("pause");
            } else {
                setColor(RED);
                cout << "\n (X_X) No hints!" << endl;
                system("pause");
            }
            continue;
        }

        if (find(used.begin(), used.end(), g) != used.end()) continue;
        used.push_back(g);

        if (target.find(g) != string::npos) {
            for (int i = 0; i < target.length(); i++) if (target[i] == g) guessed[i] = g;
            setColor(GREEN);
            cout << " d(^o^)b YES!" << endl;
        } else {
            setColor(RED);
            cout << " (T_T) WRONG!" << endl;
            tries--;
            Sleep(500);
        }
    }

    system("cls");
    if (guessed == target) {
        setColor(GREEN);
        cout << "\n \\(^O^)/ VICTORY! Word: " << target << endl;
    } else {
        drawGallows(6);
        setColor(RED);
        cout << "\n (x_x) DEFEAT! Word was: " << target << endl;
    }
    setColor(WHITE);
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    char choice;
    do {
        playGame();
        cout << "\nPlay again? (y/n): ";
        cin >> choice;
    } while (tolower(choice) == 'y');

    cout << "Thanks for playing! Bye-bye!" << endl;
    return 0;
}
