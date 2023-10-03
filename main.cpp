#include <iostream>
#include <vector>
#include <string>


class Line {
public:
    std::string data;
};
//'std::cin' is employed to get the integer type data from the user
class TextEditor {
private:
    std::vector<Line> lines;
    size_t cursorLine;
    size_t cursorIndex;
    std::vector<std::vector<Line>> undoStack;
    std::vector<std::vector<Line>> redoStack;

public:
    // Constructor to initialize the text editor with one empty line
    TextEditor() {
        lines.push_back(Line()); // Initialize with one empty line.
        cursorLine = 0;
        cursorIndex = 0;
    }

    void appendText(const std::string& text) {
        undoStack.push_back(lines);
        lines[cursorLine].data.insert(cursorIndex, text);
        cursorIndex += text.length();
    }


int main() {
    TextEditor textEditor;
    while (true) {
        std::cout << "Choose the command:" << std::endl;
        std::cout << "1| Append text symbols to the end" << std::endl;
        std::cout << "2| Start a new line" << std::endl;
        std::cout << "3| Delete text" << std::endl;
        std::cout << "4| Undo" << std::endl;
        std::cout << "5| Redo" << std::endl;
        std::cout << "6| Print the current text to console" << std::endl;

        int command = 2;
        std::cin >> command;

        switch (command) {
            case 1:{
                std::cout << "Enter text to append: ";
                std::string appendText;
                std::cin.ignore();
                std::getline(std::cin, appendText);
                textEditor.appendText(appendText);}
                break;


            default: {
                std::cout << "The command is not chosen." << std::endl;
            }
                break;
        }
    }

    return 0;
}

