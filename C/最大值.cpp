#include <cstdlib>
#include <iostream>
#include <string>
#include <Math.h>

using namespace std;

int main(int argc, char *argv[])
{
    int num = 0;
    int input = 0;
    cout << "請問要輸入幾個數字 : " ; 
    cin >> num;

    int max = -9999;

    for ( int i  = 0 ; i < num ; i++ ) {
        cin >> input ;
        if( input > max ) {
            max = input;
        }
    }

    cout << "最大的數為: " << max ;


    system("PAUSE");
    return 0;
}