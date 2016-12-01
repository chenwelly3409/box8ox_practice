#include <cstdlib>
#include <iostream>
#include <string>
#include <Math.h>

using namespace std;

int main(int argc, char *argv[])
{
    float a, b, c;
    cin >> a >> b >> c;

    float s = ( a + b + c ) / 2 ;

    float A = sqrt( s*(s-a)*(s-b)*(s-c) );

    cout << A << endl ;
    system("PAUSE");
    return 0;
}
