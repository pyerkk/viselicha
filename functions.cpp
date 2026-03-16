#include "hangman.h"
#include <iostream>
#include <vector>

using namespace std;

void drawGallows(int errors) {
    cout << "\n  _______" << endl;
    cout << "  |     |" << endl;
    cout << "  |     " << (errors > 0 ? "O" : "") << endl;
    cout << "  |    " << (errors > 2 ? "/" : " ") << (errors > 1 ? "|" : "") << (errors > 3 ? "\\" : "") << endl;
    cout << "  |    " << (errors > 4 ? "/" : "") << " " << (errors > 5 ? "\\" : "") << endl;
    cout << " _|_" << endl;
}

void printStatus(const string& guessed, int tries, int hints, const vector<char>& used) {
    cout << "\nWord: " << guessed << endl;
    cout << "Tries left: " << tries << " | Hints: " << hints << endl;
    cout << "Used: ";
    for (char c : used) cout << c << " ";
    cout << "\n----------------------------" << endl;
}

vector<WordEntry> getLibrary() {
    return {
            {"algorithm", "Math & CS step-by-step"}, {"binary", "System of 0s and 1s"},
            {"jupiter", "The gas giant planet"}, {"galaxy", "A huge collection of stars"},
            {"elephant", "A gray mammal with a trunk"}, {"crocodile", "Sharp-toothed river reptile"},
            {"lasagna", "Layered pasta with cheese"}, {"hamburger", "Beef patty in a bun"},
            {"architect", "One who designs buildings"}, {"dentist", "A specialist for your smile"},
            {"guitar", "String instrument for rock"}, {"jazz", "Saxophone music style"},
            {"avalanche", "Snow falling from mountains"}, {"tornado", "Spinning wind storm"},
            {"physics", "Science of matter and energy"}, {"microscope", "Used to see tiny bacteria"},
            {"submarine", "Underwater naval vessel"}, {"umbrella", "Keeps you dry in London"},
            {"paradigm", "A standard model or pattern"}, {"nostalgia", "Longing for the good old days"}
    };
}
