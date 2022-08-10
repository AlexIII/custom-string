/*
 *      Custom String
 *      Author: AlexIII
 *
 *      Note.
 *      In this implementation, the memory is allocated with the c-style
 *      malloc() and free() in order to make use of the realloc() function.
 */

#include "custom_string.h"
#include <cstring>
#include <cstdlib>
#include <new>
#include <cctype>

using namespace Custom;
using std::strlen, std::strcpy, std::strcat, std::strcmp;
using std::malloc, std::realloc, std::free;

/* Constructors */

String::String() noexcept : _str(nullptr), _size(0) { }
String::String(const char *str) {
    _size = strlen(str);
    _str = static_cast<char *>(malloc((_size + 1) * sizeof(char)));
    if(!_str) throw std::bad_alloc();
    strcpy(_str, str);
}
String::String(const String &str) {
    _size = str._size;
    _str = static_cast<char *>(malloc((_size + 1) * sizeof(char)));
    if(!_str) throw std::bad_alloc();
    strcpy(_str, str._str);
}
String::String(String &&str) noexcept : _str(str._str), _size(str._size) {
    str._str = nullptr;
    str._size = 0;
}
String::~String() noexcept {
    free(_str);
    _str = nullptr;
}

/* Assignments */ 

String &String::operator=(const String &str) {
    if (this == &str) return *this;
    _size = str._size;
    _str = static_cast<char *>(realloc(_str, (_size + 1) * sizeof(char)));
    if(!_str) throw std::bad_alloc();
    strcpy(_str, str._str);
    return *this;
}
String &String::operator+=(const String &str) {
    _size += str._size;
    _str = static_cast<char *>(realloc(_str, (_size + 1) * sizeof(char)));
    if(!_str) throw std::bad_alloc();
    strcat(_str, str._str);
    return *this;
}

/* Access */ 

char &String::operator[](size_t index) noexcept {
    return _str[index];
}
const char &String::operator[](size_t index) const noexcept {
    return _str[index];
}
char &String::back() noexcept {
    return _str[_size - 1];
}
const char &String::back() const noexcept {
    return _str[_size - 1];
}
char &String::front() noexcept {
    return _str[0];
}
const char &String::front() const noexcept {
    return _str[0];
}

/* Conversion */

String::operator const char *() const noexcept {
    return _str;
}
const char *String::c_str() const noexcept {
    return _str;
}

/* Comparison */ 

int String::compare(const String &str) const noexcept {
    return strcmp(_str, str._str);
}
bool String::operator==(const String &str) const noexcept {
    return compare(str) == 0;
}
bool String::operator!=(const String &str) const noexcept {
    return compare(str) != 0;
}
bool String::operator<(const String &str) const noexcept {
    return compare(str) < 0;
}
bool String::operator>(const String &str) const noexcept {
    return compare(str) > 0;
}
bool String::operator<=(const String &str) const noexcept {
    return compare(str) <= 0;
}
bool String::operator>=(const String &str) const noexcept {
    return compare(str) >= 0;
}

/* Misc */ 

size_t String::length() const noexcept {
    return _size;
}
bool String::empty() const noexcept {
    return _size == 0;
}

String &String::toLower() noexcept {
    for (size_t i = 0; i < _size; i++)
        _str[i] = tolower(_str[i]);
    return *this;
}
String &String::toUpper() noexcept {
    for (size_t i = 0; i < _size; i++)
        _str[i] = toupper(_str[i]);
    return *this;
}
String String::asLower() const {
    String str(*this);
    str.toLower();
    return str;
}
String String::asUpper() const {
    String str(*this);
    str.toUpper();
    return str;
}

/* External operators */ 

String Custom::operator+(const String &str1, const String &str2) {
    String str;
    str._size = str1._size + str2._size;
    str._str = static_cast<char *>(malloc((str._size + 1) * sizeof(char)));
    if(!str._str) throw std::bad_alloc();
    strcpy(str._str, str1._str);
    strcat(str._str, str2._str);
    return str;
}

std::ostream& Custom::operator<<(std::ostream& os, const String& str) {
    os << str._str;
    return os;
}

void String::_readChunk(std::istream& is, size_t maxBuffSize, const char separator) {
    free(_str);
    _str = static_cast<char *>(malloc(maxBuffSize * sizeof(char)));
    if(!_str) throw std::bad_alloc();
    _size = 0;
    while(_size < maxBuffSize - 1) {
        char val;
        is.get(val);
        if(!is) break;
        _str[_size++] = val;
        if(val == separator) break;
    }
    _str[_size] = '\0';
    _str = static_cast<char *>(realloc(_str, (_size + 1) * sizeof(char)));
}

std::istream& Custom::operator>>(std::istream& is, String& str) {
    const char separator = '\n';
    str = "";
    String buff;
    do {
        buff._readChunk(is, BUFSIZ, separator);
        str += buff;
    } while(is && !str.empty() && str.back() != separator);
    return is;
}
