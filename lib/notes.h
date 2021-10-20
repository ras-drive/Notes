//
// Created by sarah on 10/16/21.
//

#include <sstream>
#include <fstream>
#include <filesystem>
#include <iterator>
#include <vector>
#include <iostream>

#ifndef NOTES_APP_NOTES_H
#define NOTES_APP_NOTES_H

// simple function to set the strings to lowercase
static std::string stringCleaner(std::string &str) {
    std::string result;
    for (char i : str) {
        result += (int8_t) std::tolower(i);
    }
    return result;
}

// function to split the strings for the remove functionality
static std::vector<std::string> stringSplitter(const std::string &str) {
    std::istringstream iss{str};

    std::vector<std::string> words{
            std::istream_iterator<std::string>{iss},
            std::istream_iterator<std::string>{}
    };
    return words;
}

// function to introduce the user to the app
static void start() {
    std::cout << "Welcome to the notes app!\n\n"
                 "start typing to take a note.\n"
                 "type \"list\" to display your notes.\n"
                 "typing \"remove\" followed by the items position removes it from the list.\n"
                 "typing \"save\" will save to a file with the name of your choice.\n"
                 "typing \"open\" will list txt files to open, you can open by number.\n"
                 "Type \"quit\" or \"q\" to finish taking notes.\n\n";
}



static std::vector<std::string> pathSplitter(const std::string &str) {
    std::vector<std::string> pathVec;
    std::string s = str;
    std::string delimiter = "/";

    size_t pos;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        pathVec.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    return pathVec;
}

static std::vector<std::filesystem::directory_entry> listFiles(std::string &filePath) {
    std::vector<std::string> pathVec = pathSplitter(filePath);

    // rebuilds path from string down to the directory
    std::string folderPath;
    for (auto & i : pathVec) {
        folderPath += i + "/";
    }
    // default name for saved notes directory
    std::string saveFolderPath = "saved-notes/";
    saveFolderPath = folderPath + saveFolderPath;

    std::vector<std::filesystem::directory_entry> files;
    for (const auto &entry : std::filesystem::directory_iterator(saveFolderPath)) {
        files.push_back(entry);
    }
    return files;
}


#endif //NOTES_APP_NOTES_H
