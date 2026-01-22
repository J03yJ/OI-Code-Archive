#include<bits/stdc++.h>

using namespace std;

const int mod=998244353;
inline void AddAs(int &x,int y){x+=y;if(x>=mod) x-=mod;}
inline void SubAs(int &x,int y){x-=y;if(x<0) x+=mod;}
inline int Add(int x,int y){x+=y;return x>=mod?x-mod:x;}
inline int Sub(int x,int y){x-=y;return x<0?x+mod:x;}

int main(){
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        vector<int> a(n+1,0),f(n+1,0);
        for(int i=1;i<=n;i++) cin>>a[i];

        f[0]=1;
        for(int i=1;i<=n;i++){
            if(a[i]==a[i-1]) AddAs(f[i],f[i-1]);
            if(i>1&&a[i]==a[i-2]+1) AddAs(f[i],f[i-2]);
        }

        cout<<Add(f[n],f[n-1])<<endl;
    }
}