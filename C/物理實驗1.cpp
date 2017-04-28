#include <cstdlib>
#include <iostream>
#include <string>
#include <Math.h>

using namespace std;

int main(int argc, char *argv[])
{
    float a[] = {244.08, 348.40, 427.09, 494.40};
    float b[] = {244.84, 349.14, 427.83, 494.79};
    float c[] = {245.06, 349.38, 428.07, 495.03};
    float d[] = {243.31, 347.65, 426.34, 493.29};
    float g[] = {-0.09, 0.05, 0.05};

    //float ans[] = {0.3, 1.2, 244.32, 494.38};

    //cout << 2 * ( ans[1]*ans[2] - ans[0]*ans[3] ) / (ans[2]*ans[3]*(ans[3]-ans[2])) << endl;


    
    float sum = 0;

    for( int i = 0 ; i < 3 ; i++ ) {
    	//float HHH = a[i] + b[i] + c[i] + d[i];
    	sum = sum + g[i] * g[i];
    	//cout << sum<<endl;

    	//sum = sum + HHH;
    }
    int M = 3;
    int N = 2;
    
    cout << 0.05/9.54 << endl;
    //cout << a[M] - a[N] << endl;
    //cout << b[M] - b[N] << endl;
    //cout << c[M] - c[N] << endl;
    //cout << d[M] - d[N] << endl;

    //cout << ( a[M] - a[N] + b[M] - b[N] + c[M] - c[N] + d[M] - d[N] ) / 4 << endl;

    system("PAUSE");
    return 0;
}