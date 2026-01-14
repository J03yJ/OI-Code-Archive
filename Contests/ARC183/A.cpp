#include<bits/stdc++.h>

using namespace std;

const int N=5e2+9;
int cnt[N];

int main(){
    int n,k;
    cin>>n>>k;
    
    for(int i=1;i<=n;i++) cnt[i]=k;
    #define Out(x) cout<<x<<' ',cnt[x]--
    if(n%2==0){
        Out(n/2);
        for(int i=n;i>=1;i--) while(cnt[i]) Out(i);
        cout<<endl;
    }else{
        int pos=n+1>>1;
        while(cnt[pos]) Out(pos);
        if(pos>1) Out(pos-1);
        for(int i=n;i>=1;i--) while(cnt[i]) Out(i);
        cout<<endl;
    }

    return 0;
}