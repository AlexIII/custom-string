/*
 *      Custom String
 *      Author: AlexIII
 */

#ifndef _CUSTOM_STRING_H_
#define _CUSTOM_STRING_H_

#include <stddef.h>
#include <ostream>
#include <istream>

namespace Custom {
    class String {
    private:
        char* _str;
        size_t _size;
        void _readChunk(std::istream& is, size_t maxBuffSize, const char separator = '\n');
    public:
        String() noexcept;
        String(const char *);
        String(const String &);
        String(String &&) noexcept;
        ~String() noexcept;

        String &operator=(const String &);
        String &operator+=(const String &);

        char &operator[](size_t) noexcept;
        const char &operator[](size_t) const noexcept;
        char &back() noexcept;
        const char &back() const noexcept;
        char &front() noexcept;
        const char &front() const noexcept;

        operator const char *() const noexcept;
        const char *c_str() const noexcept;

        int compare(const String &) const noexcept;
        bool operator==(const String &) const noexcept;
        bool operator!=(const String &) const noexcept;
        bool operator<(const String &) const noexcept;
        bool operator>(const String &) const noexcept;
        bool operator<=(const String &) const noexcept;
        bool operator>=(const String &) const noexcept;

        size_t length() const noexcept;
        bool empty() const noexcept;

        String &toLower() noexcept;
        String &toUpper() noexcept;
        String asLower() const;
        String asUpper() const;

        friend String operator+(const String &, const String &);
        friend std::ostream& operator<<(std::ostream& out, const String& str);
        friend std::istream& operator>>(std::istream& in, String& str);
    };

    String operator+(const String &, const String &);
    std::ostream& operator<<(std::ostream& out, const String& str);
    std::istream& operator>>(std::istream& in, String& str);
}

#endif
