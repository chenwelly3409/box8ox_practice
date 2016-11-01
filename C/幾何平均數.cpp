#include <cstdlib>
#include <iostream>
#include <string>
#include <Math.h>

using namespace std;

int main(int argc, char *argv[])
{
    int num = 0;   // 數入進來的數字
    double sum = 1;  // 乘積總和
    int count = 0;  // 有幾個輸入進來的數字

    cin >> num;

    while ( num > 0 ) {   // 判斷輸入進來的數字大於0
        sum = sum * num ;   // 計算乘積
        count++;            // 每進來一次count+1
        cin >> num;         // ...
    }
    
    sum = pow( sum,1.0/count );   // 處理數字變成n次根

    cout << sum << endl;   // 輸出結果

    system("PAUSE");
    return 0;
}