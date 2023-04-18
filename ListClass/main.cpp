#include <iostream>
#include "List.h"

int main()
{
	int arr[5] = { 1, 2, 3, 4, 5 };
	List lst(arr, 5);
	int s = lst[4];
	List a, b, c;
	std::cout << a << std::endl;
	std::cout << c << std::endl;
	std::cout << b << std::endl;
}