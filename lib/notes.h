//
// Created by sarah on 10/16/21.
//

#include <sstream>

#ifndef NOTES_APP_NOTES_H
#define NOTES_APP_NOTES_H

static std::string stringCleaner(std::string &str) {
    std::string result;
    for (char i : str) {
        result += (int8_t) std::tolower(i);
    }
    return result;
}

static std::vector<std::string> stringSplitter(const std::string& str) {
    std::string word;
    std::istringstream iss{str};

    std::vector<std::string> words{
        std::istream_iterator<std::string>{iss},
        std::istream_iterator<std::string>{}
    };
    return words;
}

void start() {
    std::cout << "Welcome to the notes app!\n\n"
                 "start typing to take a note.\n"
                 "type \"list\" to display your notes.\n"
                 "typing \"remove\" followed by the items position removes it from the list.\n"
                 "Type \"quit\" or \"q\" to finish taking notes.\n\n";
}

#endif //NOTES_APP_NOTES_H
