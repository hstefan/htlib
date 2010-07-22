#ifndef HUGO_stack_H__
#define HUGO_stack_H__

#include "hvector.h"

namespace htl
{
	template <class T, class Container = Vector<T> >
	class stack 
	{
	public:
		typedef typename Container::value_type		value_type;
		typedef typename Container::size_type		size_type;
		typedef			 Container					container_type;

		explicit stack(const Container& = Container());

		bool				empty() const { return c.empty(); }
		size_type			size() const { return c.size(); }
		//value_type&			top() const { return c.back(); }
		const value_type&	top() const { return c.back(); }
		void				push(const value_type& x) { c.push_back(x); }
		void				pop() { c.pop_back(); }
	protected:
		Container c;
	};

	template <class T, class Container>
	stack<T, Container>::stack(const Container& x = Container()) 
		: c(x)
	{}
}
#endif