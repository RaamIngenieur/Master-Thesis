//============================================================================
// Name        : Hello.cpp
// Author      : Raam
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdlib.h>
using namespace std;

int main() {

	unsigned long *a,*b,c;
	a = (unsigned long*)malloc(sizeof (unsigned long));
	b = (unsigned long*)malloc(sizeof (unsigned long));

	*a= 12;
	*b =12;
	c=*a^*b;
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	cout << c<<endl;
	cout<<sizeof(long long);
	return 0;
}
