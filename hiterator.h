#ifndef HUGO_H_ITERATOR_H__
#define HUGO_H_ITERATOR_H__

namespace htl
{
	template <class T>
	class randomAcessIterator 
	{
	public:
		typedef T*				pointer;
		typedef T&				reference;
		typedef	T				value_type;
		typedef unsigned int	diff_type;
		
		randomAcessIterator(pointer x) : ptr(x) {}
		randomAcessIterator(const randomAcessIterator<T>& x) : ptr(x.ptr) {}
		
		randomAcessIterator& operator++() 
		{
			++ptr;
			return *this;
		}
		randomAcessIterator& operator++(int)
		{
			ptr++;
			return *this;
		}

		randomAcessIterator& operator--()
		{
			--ptr;
			return *this;
		}
		randomAcessIterator& operator--(int)
		{
			ptr--;
			return *this;
		}
		bool operator==(const randomAcessIterator<T>& x)
		{
			return x.ptr == this->ptr;
		}
		bool operator!=(const randomAcessIterator<T>& x)
		{
			return x.ptr != this->ptr;
		}
		reference operator*()
		{
			return *ptr;
		}
		reference operator[](int i)
		{
			return ptr[i];
		}
		reference operator=(const randomAcessIterator<T>& x)
		{
			ptr = x.pr;
			return *this;
		}
		diff_type operator-(const randomAcessIterator<T> x)
		{
			return (ptr - x.ptr)/sizeof(pointer);
		}

	private:
		pointer ptr;
	};
}

#endif