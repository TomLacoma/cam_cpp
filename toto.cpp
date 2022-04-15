#include <stdio.h>
#include <iostream>


class toto{
	public:
		int a;
		toto(int);
};

toto::toto(int _a){
	a=_a;
}

using namespace std;

int main (void) {
	toto t(14);
	cout << t.a << endl;
	void *pv=NULL;
	pv = &t;
	cout << "pv=" << (*(toto*)pv).a << endl ;
	(*(toto*)pv).a = 4;
 cout << "pv=" << (*(toto*)pv).a << endl ;
	return 0;
}

