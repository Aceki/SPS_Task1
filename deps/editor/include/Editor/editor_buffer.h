#pragma once

#include <vector>

class EditorBuffer 
{
public:
    EditorBuffer();
    void display() const;
    int getCharactersCount() const;
    unsigned int getCursorPosition() const;
    void setCursorPosition(unsigned int position);
    void moveCursorPreviousLine();
    void moveCursorNextLine();
    void moveCursorHorizontal(int offset);
    void moveCursorToStart();
    void moveCursorToEnd();
    void insertCharacters(char* buffer, int length);
    void deleteCharacters(int count);
private:
    unsigned int m_cursorPosition = 0;
    std::vector<char> m_data;
};

inline int EditorBuffer::getCharactersCount() const 
{
    return m_data.size() - 1; // Because m_data always store one additional character
}

inline unsigned int EditorBuffer::getCursorPosition() const 
{
    return m_cursorPosition;
}

