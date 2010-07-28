
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
		basic_string(const charT* s, charT c, const Allocator& a = Allocator());
		
		template <class InputIterator>
		basic_string(InputIterator begin, InputIterator end, const Allocator& a = Allocator);
		~basic_string();
		basic_string& operator=(const basic_string& str);
		basic_string& operator=(const charT* s);
		basic_string& operator=(charT c);

		//iterators	
		
	private:
		vector<T, Allocator> vec;
	};

	template <class charT, class Allocator>
	basic_string<charT, Allocator>::basic_string(const Allocator& a)
		: vec(vector<T, Allocator>)
	{
		iterator it = a.begin();
		while(it != a.end)
			vec.push_back(*it)
	}

	template <class charT, class Allocator>
	template <class charT, class Allocator>
	template <class charT, class Allocator>
	template <class charT, class Allocator>
}

#endif
