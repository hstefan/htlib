
/*
 *  Copyright (c) 2010 
 * 	Hugo Stefan Kaus Puhlmann <hugopuhlmann@gmail.com>
 * 
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 * 
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 * 
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
*/

#ifndef HUGO_HSTRING_H
#define HUGO_HSTRING_H

#include "hllocator.h"
#include "hvector.h"

namespace htl
{
	template <class charT, class Allocator = allocator<charT>>
	class basic_string
	{
	public:
		//types
		typedef typename Allocator::size_type						size_type;
		typedef typename Allocator::difference_type					difference_type;
		typedef 		 Allocator									allocator_type;	
		typedef typename Allocator::reference						reference;
		typedef typename Allocator::const_reference 				const_reference;
		typedef typename Allocator::pointer							pointer;
		typedef typename Allocator::const_pointer					const_pointer;
		
		typedef typename vector<CharT, Allocator>::iterator			iterator;
		typedef typename vector<CharT, Allocator>::const_iterator	const_iterator;

		static const size_type npos = -1;
		
		explicit basic_string(const Allocator& a = Allocator());
		basic_string(const basic_string& str);
		basic_string(const basic_string& str, size_type pos, size_type n = npos,
			const Allocator& a = Allocator());
		basic_string(const charT* s, size_type n, const Allocator& a = Allocator);
		basic_string(const charT* s, const Allocator& a = Allocator());
		basic_string(size_type n, charT c, const Allocator& a = Allocator());
		
		template <class InputIterator>
		basic_string(InputIterator begin, InputIterator end, const Allocator& a = Allocator);
		
		~basic_string();
		basic_string& operator=(const basic_string& str);
		basic_string& operator=(const charT* s);
		basic_string& operator=(charT c);

		//iterators	
		iterator		begin();
		const_iterator	begin() const;
		iterator		end();
		const_iterator	end() const;

		//capacity
		size_type size() const;
		size_type length() const;
		size_type max_size() const;
		void resize(size_type n, charT c);
		void resize(size_type n);
		size_type capacity() const;
		void reserve(size_type res_arg = 0);
		void clear();
		bool empty() const;
		
		//modifiers
		basic_string& operator +=(const basic_string& str);
		basic_string& operator +=(const charT* s);
		basic_string& operator +=(charT c);
		basic_string& append(const basic_string& str);
		basic_string& append(const basic_string& str, size_type pos,
			size_type n);
		basic_string& append(const charT* s, size_type n);
		basic_string& append(const charT* s);
		basic_string& append(size_type n, charT c);
		template <class InputIterator>
			basic_string& append& append(InputIterator first, InputIterator last);
		void push_back(charT c);

	private:
		vector<T, Allocator> vec;
	};

	template <class charT, class Allocator>
	basic_string<charT, Allocator>::basic_string(const Allocator& a)
		: vec(a)
	{}

	template <class charT, class Allocator>
	basic_string<charT, Allocator>::basic_string(const basic_string<charT, Allocator>& str)
		: vec(str.get_allocator())
	{
		iterator it = str.begin();
		while it != str.end()
		{
			vec.push_back(*it);
			it++;
		}
	}

	template <class charT, class Allocator>
	basic_string<charT, Allocator::basic_string(const basic_string<charT, Allocator>& str,
		size_type pos, size_type n, const Allocator& a)
		: vec(a)
	{
		*this = str.substring(pos, n);
	}

	template <class charT, class Allocator>
	basic_string<charT, Allocator>::basic_string(const charT* s, size_type n, const Allocator& a = Allocator)
		: vec(a)
	{
		for(size_type i = 0; i < n; i++)
			push_back(s[i]);
	}

	template <class charT, class Allocator>
	basic_string<charT, Allocator>::basic_string(const charT* s,const Allocator& a = Allocator())
		: vec(a)
	{
		for(size_type i = 0; s[i] != '\0'; i++)
			push_back(s[i]);
	}

	template <class charT, class Allocator>
	basic_string<charT, Allocator>::basic_string(size_type n, charT c, const Allocator a)
		: vec(a)
	{
		while(n > 0)
		{
			push_back(c);
			n--;
		}
	}
	template <class charT, class Allocator>
	template <class InputIterator>
	basic_string<charT, Allocator>::basic_string(InputIterator begin, InputIterator end, 
			const Allocator& a)
		: vec(a)
	{
		while(begin != end)
		{
			push_back(*begin);
			begin++;
		}
	}

	template <class charT, class Allocator>
	basic_string<charT, Allocator>::~basic_string()
	{}

	template <class charT, class Allocator>
	basic_string<charT, Allocator>::operator=(const basic_string<charT, Allocator>& str)
	{
		vec.clear();
		iterator it = str.begin();
		while(it != str.end())
		{
			vec.push_back(*it);
			it++;
		}
	}

