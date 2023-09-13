#pragma once
#include <iostream>
#include <string.h>
using namespace std;

class MyString
{
    friend std::ostream& operator<<(std::ostream& s, const MyString& str);
public:
    MyString();
    MyString(const char* array);
    MyString(const char* array, size_t count);
    MyString(initializer_list<char> array);
    MyString(string array);
    MyString(size_t count, char symbol);
    MyString(const MyString& object);
    MyString(MyString&& object) noexcept;
    ~MyString();
    size_t size() const;
    size_t length() const;
    size_t capacity() const;
    void shrink_to_fit();
    char* c_str() const;
    const char* data() const;
    bool empty();
    void erase(size_t index, size_t count);
    void clear();
    int find(const char* string, size_t index) const;
    int find(const char* string) const;
    int find(string array, size_t index) const;
    int find(string array) const;
    void append(const char* string, size_t index, size_t count);
    void append(const char* string);
    void append(const string array);
    void append(const string array, size_t index, size_t count);
    void append(size_t count, char symbol);
    void insert(size_t index, const char* string, size_t count);
    void insert(size_t index, const char* string);
    void insert(size_t index, const string array, size_t count);
    void insert(size_t index, const string array);
    void insert(size_t index, size_t count, char symbol);
    void replace(size_t index, size_t count, const char* string);
    void replace(size_t index, size_t count, const string array);
    MyString substr(size_t index, size_t count)const;
    MyString substr(size_t index)const;
    
    MyString& operator=(const MyString& right);
    MyString& operator=(const char* right);
    MyString& operator=(const string right);
    MyString& operator=(const char right);
    MyString& operator += (const MyString& s);
    MyString& operator += (const char* s);
    MyString& operator += (const string s);

    const char& operator [] (size_t i) const;
    int lexic_compare(const MyString& right) const;
private:
    char* m_array;
    size_t m_size;
    size_t m_capacity;
    void extend(size_t count);
    
};

std::ostream& operator<<(std::ostream& s, const MyString& str);
std::istream& operator>> (std::istream& is, MyString& str);
MyString operator+(const MyString& left, const MyString& right);
MyString operator+(const MyString& left, const char* right);
MyString operator+(const MyString& left, const string right);
bool operator==(const MyString& left, const MyString& right);
bool operator!=(const MyString& left, const MyString& right);
bool operator>(const MyString& left, const MyString& right);
bool operator < (const MyString& left, const MyString& right);
bool operator>=(const MyString& left, const MyString& right);
bool operator <= (const MyString& left, const MyString& right);
