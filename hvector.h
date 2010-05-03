#ifndef HUGO_VECTOR_H__
#define HUGO_VECTOR_H__

#include "hallocator.h"

namespace htl
{
    template <class T, class Allocator = allocator<T> >
    class Vector
    {
    public:
        //types
        typedef typename Allocator::reference                   reference;
        typedef typename Allocator::const_reference             const_reference;
        typedef typename Allocator::pointer                     iterator;
        typedef typename Allocator::const_pointer				const_iterator;
        typedef size_t				                            size_type;
        typedef size_t                                          difference_type;
        typedef T                                               value_type;
        typedef Allocator										allocator_type;
        typedef typename Allocator::pointer                     pointer;
        typedef typename Allocator::const_pointer               const_pointer;
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
		void alloc_capacity(size_type n);
        T* myBegin;
        size_type myCapacity;
        size_type mySize;
		Allocator myAllocator;
    };
	template <class T, class Allocator>
	explicit Vector<T, Allocator>::Vector(const Allocator& x = Allocator())
		: myBegin(0), myCapacity(0), mySize(0), myAllocator(x)
	{}

	template <class T, class Allocator>
	explicit Vector<T, Allocator>::Vector(size_type n, const T& value = T(), 
		const Allocator& x = Allocator())
		: mySize(n), myCapacity(n), myAllocator(x)
	{
		myBegin = myAllocator.allocate(n);
		for(Vector::iterator v = begin(); v++; v != end())
			push_back(n);
	}

	template <class T, class Allocator>
	template <class InputIterator>
    Vector<T, Allocator>::Vector(InputIterator first, InputIterator last,
                 const Allocator& = Allocator())
	{
		while(first != last)
		{
			push_back(first*);
			first++;
		}
	}
	
	template <class T, class Allocator>
	Vector<T, Allocator>::Vector(const Vector<T, Allocator>& x)
		: myCapacity(x.max_size()), mySize(x.size())
	{
		for(Vector::iterator i = x.begin(); i != x.end(); i++)
			push_back(i*);
	}

	template <class T, class Allocator>
	Vector<T, Allocator>::~Vector()
	{
		if(myBegin != 0)
			myAllocator.deallocate(myBegin);
	}

	template <class T, class Allocator>
	Vector<T, Allocator>& Vector<T, Allocator>::operator=(const Vector<T, Allocator>& x)
	{
		myCapacity = x.capacity();
		mySize = x.size();
		myAllocator = x.get_allocator();
		for(Vector::iterator i = x.begin(); i != x.end(), i++)
			push_back(i*);
		return this*;
	}

	template <class T, class Allocator>
	template <class InputIterator>
    void Vector<T, Allocator>::assign(InputIterator first, InputIterator last)
	{
		mySize = (size_type) ((last - first)/sizeof(InutIterator));
		while(first != last)
		{
			push_Back(first*);
			first++;
		}
	}
	template <class T, class Allocator>
	Vector<T, Allocator>::allocator_type get_allocator()
	{
		return myAllocator;
	}
	
	template <class T, class Allocator>
	Vector<T, Allocator>::iterator begin()
	{
		return myBegin;
	}

	template <class T, class Allocator>
	Vector<T, Allocator>::const_iterator begin() const
	{
		return myBegin;
	}

	template <class T, class Allocator>
	Vector<T, Allocator>::iterator Vector<T, Allocator>::end()
	{
		return myBegin + mySize;
	}

	template <class T, class Allocator>
	Vector<T, Allocator>::const_iterator Vector<T, Allocator>::end() const
	{
		return myBegin + mySize;
	}

	template <class T, class Allocator>
	Vector<T, Allocator>::size_type Vector<T, Allocator>::size()
	{
		return mySize;
	}

	template <class T, class Allocator>
	Vector<T, Allocator>::max_size()
	{
		return myAllocator.max_size();
	}

	template <class T, class Allocator>
	Vector<T, Allocator>::size_type Vector<T, Allocator>::capacity()
	{
		return myCapacity;
	}

	template <class T, class Allocator>
	void Vector<T, Allocator>::resize(size_type sz, T c = T())
	{
		Vector<T, Allocator> x = *this;
		clear();
		*this = x;
	}

	template <class T, class Allocator>
	Vector<T, Allocator>::size_type Vector<T, Allocator>::capacity()
	{
		return myCapacity;
	}

	template <class T, class Allocator>
	bool Vector<T, Allocator>::empty()
	{
		return (begin == 0);
	}

	template <class T, class Allocator>
	void Vector<T, Allocator>::reserve(size_type n)
	{
		Vector<T, Allocator> = *this;
		alloc_capacity(n);
	}

	template <class T, class Allocator>
	void Vector<T, Allocator>::alloc_capacity(size_type n)
	{
		myAllocator.deallocate(myBegin);
		myBegin = myAllocator.allocate(n);
		myCapacity = n;
	}
}
#endif