	template <class charT, class Allocator>
	basic_string<charT, Allocator>::operator=(const charT* s)
	{
		vec.clear();
		for(size_type i = 0; s[i] != '\0'; i++)
			vec.push_back(s[i]);
	}

	template <class charT, class Allocator>
	basic_string<charT, Allocator>::operator=(charT c)
	{
		vec.clear();
		vec.push_back(c);
	}
	
	template <class charT, class Allocator>
	basic_string<charT, Allocator>::iterator basic_string<charT, Allocator>::begin()
	{ return vec.begin(); }
	
	template <class charT, class Allocator>
	basic_string<charT, Allocator>::const_iterator basic_string<charT, Allocator>::begin() const
	{ return vec.begin(); }
	
	template <class charT, class Allocator>
	basic_string<charT, Allocator>::iterator basic_string<charT, Allocator>::end()
	{ return vec.end(); }

	template <class charT, class Allocator>
	basic_string<charT, Allocator>::const_iterator basic_string<charT, Allocator>::end()
	{ return vec.end(); }

	template <class charT, class Allocator>
	basic_string<charT, Allocator>::size_type basic_string<charT, Allocator>::size() const
	{ return vec.size(); }
	
	template <class charT, class Allocator>
	basic_string<charT, Allocator>::size_type basic_string<charT, Allocator>::length() const
	{ return vec.size(); }
	
	template <class charT, class Allocator>
	basic_string<charT, Allocator>::size_type basic_string<charT, Allocator>::max_size() const
	{ return vec.max_size(); }

	template <class charT, class Allocator>
	void basic_string<charT, Allocator>::resize(size_type n, charT c)
	{ vec.resize(n, c); }
	
	template <class charT, class Allocator>
	void basic_string<charT, Allocator>::resize(size_type n)
	{ vec.resize(n); }

	template <class charT, class Allocator>
	basic_string<charT, Allocator>::size_type basic_string<charT, Allocator>::capacity() const
	{ return vec.capacity(); }

	template <class charT, class Allocator>
	void basic_string<charT, Allocator>::reserve(size_type res_arg)
	{ vec.reserve(res_arg); }

	template <class charT, class Allocator>
	void basic_string<charT, Allocator>::clear()
	{ vec.clear(); }

	template <class charT, class Allocator>
	bool basic_string<charT, Allocator>::empty() const
	{ return vec.empty(); }

	template <class charT, class Allocator>
	basic_string<charT, Allocator>& basic_string<charT, Allocator>::operator+=(
		const basic_string<charT, Allocator>& str)
	{
		iterator it = str.begin();
		while(it != str.end())
		{
			push_back(*it);
			it++;
		}
		return *this;
	}	

	template <class charT, class Allocator>
	basic_string<charT, Allocator>& basic_string<charT, Allocator>::operator+=(const charT* s)
	{
		for(size_type i = 0; s[i] != '\0'; i++)
			push_back(s[i]);
		return *this;
	}
	
	template <class charT, class Allocator>
	basic_string<charT, Allocator>&  basic_string<charT, Allocator>::operator+=(charT c)
	{ 
		push_back(c); 
		return *this;
	}
	
	template <class charT, class Allocator>
	basic_string<charT, Allocator>& basic_string<charT, Allocator>::append(
			const basic_string<charT, Allocator>& str)
	{ return (*this += str); }

	template <class charT, class Allocator>
	basic_string<charT, Allocator>& basic_string<charT, Allocator>::append(
			const basic_string<charT, Allocator>& str, seize_type pos, size_type n)
	{
		while(n > 0)
			push_back(str[pos++]), n--;
		return *this;
	}
	
	template <class charT, class Allocator>
	basic_string<charT, Allocator>& basic_string<charT, Allocator>::append(
			const charT* s, size_type n)
	{
		for(size_type i = 0; i < n; i++)
			push_back(s[i]);
		return *this;
	}
	
	template <class charT, class Allocator>
	basic_string<charT, Allocator>& basic_string<charT, Allocator>::append(
			const charT* s)
	{
		for(size_type i = 0; s[i] != '\0'; i++)
			push_back(s[i]);
		return *this;
	}
	
	template <class charT, class Allocator>
	basic_string<charT, Allocator>& basic_string<charT, Allocator>::append(
			size_type n, charT c)
	{
		while(n > 0)
			push_back(c), n--;
		return *this;
	}
		
	template <class charT, class Allocator>
	template <class InputIterator>
	basic_string<charT, Allocator>& basic_string<charT, Allocator>::append(
			InputIterator first, InputIterator last)
	{
		while first != last
			push_back(*(first++));
		return *this;
	}
	
	template <class charT, class Allocator>
	void basic_string<charT, Allocator>::push_back(charT c)
	{ vec.push_back(c); }

	
}

#endif


