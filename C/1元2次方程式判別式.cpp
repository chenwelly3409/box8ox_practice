#include <cstdlib>
#include <iostream>
#include <string>
#include <Math.h>

using namespace std;

double det( double a, double b, double c ) {
    return b*b - 4 * a * c;
}

int main(int argc, char *argv[])
{
    cout << "請輸入1元2次方程式ax^2 + bx + c = 0，的 a,b,c " << endl;

    double a, b, c;
    cin >> a >> b >> c;

    double d = det(a,b,c);

    if( d > 0 ) {
        cout << "判別式大於0" << endl;
    }
    else if ( d == 0 ) {
        cout << "判別式等於0" << endl;
    }
    else {
        cout << "判別式小於0" << endl;
    }

    system("PAUSE");
    return 0;
}
