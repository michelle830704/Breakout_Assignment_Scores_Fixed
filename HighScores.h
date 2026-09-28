#pragma once
#include <string>

class HighScores {
private:
    unsigned int* scores;
    unsigned int size;
    unsigned int capacity;

public:
    HighScores();
    ~HighScores();

    HighScores(const HighScores&) = delete;
    HighScores& operator=(const HighScores&) = delete;

    void LoadFromFile(const std::string& filename);
    void SaveToFile(const std::string& filename) const;
    void AddScore(unsigned int score);
    void Draw() const;
};
