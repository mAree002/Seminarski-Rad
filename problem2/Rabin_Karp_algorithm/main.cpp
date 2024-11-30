#include <iostream>
#include <cstring>

using namespace std;
void rabin_karp(char pat[], char txt[], int q,int d);

int main()
{
    char pattern[]="ko";
    char sentence[]="koliko ko da";
    int q = 10e9+9;
    int d=31;
    rabin_karp(pattern, sentence, q, d);
    return 0;
}


void rabin_karp(char pat[], char txt[], int q,int d)
{
    int M=strlen(pat);
    int N=strlen(txt);
    int p=0;
    int t=0;
    int h=1;
    int i,j;

    for(i=0; i<M-1; i++)
    {
        h=(h*d) %q;
    }

    for (i = 0; i < M; i++)
    {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }

    for (i = 0; i <= N - M; i++)
    {
        if (p == t)
        {
            for (j = 0; j < M; j++)
            {
                if (txt[i + j] != pat[j])
                {
                    break;
                }
            }
            if (j == M)
                cout << "Pattern found at index " << i
                     << endl;
        }

        if (i < N - M)
        {
            t = (d * (t - txt[i] * h) + txt[i + M]) % q;
            if (t < 0)
                t = (t + q);
        }
    }

}
