#include <string>
#include <iostream>
#include <cctype>

#include "Editor/editor_buffer.h"

using namespace std;

void executeCommand(EditorBuffer & buffer, string line);

int main() 
{
    EditorBuffer buffer;

    while (true) {
        cout << "> ";

        string cmd;
        getline(cin, cmd);

        if (cmd != "") 
            executeCommand(buffer, cmd);

        buffer.display();

        cout << endl;
    }

    return 0;
}

void executeCommand(EditorBuffer & buffer, string line) 
{
    char command = toupper(line[0]);
    string data = line.substr(1, line.length() - 1);
    switch (command) 
    {
        case 'I': buffer.insertCharacters(data.c_str(), data.length());
            break;
        case 'D': buffer.deleteCharacters(1); break;
        case 'F': buffer.moveCursorHorizontal(1); break;
        case 'B': buffer.moveCursorHorizontal(-1); break;
        case 'J': buffer.moveCursorToStart(); break;
        case 'E': buffer.moveCursorToEnd(); break;
        case 'Q': exit(0);
        default: cout << "Illegal command" << endl; break;
    }
}

