#ifndef HUGO_HSTRING_H__
#define HUGO_HSTRING_H__
#include <cstring>

namespace htl
{
    class String
    {
    private:
        char* m_str;
        size_t m_length;

        char* duplicate(const char* str);
        String duplicate(const String& str);

    public:
        //ctors
        String();
        String(const String& str);
        String(const String& str, size_t pos, size_t n);
        String(const char* str, size_t n);
        String(const char* str);
        String(size_t n, char c);
        
        //access functions    
        inline const char* cstr() const
        {
            return m_str;
        }
        size_t length() const
        {
            return m_length;
        }
        
        //stuff functions
        String substr(const size_t& s, const size_t& f) const;
        void resize(size_t n);
        void resize(size_t n, char c);
        String& operator=(const String& str);
    };
}
#endif