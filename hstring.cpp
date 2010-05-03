#include "hstring.h"

namespace htl
{
    //Default constructor, initializes an empty string
    String::String() 
        : m_str(duplicate("")), m_length(0)
    {}

    //copies one String
    String::String(const String& str)
        : m_str(duplicate(str.cstr())), m_length(str.length())
    {}
   
    //creates a substring from s to f
    String String::substr(const size_t& s, const size_t& f) const 
    {
        char* newstr = new char[f - s];
        strncpy(newstr, m_str + s, f - s);
        newstr[f - s] = '\0';
        return String(newstr);
    }
    //copies a substring
    String::String(const String& str, size_t pos, size_t n)
    {	
		m_length = n - pos;
        m_str = duplicate(str.substr(pos, n).cstr());
    }
    
    //creates a String from a const char*
    String::String(const char* str) 
    {
        m_str = duplicate(str);
        m_length = strlen(str);
    }

    //creates a String with the first n characters of 'str'
    String::String(const char* str, size_t n)
    {
        m_length = n;
        m_str = new char[n];
        strncpy(m_str, str, n);
        m_str[n] = '\0';
    }
    
    //creats a String which is a repetition of 'c' character
    String::String(size_t n, char c)
    {
        m_str = new char[n];
        for(unsigned int i = 0; i < n; i++)
        {
            m_str[i] = c;
        }
        m_str[n] = '\0';
    }

    //resizes the list to a new length 'n'
    void String::resize(size_t n)
    {
        if(n > length())
        {
            // todo: alocar nova string
        }
        else
        {}
    }
    
    //resizes the list to a new length 'n' filled with characters c, if n > lenght
    void String::resize(size_t n, char c)
    {
        char* cpy = _strdup(m_str);
        delete[] m_str;
        m_str = new char[n];

        if(n < m_length)
            strncpy(m_str, cpy, n);
        else
        {
            strncpy(m_str, cpy, m_length);
            m_str[m_length] = '\0';
            String s(n - m_length, c);
            char* newstr = strcat(m_str, s.cstr());
            delete m_str;
            m_str = duplicate(newstr);
            delete newstr;
        }
    }
    String& String::operator=(const String& str)
    {
        delete[] m_str;
        m_str = duplicate(str.cstr());
        m_length = str.length();
        return *this;
    }
    char* String::duplicate(const char* str)
    {
        char* newstr = new char[strlen(str)];
        strcpy(newstr, str);
        return newstr;
    }
    String String::duplicate(const String& str)
    {
        return String(duplicate(str.cstr()));
    }
}