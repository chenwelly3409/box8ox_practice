#include <cstdlib>
#include <iostream>
#include <string>
#include <Math.h>

using namespace std;

double det( double a, double b, double c ) {
    return b*b - 4 * a * c;
}

bool solvel( double a, double b, double c , double & x1, double & x2 ) {
    if( det( a, b, c ) >= 0 ) {
        x1 = ( -b + sqrt( det( a, b, c ) ) ) / 2*a;
        x2 = ( -b - sqrt( det( a, b, c ) ) ) / 2*a;
        return true;
    }
    else {
        return false;
    }
}

int main(int argc, char *argv[])
{
    cout << "請輸入1元2次方程式ax^2 + bx + c = 0，的 a,b,c " << endl;

    double a, b, c;
    cin >> a >> b >> c;
    double x1, x2;

    if( solvel( a, b, c, x1, x2 ) == true ) {
        cout << "一元二次方程式的根為: " << endl;
        cout << "x1 = " << x1 << endl;
        cout << "x2 = " << x2 << endl;
    }
    else {
        cout << "一元二次方程式沒有實數解。" << endl;
    }

    system("PAUSE");
    return 0;
}
