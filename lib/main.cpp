#include <iostream>
#include <vector>
#include <iterator>

#include "notes.hpp"
#include "csv.hpp"

bool saveFolderEmpty = false;

std::vector<std::filesystem::directory_entry> getSaveFolder() {
    std::string path = canonicalize_file_name(__FILE__);
    std::vector<std::filesystem::directory_entry> files = listFiles(path);
    return files;
}

void listNotes(std::vector<std::string> &notes) {
    if (notes.empty()) {
        std::cout << "You need to add a note to list them!\n";
    } else {
        for (auto & note : notes) {
            std::cout << note << "\n";
        }
    }
}

void removeNote(std::string &temp, std::vector<std::string> &notes) {
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
}

void printSaveFolderContents() {
    std::vector<std::filesystem::directory_entry> files = getSaveFolder();
    int count = 1;
    for (const auto &file: files) {
        std::cout << count << ": " << file.path() << "\n";
        count++;
    }
    if (count == 1) {
        std::cout << "ERROR: There are no files in the save-data/ folder\n";
        saveFolderEmpty = true;
    } else {
        saveFolderEmpty = false;
    }
}

void saveToFile(std::vector<std::string> &notes) {
    if (!notes.empty()) {
        std::cout << "What would you like the file to be named?\n";
        std::string saveFolder;
        std::filesystem::directory_entry saveFolderPath = getSaveFolder()[0];
        std::vector<std::string> splitPath = pathSplitter(saveFolderPath.path());
        splitPath.pop_back();
        std::string folderAbsPath;
        for (auto & i : splitPath) {
            folderAbsPath += i, folderAbsPath += '/';
        }
        folderAbsPath += "saved-notes/";

        std::string fileName;
        std::getline(std::cin, fileName);

        fileName += ".csv";

        std::string fullFilePath = folderAbsPath + fileName;

        std::ofstream fileOut(fullFilePath);

        if (!fileOut.is_open()) {
            std::cout << "ERROR: could not write to file!\n";
        } else {
            fileOut.write("note\n", 5);
            for (auto note : notes) {
                note += "\n";
                std::string str = note;
                fileOut << str;
            }
            std::cout << "Notes list saved as " << fileName << "\n";
            fileOut.close();
        }
    } else {
        std::cout << "You need to add some notes to the list before you can save them!\n";
    }
}

void readFromFile(std::vector<std::string> &notes) {
    std::vector<std::filesystem::directory_entry> files = getSaveFolder();
    printSaveFolderContents();
    // checks if the save-data/ folder is empty
    if (saveFolderEmpty) {
        return;
    }
    int fileChoice;
    std::cout << "Which file would you like to open?\n";

    std::cin >> fileChoice;
    std::filesystem::path file = files[fileChoice - 1].path();

    // uses csv.h
    io::CSVReader<1> in(file);

    std::vector<std::string> tempVec;
    in.read_header(io::ignore_extra_column, "note");
    std::string note;
    while(in.read_row(note)){
        tempVec.push_back(note);
    }


    // empty notes vector
    for (std::string nul : notes) {
        notes.pop_back();
    }

    // pushes from file to notes vector
    for (auto & i : tempVec) {
        notes.push_back(i);
    }
}



int main() {
    std::vector<std::string> notes;
    std::string temp;
    start();

    while (true) {
        getline(std::cin, temp);
        // list notes functionality
        if (stringCleaner(temp).empty()) {
        } else if (stringCleaner(temp) == "list") {
            listNotes(notes);
            // remove from list functionality
        } else if (stringSplitter(stringCleaner(temp))[0] == "remove" &&
                   stringSplitter(stringCleaner(temp)).size() > 1) {
            removeNote(temp, notes);
        } else if (stringCleaner(temp) == "quit" || stringCleaner(temp) == "q") {
            return 0;
        } else if (stringCleaner(temp) == "save") {
            saveToFile(notes);
        } else if (stringCleaner(temp) == "open") {
            readFromFile(notes);
        } else {
            // default statement
            notes.push_back(temp);
        }
    }
}
