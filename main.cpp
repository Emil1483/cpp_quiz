#include <vector>
#include <iostream>
#include <memory>
#include <map>
#include <cassert>
#include <charconv>
#include <iomanip>
#include <iostream>
#include <optional>
#include <string_view>
#include <system_error>
#include <algorithm>  // for std::find

#include "question.h"

int main() {
    Question<4> questions[] = {
        {
            "test question1",
            {
                Alternative{
                    "test alternative 1",
                    false,
                },
                Alternative{
                    "test alternative 2",
                    false,
                },
                Alternative{
                    "test alternative 3",
                    true,
                },
                Alternative{
                    "test alternative 4",
                    true,
                },
            },
        },
        {
            "test question2",
            {
                Alternative{
                    "test alternative 1",
                    false,
                },
                Alternative{
                    "test alternative 2",
                    false,
                },
                Alternative{
                    "test alternative 3",
                    true,
                },
                Alternative{
                    "test alternative 4",
                    true,
                },
            },
        },
    };


    for (const auto question : questions) {
        std::cout << questions[0];

        const auto input = inputAnswer();

        int score = 0;
        const int numAlts = questions[0].alternatives.size();
        for (int i = 0; i < numAlts; i++) {
            const auto alt = questions[0].alternatives.at(i);
            const auto found = std::find(input.begin(), input.end(), i) != input.end();
            if (alt.isCorrect != found) {
                std::cout << alt.text << " Var " << formatBool(alt.isCorrect)
                        << ", men du du skrev at den var "
                        << formatBool(found) << "\n";
            } else {
                score += 1;
            }
        }

        std::cout << "Du fikk " << score << "/" << numAlts << " riktig!\n";
    }

    std::cout << "Takk for at du spilte med meg!\n";

    return 0;
}
