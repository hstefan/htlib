#ifndef HUGO_H_LIST__
#define HUGO_H_LIST__

#include "hallocator.h"
#include "hlist_node.h"

namespace htl 
{
	namespace detail 
	{
		template <class T>
		class list_iterator 
		{
		public:
			typedef T*					pointer;
			typedef T&					reference;
			typedef T					value_type;
			typedef unsigned int		diff_type;
			list_iterator(hlist_node<T>* i);
			list_iterator(const list_iterator<T>& it);
			list_iterator();

			list_iterator& operator=(const list_iterator<T>& it)
			{
				ptr = it.ptr;
				return *this;
			}
			list_iterator& operator++()
			{
				ptr = ptr->next;
				return *this;
			}
			list_iterator operator++(int)
			{
				list_iterator i = *this;
				ptr = ptr->next;
				return i;
			}
			list_iterator& operator--()
			{   
				ptr = ptr->prev;
				return *this;
			}
			list_iterator& operator--(int)
			{
				list_iterator i = *this;
				ptr = ptr->prev;
				return i;
			}
			bool operator==(const list_iterator<T>& it)
			{ return ptr == it.ptr; }
			bool operator!=(const list_iterator<T>& it)
			{ return ptr != it.ptr; }
			reference operator*()
			{ return ptr->value;}

		private:
			template <class S, class U>
			friend class list;

			hlist_node<T>* ptr;
		};

		template <class T>
		list_iterator<T>::list_iterator(hlist_node<T>* i)
		{
			ptr = i;
		}

		template <class T>
		list_iterator<T>::list_iterator(const list_iterator<T>& it)
		{
			ptr = it.ptr;
		}
		template <class T>
		list_iterator<T>::list_iterator()
		{
			ptr = 0;
		}
	} 

	template <class T, class Allocator = allocator<T> >
	class list 
	{
	public:
		// types:
		typedef typename Allocator::reference							reference;
		typedef typename Allocator::const_reference						const_reference;		
		typedef typename detail::list_iterator<T>						iterator; 
		typedef typename detail::list_iterator<T>						const_iterator;
		typedef unsigned int									size_type;
		typedef unsigned int									difference_type;
		typedef T										value_type;
		typedef Allocator									allocator_type;
		typedef typename Allocator::pointer							pointer;
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
		
		template <class Predicate> 
		void remove_if(Predicate pred);
		
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

		detail::hlist_node<T>* first;
		detail::hlist_node<T>* last;
		size_type m_size;
		Allocator alloc;

		template <typename U>
		friend class detail::list_iterator;
	};
	template <class T, class Allocator>
	list<T,Allocator>::list(const Allocator& x)
		: first(0),  last(0), m_size(0), alloc(x)
	{}

