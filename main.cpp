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
    std::string clipboard;

public:
    // Constructor to initialize the text editor with one empty line
    TextEditor() {
        lines.push_back(Line()); // Initialize with one empty line.
        cursorLine = 0;
        cursorIndex = 0;
    }

    void appendText(const std::string &text) {
        undoStack.push_back(lines);
        lines[cursorLine].data.insert(cursorIndex, text);
        cursorIndex += text.length();
    }

    void startNewLine() {
        undoStack.push_back(lines);
        cursorLine++;
        lines.insert(lines.begin() + cursorLine, Line());
        cursorIndex = 0;
    }

    void deleteText(size_t line, size_t index, size_t length) {
        undoStack.push_back(lines);
        if (line < lines.size() && index < lines[line].data.length()) {
            lines[line].data.erase(index, length);
            cursorLine = line;
            cursorIndex = index;
        }
    }

    void undo() {
        if (!undoStack.empty()) {
            redoStack.push_back(lines);
            lines = undoStack.back();
            undoStack.pop_back();
        }
    }

    void redo() {
        if (!redoStack.empty()) {
            undoStack.push_back(lines);
            lines = redoStack.back();
            redoStack.pop_back();
        }
    }

    void cut(size_t line, size_t index, size_t length) {
        if (line < lines.size() && index < lines[line].data.length()) {
            clipboard = lines[line].data.substr(index, length);
            lines[line].data.erase(index, length);
            cursorLine = line;
            cursorIndex = index;
        }
    }

    void copy(size_t line, size_t index, size_t length) {
        if (line < lines.size() && index < lines[line].data.length()) {
            clipboard = lines[line].data.substr(index, length);
        }
    }

    void paste() {
        undoStack.push_back(lines);
        lines[cursorLine].data.insert(cursorIndex, clipboard);
        cursorIndex += clipboard.length();
    }

    void insertWithReplacement(size_t line, size_t index, const std::string &text) {
        undoStack.push_back(lines);
        if (line < lines.size() && index < lines[line].data.length()) {
            lines[line].data.replace(index, text.length(), text);
            cursorLine = line;
            cursorIndex = index;
        }
    }

    void print() const {
        for (const Line& line : lines) {
            std::cout << line.data << std::endl;
        }
    }
};

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
        std::cout << "7| Cut" << std::endl;
        std::cout << "8| Copy" << std::endl;
        std::cout << "9| Paste" << std::endl;
        std::cout << "10| Insert with replacement" << std::endl;

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

            case 2:{
                textEditor.startNewLine();}
                break;

            case 3: {
                std::cout << "Choose line, index, and number of symbols to delete: ";
                size_t line, index, length;
                std::cin >> line >> index >> length;
                textEditor.deleteText(line, index, length);
            }
                break;

            case 4: {
                textEditor.undo();
            }
                break;

            case 5: {
                textEditor.redo();
            }
                break;

            case 6: {
                std::cout << "Current text:" << std::endl;
                textEditor.print();
            }
                break;

            case 7: {
                std::cout << "Choose line, index, and number of symbols to cut: ";
                size_t line, index, length;
                std::cin >> line >> index >> length;
                textEditor.cut(line, index, length);
            }
                break;

            case 8: {
                std::cout << "Choose line, index, and number of symbols to copy: ";
                size_t line, index, length;
                std::cin >> line >> index >> length;
                textEditor.copy(line, index, length);
            }
                break;

            case 9: {
                textEditor.paste();
            }
                break;

            case 10: {
                std::cout << "Choose line and index: ";
                size_t line, index;
                std::cin >> line >> index;
                std::cout << "Write text: ";
                std::string replacementText;
                std::cin.ignore();
                std::getline(std::cin, replacementText);
                textEditor.insertWithReplacement(line, index, replacementText);
            }
                break;


            default: {
                std::cout << "The command is not chosen." << std::endl;
            }
                break;
        }
    }

    return 0;
}
