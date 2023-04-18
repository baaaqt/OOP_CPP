#include <iostream>
#include "DynamicArray.h"
#include <time.h>

int main() {
	srand(time(0));
	DynamicArray<int> arr(50);
	arr.increasing_random_array(50, 100);
	std::cout << arr;
}