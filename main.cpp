#include <iostream>
#include <vector>
#include <iterator>

#include "lib/notes.h"


int main() {
    std::vector<std::string> notes;
    std::string temp;
    start();

    while (true) {
        getline(std::cin, temp);
        // list notes functionality
        if (stringCleaner(temp) == "list") {
            if (notes.empty()) {
                std::cout << "You need to add a note to list them!\n";
            } else {
                for (auto & note : notes) {
                    std::cout << note << "\n";
                }
            }
        // remove from list functionality
        }  else if (stringSplitter(stringCleaner(temp))[0] == "remove" &&
        stringSplitter(stringCleaner(temp)).size() > 1) {
            try {
                int num = std::stoi(stringSplitter(stringCleaner(temp))[1]);
                if (num > 0 && num <= notes.size()) {
                    notes.erase(notes.begin() + num - 1);
                } else if (notes.empty()) {
                    std::cout << "You need to have a note in the list to remove it!\n";
                } else if (num > notes.size()) {
                    std::cout << "You don't even have " << num << " notes in the list!\n";
                }
            // catches in case the first word in your note is "remove"
            } catch (std::invalid_argument&) {
                notes.push_back(temp);
            }
        // quit program functionality
        } else if (stringCleaner(temp) == "quit" || stringCleaner(temp) == "q") {
            return 0;
        } else {
            notes.push_back(temp);
        }
    }
}
