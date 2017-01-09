#include <cstdlib>
#include <iostream>
#include <string>
#include <Math.h>

using namespace std;

template <class X>
void max(X[], int,int &);

int main() {
    int a[] = {5, 3, 11, 6, 8, 9, 20, 11};
    int m = 0;
    max(a,sizeof(a)/sizeof(int),m);


    cout << m << endl;

    return 0;
}

template <class X>
void max(X a[], int length, int & m ) {
	for( int i = 0 ; i < length ; i++ ) {


		if( a[i] > m ) {
			m = a[i];
		}
	}
}
