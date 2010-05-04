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
        typedef Allocator								        allocator_type;
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
		size_type calculate_size();
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
		: mySize(n), myCapacity(n), myAllocator(x)
	{
		myBegin = myAllocator.allocate(n);
        myAllocator.construct(myBegin, T());
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
		: myCapacity(x.capacity()), mySize(x.size())
	{
        reserve(x.capacity());
        for(size_type i = 0; i < x.size(); i++)
        {
            myBegin[i] = x[i];
            mySize++;
        }
	}

	template <class T, class Allocator>
	Vector<T, Allocator>::~Vector()
	{
		if(myBegin != 0)
            myAllocator.destroy(myBegin);
			myAllocator.deallocate(myBegin);
	}

	template <class T, class Allocator>
	Vector<T, Allocator>& Vector<T, Allocator>::operator=(const Vector<T, Allocator>& x)
	{
		myCapacity = x.capacity();
		mySize = x.size();
		myAllocator = x.get_allocator();
        if(!empty())
            clear();
        reserve(x.capacity());
        for(size_type i = 0; i < x.size(); i++) 
        {
            myBegin[i] = x[i];
            mySize++;
        }
		return *this;
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
    typename Vector<T, Allocator>::allocator_type Vector<T, Allocator>::get_allocator() const
	{
		return myAllocator;
	}
	
	template <class T, class Allocator>
	typename Vector<T, Allocator>::iterator Vector<T, Allocator>::begin()
	{
		return myBegin;
	}

	template <class T, class Allocator>
	typename Vector<T, Allocator>::const_iterator Vector<T, Allocator>::begin() const
	{
		return myBegin;
	}

	template <class T, class Allocator>
	typename Vector<T, Allocator>::iterator Vector<T, Allocator>::end()
	{
		return myBegin + mySize;
	}

	template <class T, class Allocator>
	typename Vector<T, Allocator>::const_iterator Vector<T, Allocator>::end() const
	{
		return myBegin + mySize;
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
		Vector<T, Allocator> x = *this;
		for(iterator i = begin(); i != end(); i++)
        {
            myAllocator.destroy(*i);
        }
        myAllocator.deallocate(myBegin);
        myBegin = myAllocator.allocate(sz);
        myAllocator.construct(p, T());
        this->assign(x.begin(), x.end());
	}

	template <class T, class Allocator>
	bool Vector<T, Allocator>::empty() const
	{
		return (myBegin == 0);
	}

	template <class T, class Allocator>
	void Vector<T, Allocator>::reserve(size_type n)
	{
		Vector<T, Allocator> x(*this);
		if(myBegin != 0)
        {
            myAllocator.destroy(myBegin);
            myAllocator.deallocate(myBegin);
        }
        myBegin = myAllocator.allocate(n);
        *this = x;
        myCapacity = n;
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
        return myBegin[mySize];
    }

    template <class T, class Allocator>
    typename Vector<T, Allocator>::const_reference Vector<T, Allocator>::back() const
    {
        return myBegin[mySize];
    }

    template <class T, class Allocator>
    void Vector<T, Allocator>::push_back(const T& x)
    {
        if(myCapacity - mySize <= 0)
        {
            reserve(calculate_size());
            myAllocator.construct(&myBegin[mySize], x);
        }
        else
        {
            myAllocator.construct(&myBegin[mySize], x);
        }
        mySize++;
    }

    template <class T, class Allocator>
    void Vector<T, Allocator>::pop_back()
    {
        myAllocator.destroy(&myBegin[mySize - 1]);
        mySize--;
    }

    template <class T, class Allocator>
    typename Vector<T, Allocator>::iterator Vector<T, Allocator>::insert(iterator position, const T& x)
    {
        Vector<T, Allocator> v(begin(), position - 1);
        v.push_back(x);
        iterator ret = v.end();
        for(iterator i = position; i != end(); i++)
            v.push_back(*i);

        *this = v;
        return ret;
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
       Vector<T, Allocator> v(begin(), position - 1);
       for(iterator i = position + 1; i != end(); i++)
           v.push_back(i);
       *this = v;
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
        for(iterator i = begin(); i != end(); i++)
        {
            myAllocator.destroy(i);
        }
        myAllocator.deallocate(myBegin);
        mySize = 0;
        myCapacity = 0;
        myBegin = 0;
    }

    template <class T, class Allocator>
    typename Vector<T, Allocator>::size_type Vector<T,Allocator>::calculate_size()
    {
        return myCapacity*2;
    }
}

#endif