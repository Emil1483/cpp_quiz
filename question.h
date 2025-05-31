#pragma once

#include <string>
#include <array>
#include <iostream>
#include <vector>

struct Alternative {
    std::string text;
    bool isCorrect;
};

template<int T>
struct Question {
    std::string question;
    std::array<Alternative, T> alternatives;
};

template<int T>
std::ostream& operator<<(std::ostream& os, const Question<T>& q) {
    os << q.question << "\n";
    for (int i = 0; i < q.alternatives.size(); i++) {
        auto alternative = q.alternatives.at(i);
        os << i << ". " << alternative.text << "\n";
    }
    return os;
}

const std::vector<std::string> split(std::string string, std::string sep);
const std::vector<int> inputAnswer();
std::string formatBool(bool b);