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

	template <class T, class C>
	class bidirectionalIterator
		{
		public:
			typedef C				container;
			typedef T*				pointer;
			typedef T&				reference;
			typedef T				value_type;
			typedef unsigned int	diff_type;
			bidirectionalIterator(C* x = 0);
			bidirectionalIterator(const bidirectionalIterator<T, C>& it);
			
			bidirectionalIterator& operator=(const bidirectionalIterator<T, C>& it)
			{
				ptr = it.ptr;
				return *this;
			}
			bidirectionalIterator& operator++()
			{
				ptr = ptr->next;
				return *this;
			}
			bidirectionalIterator& operator++(int)
			{
				ptr = ptr->next;
				return *this;
			}
			bidirectionalIterator& operator--()
			{   
				ptr = ptr->prev;
				return *this;
			}
			bidirectionalIterator& operator--(int)
			{
				ptr = ptr->prev;
				return *this;
			}
			bidirectionalIterator& operator==(const bidirectionalIterator<T,C>& it)
			{ return ptr == it; }
			bidirectionalIterator& operator!=(const bidirectionalIterator<T,C>& it)
			{ return ptr != it; }
			reference operator*()
			{ return ptr->value;}

		private:
			C* ptr;
		};
}

#endif