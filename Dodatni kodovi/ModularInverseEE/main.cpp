#include <iostream>

using namespace std;

int modularInverse(int ,int );

int main()
{
    int a=17;
    int M=43;
    cout << "Modularna inverzija broja " << a << " (mod " << M << ") = " << modularInverse(17,43) << endl;
}

int modularInverse(int a, int M)
{
    int Q,T,R=1,T1=0,T2=1;
    int tempM=M;
    if(a<M)
    {
        int temp=a;
        a=M;
        M=temp;
    }
    Q=a/M;
    R=a%M;
    T=T1-T2*Q;
    while(R!=0)
    {
        a=M;
        M=R;
        T1=T2;
        T2=T;
        Q=a/M;
        R=a%M;
        T=T1-T2*Q;
    }
    if(T2<0)
    {
        return tempM+T2;
    }
    return T2;
}
