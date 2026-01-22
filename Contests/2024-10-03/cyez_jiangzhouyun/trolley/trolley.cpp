#include<bits/stdc++.h>

using namespace std;

ifstream fin("trolley.in");
ofstream fout("trolley.out");
#define cin fin
#define cout fout

#define int long long

const int N=3e2+9;

int _a[N<<1],*a=_a+N,n,k,cur;
int _use[N<<1],*use=_use+N;

signed main(){
    cin>>n>>k;
    for(int i=-n;i<=n;i++) cin>>a[i];

    if(k<0) for(int i=1;i<=n;i++) swap(a[i],a[-i]);
    for(int i=0;i<=n;i++){
        while(use[i]<a[i]&&cur<k){
            use[i]++;
            cur+=i;
        }
        if(cur>=k) break ;
    }
    if(cur<k){
        cout<<""<<endl;
        return 0;
    }
    
    return 0;
}