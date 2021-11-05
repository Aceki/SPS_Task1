# Задание 1

Школа разработчиков. ПК. Брехунцов Н.А.

## Абстракция

```cpp
class EditorBuffer 
{
public:
    EditorBuffer();
    void display() const;
    int getCharactersCount() const;
    unsigned int getCursorPosition() const;
    void setCursorPosition(unsigned int position);
    void moveCursorHorizontal(int offset);
    void moveCursorToStart();
    void moveCursorToEnd();
    void insertCharacters(char* buffer, int length);
    void deleteCharacters(int count);
private:
    /* ... */
};
```

## Инкапсуляция

### Массив фиксированной длины

```cpp
template <std::size_t N = 10000>
class EditorBuffer 
{
public:
    EditorBuffer();
    void display() const;
    int getCharactersCount() const;
    unsigned int getCursorPosition() const;
    void setCursorPosition(unsigned int position);
    void moveCursorHorizontal(int offset);
    void moveCursorToStart();
    void moveCursorToEnd();
    void insertCharacters(char* buffer, int length);
    void deleteCharacters(int count);
private:
    unsigned int m_cursorPosition = 0;
    std::array<char, N> m_data;
};
```

|Метод|Сложность по времени|Сложность по памяти|
|--|--|--|
|setCursorPosition|O(1)|O(1)|
|moveCursorHorizontal|O(1)|O(1)|
|moveCursorToStart|O(1)|O(1)|
|moveCursorToEnd|O(1)|O(1)|
|insertCharacters|O(n)|O(1)|
|deleteCharacters|O(n)|O(1)|


### Динамически размещаемый массив

```cpp
class EditorBuffer 
{
public:
    EditorBuffer();
    void display() const;
    int getCharactersCount() const;
    unsigned int getCursorPosition() const;
    void setCursorPosition(unsigned int position);
    void moveCursorHorizontal(int offset);
    void moveCursorToStart();
    void moveCursorToEnd();
    void insertCharacters(char* buffer, int length);
    void deleteCharacters(int count);
private:
    unsigned int m_cursorPosition = 0;
    std::vector<char> m_data;
};
```

|Метод|Сложность по времени|Сложность по памяти|
|--|--|--|
|setCursorPosition|O(1)|O(1)|
|moveCursorHorizontal|O(1)|O(1)|
|moveCursorToStart|O(1)|O(1)|
|moveCursorToEnd|O(1)|O(1)|
|insertCharacters|O(n)|O(n)|
|deleteCharacters|O(n)|O(1)|


### Два стека

```cpp
class EditorBuffer 
{
public:
    EditorBuffer();
    void display() const;
    int getCharactersCount() const;
    unsigned int getCursorPosition() const;
    void setCursorPosition(unsigned int position);
    void moveCursorHorizontal(int offset);
    void moveCursorToStart();
    void moveCursorToEnd();
    void insertCharacters(char* buffer, int length);
    void deleteCharacters(int count);
private:
    unsigned int m_cursorPosition = 0;
    std::stack<char> m_data_before;
    std::stack<char> m_data_after;
};
```

|Метод|Сложность по времени|Сложность по памяти|
|--|--|--|
|setCursorPosition|O(n)|O(n)|
|moveCursorHorizontal|O(n)|O(n)|
|moveCursorToStart|O(n)|O(n)|
|moveCursorToEnd|O(n)|O(n)|
|insertCharacters|O(n)|O(n)|
|deleteCharacters|O(1)|O(1)|


### Односвязный список

```cpp
class EditorBuffer 
{
public:
    EditorBuffer();
    void display() const;
    int getCharactersCount() const;
    unsigned int getCursorPosition() const;
    void setCursorPosition(unsigned int position);
    void moveCursorHorizontal(int offset);
    void moveCursorToStart();
    void moveCursorToEnd();
    void insertCharacters(char* buffer, int length);
    void deleteCharacters(int count);
private:
    std::iterator m_cursor;
    std::forward_list<char> m_data;
};
```

|Метод|Сложность по времени|Сложность по памяти|
|--|--|--|
|setCursorPosition|O(n)|O(n)|
|moveCursorHorizontal|O(n)|O(1)|
|moveCursorToStart|O(1)|O(1)|
|moveCursorToEnd|O(1)|O(1)|
|insertCharacters|O(n)|O(n)|
|deleteCharacters|O(n)|O(1)|

### Двусвязный список

```cpp
class EditorBuffer 
{
public:
    EditorBuffer();
    void display() const;
    int getCharactersCount() const;
    unsigned int getCursorPosition() const;
    void setCursorPosition(unsigned int position);
    void moveCursorHorizontal(int offset);
    void moveCursorToStart();
    void moveCursorToEnd();
    void insertCharacters(char* buffer, int length);
    void deleteCharacters(int count);
private:
    std::iterator m_cursor;
    std::list<char> m_data;
};
```

|Метод|Сложность по времени|Сложность по памяти|
|--|--|--|
|setCursorPosition|O(n)|O(n)|
|moveCursorHorizontal|O(n)|O(1)|
|moveCursorToStart|O(1)|O(1)|
|moveCursorToEnd|O(1)|O(1)|
|insertCharacters|O(n)|O(n)|
|deleteCharacters|O(n)|O(1)|

## Реализация

```cpp
// editor_buffer.h

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
    void insertCharacters(const char* buffer, int length);
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

// editor_buffer.cpp

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
```