	template <class T, class Allocator>
	list<T, Allocator>::list(size_type n, const T& value, 
		const Allocator& x) 
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
		const Allocator& x)
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
		erase(begin(), end());
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
	typename list<T, Allocator>::iterator list<T, Allocator>::begin() 
	{ return iterator(first); }	

	template <class T, class Allocator>
	typename list<T, Allocator>::iterator list<T, Allocator>::end() 
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
			first = new detail::hlist_node<T>(x, 0, 0);
			last = first;
		}
		else
		{
			detail::hlist_node<T>* n = new detail::hlist_node<T>(x, 0, first);
			first->prev = n;
			first = n;
		}
	}

	template <class T, class Allocator>
	void list<T, Allocator>::pop_front() 
	{
		if(first != 0)
		{
			detail::hlist_node<T>* n = first;
			first = first->next;
			delete n;
		}
	}

	template <class T, class Allocator>
	void list<T, Allocator>::push_back(const T& x)
	{
		if(last == 0)
		{
			first = new detail::hlist_node<T>(x);
			last = first;
		}
		else
		{
			detail::hlist_node<T>* n = new detail::hlist_node<T>(x, last, 0);
			last->next = n;
			last = n;
		}
		m_size++;
	}
	template <class T, class Allocator>
	void list<T, Allocator>::pop_back()
	{
		if(last != 0)
		{
			detail::hlist_node<T>* n = last;
			last = last->prev;
			delete n;
		}
	}

	template <class T, class Allocator>
	typename list<T, Allocator>::iterator list<T, Allocator>::erase(iterator position)
	{
		if(position.ptr != 0)
		{	
			if(position.ptr->prev != 0)
				position.ptr->prev->next = position.ptr->next;
			else //the element was the first in the list
				first = position.ptr->next;
			
			if(position.ptr->next != 0)
				position.ptr->prev->next->prev = position.ptr->prev;
			else //the element was the last in the list
				last = position.ptr->prev;
			
			iterator it(position.ptr->next);
			delete position.ptr;
			m_size--;
			return it;		
		}
	}

	template <class T, class Allocator>
	typename list<T, Allocator>::iterator list<T, Allocator>::erase(iterator position, iterator last)
	{
		iterator it;
		while(position != last)
			it = erase(position++);
		return it;
	}

	template <class T, class Allocator>
	typename list<T,Allocator>::iterator list<T, Allocator>::insert(iterator position, const T& x)
	{
		if(position.ptr != 0)
		{
			detail::hlist_node<T>* node = new detail::hlist_node<T>(x, position.ptr, position.ptr->next);
			
			if(position.ptr->next == 0)
				last = node;
			if(position.ptr->prev == 0)
				first = node;
			
			position.ptr->next = node;
			m_size++;
			return iterator(node);
		}
		else
			return iterator(0);
	}

	template <class T, class Allocator>
	void list<T, Allocator>::insert(iterator position, size_type n, const T& x)
	{
		while(n != 0)
		{
			insert(position++, x);
			n--;
		}
	}
	template <class T, class Allocator>
	template <class InputIterator>
	void list<T, Allocator>::insert(iterator position, InputIterator first, InputIterator last)
	{
		while(first != last)
		{
			insert(position++, *first);
			first++;
		}
	}

	template <class T, class Allocator>
	void list<T, Allocator>::swap(list<T, Allocator>& x)
	{
		detail::hlist_node<T>* f = x.first;
		detail::hlist_node<T>* l = x.last;
		size_type size = x.size();
		Allocator al = x.get_allocator();

		x.first = this->first;
		x.last = this->last;
		x.m_size = this->m_size;
		x.alloc = this->alloc;

		first = f;
		last = l;
		m_size = size;
		alloc = al;
	}

	template <class T, class Allocator>
	void list<T, Allocator>::clear()
	{ erase(begin(), last()); }

	template <class T, class Allocator>
	void list<T, Allocator>::splice(iterator position, list<T, Allocator>& x)
	{
		splice(position, x, x.begin(), x.end());	
	}

	template <class T, class Allocator>
	void list<T, Allocator>::splice(iterator position, list<T, Allocator>& x, iterator i)
	{
			insert(position, *i);
			x.erase(i);
	}

	template <class T, class Allocator>
	void list<T, Allocator>::splice(iterator position, list<T, Allocator>& x, iterator first, 
					iterator last)
	{
		while(first != last)
		{
			insert(position++, *first);
			x.erase(first);
			first++;
		}
	}

	template <class T, class Allocator>
	void list<T, Allocator>::remove(const T& value)
	{
		iterator it = begin();
		while(it != end())
		{
			if(*it == value)
				erase(it);
			it++;
		}
	}
	
	template <class T, class Allocator>
	template <class Predicate>
	void list<T, Allocator>::remove_if(Predicate pred)
	{
		iterator it = begin();
		while(it != end())
		{
			if(Predicate(*it))
				erase(it);
			it++;
		}
	}

	template <class T, class Allocator>
	void list<T, Allocator>::unique()
	{
		iterator it = begin();
		value_type val;
		while(it != end())
		{
			if(*it != val)
				val = *it;
			it++;
			if(val == *it)
				it = erase(it);
		}
	}

	template <class T, class Allocator>
	template <class BinaryPredicate>
	void list<T, Allocator>::unique(BinaryPredicate binary_pred)
	{
		iterator it = begin();
		value_type val;
		while(it != end())
		{
			if(binary_pred(*it, val))
				it = erase(it);
			else
				val = *it;
		}
	}

	template <class T, class Allocator>
	void list<T, Allocator>::merge(list<T, Allocator>&  x)
	{
		x.sort();
		sort();
		iterator it_x = x.begin();
		iterator it_y = begin();
		
		while(it_x != x.end())
		{
			if(*it_y <= *it_x)
			{
				insert(it_y, *it_x);
				it_x = x.erase(it_x);
			}
			else if(it_y != end())
				it_y++;
			else
			{
				while(it_x != x.end())
				{
					push_back(*it_x);
					it_x++;
				}
			}
		}
	}

	template <class T, class Allocator>
	template <class Compare>
	void list<T, Allocator>::merge(list<T, Allocator>& x, Compare comp)
	{
		x.sort();
		sort();
		iterator it_x = x.begin();
		iterator it_y = begin();
		
		while(it_x != x.end())
		{
			if(comp(*it_y,*it_x))
			{
				insert(it_y, *it_x);
				it_x = x.erase(it_x);
			}
			else if(it_y != end())
				it_y++;
			else
			{
				while(it_x != x.end())
				{
					push_back(*it_x);
					it_x = x.erase(it_x);
				}
			}
		}
	}

	template <class T, class Allocator>
	void list<T, Allocator>::sort() //temporary bubble sort... but it'll be upgraded soon
	{
		iterator it_a = begin();
		iterator it_b = begin();
		while(it_a != end())
		{
			while(it_b != end())
			{
				if(*it_a > *it_b)
				{
					insert(it_b, *it_a);
					it_b = erase(it_a);
				}
				else
					it_b++;
			}
			it_b = begin();
		}
	}

	template <class T, class Allocator>
	template <class Compare>
	void list<T, Allocator>::sort(Compare comp)
	{
		iterator it_a = begin();
		iterator it_b = begin();
		while(it_a != end())
		{
			while(it_b != end())
			{
				if(comp(*it_a, *it_b))
				{
					insert(it_b, *it_a);
					it_b = erase(it_a);
				}
				else
					it_b++;
			}
			it_b = begin();
		}
	}

	template <class T, class Allocator>
	void list<T, Allocator>::reverse()
	{
		size_type sz = m_size;
		while(sz > 0)
		{
			push_back(*begin());
			erase(begin());
			sz--;
		}
	}
}

#endif
