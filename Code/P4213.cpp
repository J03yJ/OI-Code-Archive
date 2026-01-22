#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=1e5+9;

int sqr,n;

bool ntp[N];
int pri[N],cnt;
void InitP(){
    pri[0]=1;
    for(int i=2;i<=sqr;i++){
        if(!ntp[i]) pri[++cnt]=i;
        for(int j=1;j<=cnt&&pri[j]*i<=sqr;j++){
            ntp[pri[j]*i]=1;
            if(i%pri[j]==0) break ;
        }
    }
}

namespace Phi{
    int S(int x,int k){
        if(pri[k]>x) return 0;
        
    }
}

signed main(){

}