#ifndef HUGO_VECTOR_H__
#define HUGO_VECTOR_H__

#include "hallocator.h"
#include "hiterator.h"

namespace htl
{
	template <class T, class Allocator = allocator<T> >
	class Vector
	{
	public:
		//types
		typedef typename Allocator::reference                   reference;
		typedef typename Allocator::const_reference             const_reference;
		typedef typename randomAcessIterator<T>                 iterator;
		typedef typename randomAcessIterator<T>					const_iterator;
		typedef typename Allocator::pointer                     pointer;
		typedef typename Allocator::const_pointer				const_pointer;
		typedef size_t				                            size_type;
		typedef size_t                                          difference_type;
		typedef T                                               value_type;
		typedef Allocator								        allocator_type;
		//typedef reverse_iterator<iterator>                      reverse_iterator;
		//typedef reverse_iterator<const_iterator>                const_reverse_iterator;

		//construct/destruct/destroy
		explicit Vector(const Allocator& = Allocator());
		explicit Vector(size_type n, const T& value = T(),
			const Allocator& = Allocator());
		template <class InputIterator>
		Vector(InputIterator first, InputIterator last,
			const Allocator& = Allocator());
		Vector(const Vector<T, Allocator>& x);
		~Vector();
		Vector<T, Allocator>& operator=(const Vector<T, Allocator>& x);
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last);
		allocator_type get_allocator() const;

		//iterators
		iterator                    begin();
		const_iterator              begin() const;
		iterator                    end();
		const_iterator              end() const;
		//reverse_iterator            rbegin();
		//const_reverse_iterator      rbegin() const;
		//reverse_iterator            rend();
		//const_reverse_iterator      rend() const;

		//capacity
		size_type size() const;
		size_type max_size() const;
		void      resize(size_type sz, T c = T());
		size_type capacity() const;
		bool      empty() const;
		void      reserve(size_type n);

		//elemement access
		reference           operator[](size_type n);
		const_reference     operator[](size_type n) const;
		const_reference     at(size_type n) const;
		reference           at(size_type n);
		reference           front();
		const_reference     front() const;
		reference           back();
		const_reference     back() const;

