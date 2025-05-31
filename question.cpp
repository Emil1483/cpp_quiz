#include <iostream>
#include <vector>
#include <charconv>

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