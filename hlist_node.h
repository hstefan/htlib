#ifndef HUGO_HLIST_NODE_H__
#define HUGO_HLIST_NODE_H__

namespace htl
{
	namespace detail
	{
		template <typename T>
		struct hlist_node
		{
		public:
			T value;
			hlist_node<T>* prev;
			hlist_node<T>* next;

			hlist_node(T _value = T(), hlist_node<T>* _prev = 0, hlist_node<T>* _next = 0)
				: value(_value), prev(_prev), next(_next)
			{}
		};
	}
}
#endif