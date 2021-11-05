#include <cassert>
#include <iostream>

#include "Editor/editor_buffer.h"

int main() 
{
    EditorBuffer eb;

    char buffer[] = "asfd\n";

    eb.insertCharacters(buffer, 5);

    eb.moveCursorToStart();

    eb.deleteCharacters(2);
}

