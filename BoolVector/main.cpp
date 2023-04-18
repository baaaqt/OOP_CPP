#include <iostream>
#include "BoolVector.h"

int main()
{
	using std::endl;
	using std::cout;
	BoolVector bv1(7, 1);
	BoolVector bv2(16, 0);
	BoolVector bv3(bv2);
	BoolVector bv4(~bv3);

	cout << bv1 << endl;
	cout << bv2 << endl;
	cout << bv3 << endl;
	cout << bv4 << endl;
	cout << "======= 2 =======" << endl;

	cout << bv1.weight() << endl;
	cout << bv2.weight() << endl;
	cout << bv3.weight() << endl;
	cout << bv4.weight() << endl;
	cout << "======= 3 =======" << endl;

	cout << (bv1 | bv1).weight() << endl;
	cout << (bv2 | bv1).weight() << endl;
	cout << (bv3 | bv1).weight() << endl;
	cout << (bv4 | bv1).weight() << endl;
	cout << "======= 4 =======" << endl;

	cout << (bv1 | bv2).weight() << endl;
	cout << (bv2 | bv2).weight() << endl;
	cout << (bv3 | bv2).weight() << endl;
	cout << (bv4 | bv2).weight() << endl; 
	cout << "======= 5 =======" << endl;

	cout << (bv1 & bv1).weight() << endl;
	cout << (bv2 & bv1).weight() << endl;
	cout << (bv3 & bv1).weight() << endl;
	cout << (bv4 & bv1).weight() << endl;
	cout << "======= 6 =======" << endl;

	cout << (bv1 & bv2).weight() << endl;
	cout << (bv2 & bv2).weight() << endl;
	cout << (bv3 & bv2).weight() << endl;
	cout << (bv4 & bv2).weight() << endl;
	cout << "======= 7 =======" << endl;

	cout << (bv1 ^ bv1).weight() << endl;
	cout << (bv2 ^ bv1).weight() << endl;
	cout << (bv3 ^ bv1).weight() << endl;
	cout << (bv4 ^ bv1).weight() << endl;
	cout << "======= 8 =======" << endl;
				 
	cout << (bv1 ^ bv2).weight() << endl;
	cout << (bv2 ^ bv2).weight() << endl;
	cout << (bv3 ^ bv2).weight() << endl;
	cout << (bv4 ^ bv2).weight() << endl;
	cout << "=======   =======" << endl;

	return 0;
}