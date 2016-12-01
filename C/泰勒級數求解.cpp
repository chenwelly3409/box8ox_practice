#include <cstdlib>
#include <iostream>
#include <string>
#include <Math.h>

using namespace std;
double my_exp( double x, int term = 10) {

    double sum = 0.0;

    for ( int i = 0 ; i < term ; i++ ) {
        double temp1 = 1;
        double temp2 = 1;
        for( int j = 0 ; j < i ; j++ ) {
            temp1 = temp1 * x ;
            temp2 = temp2 * i ;
        }

        sum = sum + temp1 / temp2 ;

    }

    return sum;
}

int main(int argc, char *argv[])
{
    double x = 2.0;

    cout << my_exp( x ) << endl;
    cout << my_exp( x, 15 ) << endl;

    system("PAUSE");
    return 0;
}
