#pragma once

#include <string>
#include <array>
#include <iostream>
#include <vector>

struct Alternative {
    std::string text;
    bool isCorrect;
};

struct Question {
    std::string id;
    std::string question;
    std::vector<Alternative> alternatives;
};

std::ostream& operator<<(std::ostream& os, const Question& q);
const std::vector<std::string> split(std::string string, std::string sep);
const std::vector<int> inputAnswer();
std::string formatBool(bool b);
std::vector<Question> loadQuestions(std::string file);