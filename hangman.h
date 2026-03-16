#ifndef HANGMAN_H
#define HANGMAN_H

#include <string>
#include <vector>

struct WordEntry {
    std::string word;
    std::string category;
};


void drawGallows(int errors);
void printStatus(const std::string& guessed, int tries, int hints, const std::vector<char>& used);
std::vector<WordEntry> getLibrary();

#endif