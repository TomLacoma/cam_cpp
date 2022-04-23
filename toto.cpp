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
	toto tata = (*(toto*)pv);
	cout << "pv=" << tata.a << endl ;
	tata.a = 4;
 cout << "pv=" << tata.a << endl ;
	return 0;
}
