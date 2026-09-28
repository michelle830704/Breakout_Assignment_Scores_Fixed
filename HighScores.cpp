#include "HighScores.h"
#include "constant.h"
#include "Play.h"
#include <fstream>
#include <string>

HighScores::HighScores()
    : scores(new unsigned int[5]{}), size(0), capacity(5) {}

HighScores::~HighScores() {
    delete[] scores;
}

void HighScores::AddScore(unsigned int score) {
    unsigned int position = 0;
    while (position < size && scores[position] >= score) {
        ++position;
    }
    if (position >= capacity) return;
    if (size < capacity) ++size;
    for (unsigned int i = size - 1; i > position; --i) {
        scores[i] = scores[i - 1];
    }
    scores[position] = score;
}

void HighScores::LoadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) return;

    unsigned int value = 0;
    unsigned int count = 0;
    while (file >> value) ++count;
    file.clear();
    file.seekg(0);

    const unsigned int newCapacity = count > 5 ? count : 5;
    unsigned int* newScores = new unsigned int[newCapacity]{};
    delete[] scores;
    scores = newScores;
    size = 0;
    capacity = newCapacity;

    while (file >> value) AddScore(value);
}

void HighScores::SaveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    for (unsigned int i = 0; i < size; ++i) {
        file << scores[i] << '\n';
    }
}

void HighScores::Draw() const {
    Play::DrawDebugText(
        { DISPLAY_WIDTH - 110.0f, 60.0f },
        "HIGH SCORES"
    );
    for (unsigned int i = 0; i < size; ++i) {
        const std::string label = std::to_string(i + 1) + ". " + std::to_string(scores[i]);
        Play::DrawDebugText(
            { DISPLAY_WIDTH - 110.0f, 80.0f + static_cast<float>(i * 18) },
            label.c_str()
        );
    }
}
