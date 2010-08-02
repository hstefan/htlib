#include "hlist.h"
#include <iostream>

int main()
{
	htl::list<int> b;
	for(int i = 0; i < 20; i++) b.push_back(i);

	for(htl::list<int>::iterator it = b.begin(); it != b.end(); it++)
	{
		std::cout << *it << ",";
	}
}
