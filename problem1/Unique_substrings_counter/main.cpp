#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

int unique_substrings_counter(string const &);

int main()
{

    char s[]="abklaboprsrs";
    cout<<unique_substrings_counter(s)<<endl;
}

int unique_substrings_counter(string const &s){
    int n=s.size();
    int cnt=0;
    const int p=31;
    const int m=1e9+9;
    vector<long long> p_pow(n);
    vector<long long> h(n+1,0);
    p_pow[0]=1;
    h[0]=0;

    for(int i=1;i<n;i++){
        p_pow[i]=p*p_pow[i-1]%m;
    }

    for(int i=0;i<n;i++){
        h[i+1]=(h[i]+(s[i]-'a'+1)*p_pow[i])%m;
    }

    for(int l=1; l<=n; l++){
       unordered_set<long long> hs;
       for(int i=0; i<=n-l;i++){
        long long curr_h=(h[i+l]-h[i]+m)%m;
        curr_h= (curr_h*p_pow[n-i-1])%m;
        hs.insert(curr_h);
       }
       cnt+=hs.size();
    }

    return cnt;

}
