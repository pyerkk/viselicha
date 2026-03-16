#ifndef HANGMAN_H
#define HANGMAN_H

#include <string>
#include <vector>
#include <windows.h>

struct WordEntry {
    std::string word;
    std::string category;
};


enum Color { RED = 12, GREEN = 10, BLUE = 9, YELLOW = 14, WHITE = 15, CYAN = 11 };

void setColor(int color);
void drawGallows(int errors);
void printStatus(const std::string& guessed, int tries, int hints, const std::vector<char>& used);
std::vector<WordEntry> getLibrary();

#endif
