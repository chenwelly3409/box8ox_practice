#include <cstdlib>
#include <iostream>
#include <string>
#include <Math.h>

#define _USE_MATH_DEFINES // for C++
#include <cmath>

using namespace std;

double area( double a, double b, double c ) {
    float s = ( a + b + c ) / 2 ;

    return sqrt( s*(s-a)*(s-b)*(s-c) );
}
double area( double a, double b ) {
    return a*b ;
}
double area( double a ) {
    return a*a*M_PI;
}



int main(int argc, char *argv[])
{
    cout << "請輸入欲求形狀之面積:" << endl;
    cout << "1. 三角形" << endl << "2. 長方形" << endl << "3. 圓形" << endl;
    int choose = 0;

    double a = 0;
    double b = 0;
    double c = 0;

    double ans = 0;

    cout << "請選擇: ";
    cin >> choose ;

    if( choose == 1 ) {
        cout << "請輸入三角形三邊長: " << endl;
        cin >> a >> b >> c ;
        ans = area( a, b, c );
    }
    else if ( choose == 2 ) {
        cout << "請輸入長方形邊長: " << endl;
        cin >> a >> b;
        ans = area( a, b );
    }
    else if ( choose == 3 ){
        cout << "請輸入半徑: " << endl;
        cin >> a;
        ans = area( a );
    }
    else {
        cout << "輸入錯誤" << endl;
    }

    cout << "面積為: " << ans << endl ;
    system("PAUSE");
    return 0;
}
