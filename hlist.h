#ifndef HUGO_H_LIST__
#define HUGO_H_LIST__

#include "hallocator.h"
#include "hiterators.h" 

namespace htl 
{
	template <class T, class Allocator = allocator<T> >
	class list 
	{
		class node;
	public:
		// types:
		typedef typename Allocator::reference							reference;
		typedef typename Allocator::const_reference						const_reference;		
		typedef typename bidirectionalIterator<T, node>					iterator; 
		typedef typename bidirectionalIterator<T, node>					const_iterator;
		typedef unsigned int											size_type;
		typedef unsigned int											difference_type;
		typedef T														value_type;
		typedef Allocator												allocator_type;
		typedef typename Allocator::pointer								pointer;
		typedef typename Allocator::const_pointer						const_pointer;
		/*typedef	std::reverse_iterator<iterator>			reverse_iterator;
		typedef	std::reverse_iterator<const_iterator>	const_reverse_iterator;*/

		//construct/copy/destroy:
		explicit list(const Allocator& = Allocator());

		explicit list(size_type n, const T& value = T(),
		const Allocator& = Allocator());
		
		template <class InputIterator>
		list(InputIterator first, InputIterator last,
			const Allocator& = Allocator());

		list(const list<T,Allocator>& x );
		~list();

		list<T,Allocator>& operator=(const list<T,Allocator>& x);

		template <class InputIterator>
		void assign(InputIterator first, InputIterator last);

		void assign(size_type n, const T& t);
		allocator_type get_allocator() const;
		
		// iterators:
		iterator begin();
		//const_iterator begin() const;
		iterator end();
		//const_iterator end() const;
		//reverse_iterator rbegin();
		//const_reverse_iterator rbegin() const;
		//reverse_iterator rend();
		//const_reverse_iterator rend() const;
		
		//capacity:
		bool empty() const;
		size_type size() const;
		size_type max_size() const;
		void resize(size_type sz, T c = T());
		// element access:
		reference front();
		const_reference front() const;
		reference back();
		const_reference back() const;
		//modifiers:
		void push_front(const T& x);
		void pop_front();
		void push_back(const T& x);
		void pop_back();
		iterator insert(iterator position, const T& x);
		void insert(iterator position, size_type n, const T& x);
		
		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last);
		iterator erase(iterator position);
		iterator erase(iterator position, iterator last);
		void swap(list<T,Allocator>&);
		void clear();
		//list operations:
		void splice(iterator position, list<T,Allocator>& x);
		void splice(iterator position, list<T,Allocator>& x, iterator i);
		void splice(iterator position, list<T,Allocator>& x, iterator first,
		iterator last);
		void remove(const T& value);
		template <class Predicate> void remove_if(Predicate pred);
		void unique();
		template <class BinaryPredicate>
		void unique(BinaryPredicate binary_pred);
		void merge(list<T,Allocator>& x);
		
		template <class Compare> 
		void merge(list<T,Allocator>& x, Compare comp);
		
		void sort();
		template <class Compare> 
		
		void sort(Compare comp);
		void reverse();
	
	protected:
		class node
		{
		public:
			node(const_reference val, node* prv = 0, node* nxt = 0)
				: value(val), next(nxt), prev(prv)
			{}
			node* next;
			node* prev;
			value_type value;
		};

		node* first;
		node* last;
		size_type m_size;
		Allocator alloc;
	};

	template <class T, class Allocator>
	list<T,Allocator>::list(const Allocator& x = Allocator())
		: first(0),  last(0), m_size(0), alloc(x)
	{}

	template <class T, class Allocator>
	list<T, Allocator>::list(size_type n, const T& value = T(), 
		const Allocator& x = Allocator()) 
		: first(0), last(0), m_size(0), alloc(x)
	{
		while(n >= 0)
		{
			push_back(value);
			n--;
		}
	}

	template <class T, class Allocator>
	template <class InputIterator>
	list<T, Allocator>::list(InputIterator first, InputIterator last,
		const Allocator& x = Allocator())
		: first(0), last(0), m_size(0), alloc(x)
	{
		while(first != last)
		{
			push_back(*first);
			first++;
		}
		push_back(*last);
	}

	template <class T, class Allocator>
	list<T, Allocator>::list(const list<T, Allocator>& x)
		: first(0), last(0), m_size(0), alloc(x.get_allocator())
	{
		iterator it = x.begin();
		while(it != x.last())
		{
			push_back(it);
			it++;
		}
		push_back(*it);
	}

	template <class T, class Allocator>
	list<T, Allocator>::~list()
	{
		while(first != last)
		{
			first++;
			delete first->prev;
		}
	}

	template <class T, class Allocator>
	list<T,Allocator>& list<T, Allocator>::operator=(const list<T,Allocator>& x)
	{
		for(iterator it = x.begin(); it != x.last(); it++)
			push_back(*it);
	}

	template <class T, class Allocator>
	template <class InputIterator>
	void list<T, Allocator>::assign(InputIterator first, InputIterator last)
	{
		while(first != last)
		{
			push_back(*first);
			first++;
		}
	}
	template <class T, class Allocator>
	void list<T, Allocator>::assign(size_type n, const T& t)
	{
		for(size_type i = 0; i < n; i++)
			push_back(t);
	}

	template <class T, class Allocator>
	typename list<T, Allocator>::allocator_type list<T, Allocator>::get_allocator() const
	{ return alloc; }

	template <class T, class Allocator>
	typename list<T, Allocator>::iterator begin() 
	{ return iterator(first); }	

	template <class T, class Allocator>
	typename list<T, Allocator>::iterator end() 
	{ return iterator(last); }

	template <class T, class Allocator>
	bool list<T, Allocator>::empty() const
	{ return size == 0; }

	template <class T, class Allocator>
	typename list<T, Allocator>::size_type list<T, Allocator>::size() const
	{ return size; }

	template <class T, class Allocator>
	typename list<T, Allocator>::size_type list<T, Allocator>::max_size() const
	{ return alloc.max_size(); }

	template <class T, class Allocator>
	typename list<T, Allocator>::reference list<T, Allocator>::front()
	{ return first->value; }

	template <class T, class Allocator>
	typename list<T, Allocator>::const_reference list<T, Allocator>::front() const
	{ return first->value; }

	template <class T, class Allocator>
	typename list<T, Allocator>::reference list<T, Allocator>::back()
	{ return last->value; }

	template <class T, class Allocator>
	typename list<T, Allocator>::const_reference list<T, Allocator>::back() const
	{ return last->value; }

	template <class T, class Allocator>
	void list<T, Allocator>::push_front(const T& x) 
	{
		if(first == 0)
		{
			first = new node(x);
			last = first;
		}
		else
		{
			node* n = new node(x, 0, first);
			first->prev = n;
			first = n;
		}
	}

	template <class T, class Allocator>
	void list<T, Allocator>::pop_front() 
	{
		if(first != 0)
		{
			node* n = first;
			first = first->next;
			delete n;
		}
	}

	template <class T, class Allocator>
	void list<T, Allocator>::push_back(const T& x)
	{
		if(last == 0)
		{
			first = new node(x);
			last = first;
		}
		else
		{
			node* n = new node(x, last, 0);
			last->next = n;
			last = n;
		}
	}
}

#endif