#include "hvector.h"
#include "hallocator.h"
#include <iostream>

int main(int argc, char* argv[])
{
	htl::Vector<int> h;
	h.push_back(1);
	h.push_back(2);
	h.push_back(3);
	h.push_back(4);
	h.insert(h.end(), 10);
	//h.pop_back();
}