		//modifiers
		void push_back(const T& x);
		void pop_back();
		iterator insert(iterator position, const T& x);
		void     insert(iterator position, size_type n, const T& x);
		template <class InputIterator>
		void insert(iterator position, InputIterator first,
			InputIterator last);
		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);
		void swap(Vector<T, Allocator>&);
		void clear();
	private:
		size_type calculate_size();
		void udestroy();

		T* myBegin;
		size_type myCapacity;
		size_type mySize;
		Allocator myAllocator;
	};
	
	template <class T, class Allocator>
	Vector<T, Allocator>::Vector(const Allocator& x = Allocator())
		: myBegin(0), myCapacity(0), mySize(0), myAllocator(x)
	{}

	template <class T, class Allocator>
	Vector<T, Allocator>::Vector(size_type n, const T& value = T(), 
		const Allocator& x = Allocator())
		: mySize(0), myCapacity(n), myAllocator(x)
	{
		reserve(myCapacity);
		for(int i = 0; i < myCapacity; i++) 
			myAllocator.construct(&myBegin[i], value);
	}

	template <class T, class Allocator>
	template <class InputIterator>
	Vector<T, Allocator>::Vector(InputIterator first, InputIterator last,
		const Allocator& x = Allocator())
		: myAllocator(x), myBegin(0), myCapacity(0), mySize(0)
	{
		for(InputIterator adr = first; adr != last; adr++)
			push_back(*adr);
	}

	template <class T, class Allocator>
	Vector<T, Allocator>::Vector(const Vector<T, Allocator>& x)
		: myAllocator(Allocator()), myCapacity(0), mySize(0), myBegin(0)
	{
		for(unsigned int i = 0; i < x.size(); i++) 
			push_back(x[i]);
	}

	template <class T, class Allocator>
	Vector<T, Allocator>::~Vector()
	{
		if(myBegin != 0) 
		{
			myAllocator.destroy(myBegin);
			myAllocator.deallocate(myBegin);
		}
	}

	template <class T, class Allocator>
	Vector<T, Allocator>& Vector<T, Allocator>::operator=(const Vector<T, Allocator>& x)
	{
		mySize = 0;
		myCapacity = 0;
		for(size_type i = 0; i < x.size(); i++) 
			push_back(x[i]);
		return *this;
	}

	template <class T, class Allocator>
	void Vector<T, Allocator>::udestroy() 
	{
		if(!empty()) 
			delete[] myBegin;
		mySize = 0;
		myBegin = 0;
		myCapacity = 0;
	}
	
	template <class T, class Allocator>
	template <class InputIterator>
	void Vector<T, Allocator>::assign(InputIterator first, InputIterator last)
	{	
		udestroy();
		reserve(first - last + 1);
		while(1)
		{
			this->push_back(*first);
			if(first == last) 
				break;
			first++;
		}
	}

	template <class T, class Allocator>
	typename Vector<T, Allocator>::allocator_type Vector<T, Allocator>::get_allocator() const
	{
		return myAllocator;
	}

	template <class T, class Allocator>
	typename Vector<T, Allocator>::iterator Vector<T, Allocator>::begin()
	{
		return iterator(myBegin);
	}

	template <class T, class Allocator>
	typename Vector<T, Allocator>::const_iterator Vector<T, Allocator>::begin() const
	{
		return iterator(myBegin);
	}

	template <class T, class Allocator>
	typename Vector<T, Allocator>::iterator Vector<T, Allocator>::end()
	{
		return iterator(myBegin + mySize);
	}

	template <class T, class Allocator>
	typename Vector<T, Allocator>::const_iterator Vector<T, Allocator>::end() const
	{
		return iterator(myBegin + mySize);
	}

	template <class T, class Allocator>
	typename Vector<T, Allocator>::size_type Vector<T, Allocator>::size() const
	{
		return mySize;
	}

	template <class T, class Allocator>
	typename Vector<T, Allocator>::size_type Vector<T, Allocator>::max_size() const
	{
		return myAllocator.max_size();
	}

	template <class T, class Allocator>
	typename Vector<T, Allocator>::size_type Vector<T, Allocator>::capacity() const
	{
		return myCapacity;
	}

	template <class T, class Allocator>
	void Vector<T, Allocator>::resize(size_type sz, T c = T())
	{
		if(sz < mySize) 
			mySize = sz;
		else if(sz > mySize)
		{
			for(int i = sz - mySize; i >= 0; i--)
				push_back(c);
			mySize = sz;
		}
	}

	template <class T, class Allocator>
	bool Vector<T, Allocator>::empty() const
	{
		return (myBegin == 0);
	}

	template <class T, class Allocator>
	void Vector<T, Allocator>::reserve(size_type n)
	{
		if(n > myCapacity)
		{
			pointer old_array = myBegin;
			myBegin = myAllocator.allocate(n);
			myCapacity = n;
			if(old_array != 0) 
			{
				for(size_type i = 0; i < mySize; i++)
					myAllocator.construct(&myBegin[i], old_array[i]);
				delete[] old_array;
			}
		}
	}

	template <class T, class Allocator>
	typename Vector<T, Allocator>::reference Vector<T, Allocator>::operator[] ( size_type n)
	{
		return myBegin[n];
	}

	template <class T, class Allocator>
	typename Vector<T, Allocator>::const_reference Vector<T, Allocator>::operator[] (size_type n) const
	{
		return myBegin[n];
	}

	template <class T, class Allocator>
	typename Vector<T, Allocator>::const_reference Vector<T, Allocator>::at(size_type n) const
	{
		return myBegin[n];
	}

	template <class T, class Allocator>
	typename Vector<T, Allocator>::reference Vector<T, Allocator>::at(size_type n)
	{
		return myBegin[n];
	}

	template <class T, class Allocator>
	typename Vector<T, Allocator>::reference Vector<T, Allocator>::front()
	{
		return *myBegin;
	}

	template <class T, class Allocator>
	typename Vector<T, Allocator>::const_reference Vector<T, Allocator>::front() const
	{
		return *myBegin;
	}

	template <class T, class Allocator>
	typename Vector<T, Allocator>::reference Vector<T, Allocator>::back()
	{
		return myBegin[mySize - 1];
	}

	template <class T, class Allocator>
	typename Vector<T, Allocator>::const_reference Vector<T, Allocator>::back() const
	{
		return myBegin[mySize - 1];
	}

	template <class T, class Allocator>
	void Vector<T, Allocator>::push_back(const T& x)
	{
		if(mySize >= myCapacity)
		{
			reserve(calculate_size());
			myAllocator.construct(&myBegin[mySize], x);
		}
		else
			myAllocator.construct(&myBegin[mySize], x);
		mySize++;
	}

	template <class T, class Allocator>
	void Vector<T, Allocator>::pop_back()
	{
		if(mySize <= 0) return;
		myAllocator.destroy(&myBegin[mySize - 1]);
		mySize--;
	}

	template <class T, class Allocator>
	typename Vector<T, Allocator>::iterator Vector<T, Allocator>::insert(iterator position, const T& x)
	{
		pointer old_array = myBegin;
		//stopped here
	}

	template <class T, class Allocator>
	void Vector<T, Allocator>::insert(iterator position, size_type n, const T& x)
	{
		Vector<T, Allocator> v(begin(), position - 1);
		for(size_type i = 0; i < n; i++)
			v.push_back(x);
		for(iterator it = position; position != end(); i++)
			v.push_back(x);
		*this = v;
	}

	template <class T, class Allocator>
	template <class InputIterator>
	void Vector<T, Allocator>::insert(iterator position, InputIterator first, InputIterator last)
	{
		Vector<T, Allocator> v(begin(), position);
		for(; first != last; last++)
			v.push_back(*first);
		for(; position != end(); position++)
			v.push_back(*position);
		*this = v;
	}

	template <class T, class Allocator>
	typename Vector<T, Allocator>::iterator Vector<T, Allocator>::erase(iterator position)
	{
		iterator it = position;
		it--;
		Vector<T, Allocator> v(begin(), it);
		it++, it++;
		for(; it != end(); it++)
			v.push_back(*it);
		clear();
		*this = v;
		return v.begin();
	}

	template <class T, class Allocator>
	typename Vector<T, Allocator>::iterator Vector<T, Allocator>::erase(iterator first, iterator last)
	{
		Vector<T, Allocator> v(begin(), first - 1);
		for(iterator i = last + 1; i != end(); i++)
			v.push_back();
		*this = v;
	}

	template <class T, class Allocator>
	void Vector<T, Allocator>::swap(Vector<T, Allocator>& vec)
	{
		Vector<T, Allocator> aux = vec;
		vec = *this;
		*this = aux;
	}

	template <class T, class Allocator>
	void Vector<T, Allocator>::clear()
	{
		if(empty())
			return;
		for(iterator i = begin(); i != end(); i++)
			myAllocator.destroy(&(*i));

		myAllocator.deallocate(myBegin);
		mySize = 0;
		myCapacity = 0;
		myBegin = 0;
	}

	template <class T, class Allocator>
	typename Vector<T, Allocator>::size_type Vector<T,Allocator>::calculate_size()
	{
		return myCapacity*2 + 1;
	}
}

#endif