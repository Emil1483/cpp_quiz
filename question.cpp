#include <iostream>
#include <vector>
#include <charconv>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>

#include "question.h"

const std::vector<std::string> split(std::string string, std::string sep) {
    std::vector<std::string> result{};

    int i = string.find(sep);
    if (i == -1) {
        result.push_back(string);
        return result;
    }

    result.push_back(string.substr(0, i));

    const auto right = split(string.substr(i + sep.length()), sep);
    for (const std::string el : right) {
        result.push_back(el);
    }

    return result;
}

const std::vector<int> inputAnswer() {
    std::cout << "hvilke(t) alternativ er riktig? ";
    std::string answer;
    std::vector<int> answerInts;
    std::cin >> answer;
    for (const auto part : split(answer, ",")) {
        int integer{};
        auto [ptr, ec] = std::from_chars(part.data(), part.data() + part.size(), integer);

        if (ec == std::errc())
            answerInts.push_back(integer);
        else if (ec == std::errc::invalid_argument) {
            std::cout << part << " Er ikke et tall!\n";
            return inputAnswer();
        } else if (ec == std::errc::result_out_of_range) {
            std::cout << "Dette tallet er større enn en int.\n";
            return inputAnswer();
        }
    }
    return answerInts;
}

std::string formatBool(bool b) {
    return b ? "korrekt" : "feil";
}

std::ostream& operator<<(std::ostream& os, const Question& q) {
    os << q.question << "\n";
    for (int i = 0; i < q.alternatives.size(); i++) {
        auto alternative = q.alternatives.at(i);
        os << i << ". " << alternative.text << "\n";
    }
    return os;
}

std::vector<Question> loadQuestions(std::string file) {
    std::vector<Question> result{};

    std::ifstream istrm(file, std::ios::binary);
    if (!istrm.is_open()) {
        throw std::runtime_error("Could not open file " + file);
    }

    std::string line{};
    std::getline(istrm, line); // Ignore the header line
    while (std::getline(istrm, line)) {
        std::stringstream lineStream(line);

        std::string id,question;
        std::getline(lineStream, id, ',');
        std::getline(lineStream, question, ',');

        std::vector<Alternative> alternatives{};
        std::string text, correct;
        while (std::getline(lineStream, text, ',')) {
            std::getline(lineStream, correct, ',');
            alternatives.emplace_back(Alternative{text, correct == "true"});
        }

        int i = question.find("{n}");
        while (i != -1) {
            question = question.replace(i, 3, "\n");
            i = question.find("{n}");
        }

        result.emplace_back(Question{id, question, alternatives});
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(result.begin(), result.end(), gen);

    return result;
}