#include <cstdlib>
#include <iostream>
#include <string>
#include <Math.h>

using namespace std;
void rev_ary(int a[], int size );

int main() {
    int a[] = {5, 3, 11, 6, 8, 9, 20, 11};
    int size = sizeof(a)/sizeof(int);

    rev_ary( a, size );

    for( int i = 0 ; i < size ; i++ ) {
        cout << a[i] << endl;
    }

    return 0;
}

void rev_ary(int a[], int size ) {
    int b[size];

    for( int i = 0 ; i < size ; i ++ ) {
        b[i] = a[i];
    }

    for( int i = 0 ; i < size ; i++ ) {
        a[i] = b[size-i-1];
    }


}
