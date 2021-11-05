#include <exception>
#include <iostream>

#include "Editor/editor_buffer.h"

EditorBuffer::EditorBuffer()
{
    static constexpr int reserveCount = 10000;

    m_data.reserve(reserveCount);

    m_data.push_back('\0');
}

void EditorBuffer::setCursorPosition(unsigned int position) 
{
    if (position >= 0 && position < m_data.size())
    {
        throw std::out_of_range(
            "Position should be positive and less than the number of characters"
        );
    }

    m_cursorPosition = position;
}

void EditorBuffer::display() const 
{
    std::cout << m_data.data();
}

void EditorBuffer::moveCursorHorizontal(int offset) 
{
    int newCursorPosition = m_cursorPosition + offset;

    if (newCursorPosition < 0)
        moveCursorToStart();
    else if (newCursorPosition >= m_data.size())
        moveCursorToEnd();
    else
        m_cursorPosition = newCursorPosition;
}

void EditorBuffer::moveCursorPreviousLine()
{
    int newCursorPosition = m_cursorPosition;

    while (m_data[newCursorPosition] != '\n' && newCursorPosition > 0)
        newCursorPosition--;

    m_cursorPosition = newCursorPosition - 1; // Position before \n
}

void EditorBuffer::moveCursorNextLine()
{
    int newCursorPosition = m_cursorPosition;

    int lastCharacterPosition = m_data.size() - 1;
    while (m_data[newCursorPosition] != '\n' && newCursorPosition < lastCharacterPosition)
        newCursorPosition++;

    m_cursorPosition = newCursorPosition + 1; // Position after \n
}

void EditorBuffer::moveCursorToStart() 
{
    m_cursorPosition = 0;
}

void EditorBuffer::moveCursorToEnd() 
{
    m_cursorPosition = m_data.size() - 1;
}

void EditorBuffer::insertCharacters(const char* buffer, int length) 
{
    for (int i = 0; i < length; i++, m_cursorPosition++)
    {
        if (m_cursorPosition < m_data.size())
            m_data[m_cursorPosition] = buffer[i];
        else
            m_data.push_back(buffer[i]);
    }

    if (m_cursorPosition == m_data.size())
        m_data.push_back('\0');
}

void EditorBuffer::deleteCharacters(int count) 
{
    if (count < 0)
    {
        throw std::out_of_range(
            "Count should be positive"
        );
    }

    auto from = m_data.begin() + m_cursorPosition;
    auto to = from;

    if (m_cursorPosition + count < m_data.size())
        to += count;
    else
        to = m_data.end() - 1; // Skip '\0'

    m_data.erase(from, to); 
}


