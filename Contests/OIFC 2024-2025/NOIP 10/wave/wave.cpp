#include<bits/stdc++.h>

using namespace std;

ifstream fin("wave.in");
ofstream fout("wave.out");
#define cin fin
#define cout fout

#define int long long
#define ssiz(x) (signed)x.size()
#define endl '\n'
const int N=3e5+9;
const int mod=998244353;

int n,m,B,cnt;

signed main(){
    cin>>n>>m;
    vector<int> a(n+1,0);
    for(int i=1;i<=n;i++) cin>>a[i];

    if(!n){
        while(m--){
            int op,x,y;
            cin>>op>>x>>y;
            cout<<0<<endl;
        }
        return 0;
    }
    
    vector<int> s(a);
    for(int i=1;i<=n;i++) s[i]=(s[i-1]+a[i])%mod;
    vector<int> c={1};
    while(m--){
        int op,x,y;
        cin>>op>>x>>y;
        if(op==1){
            s.push_back(s.back());
            for(int i=ssiz(s)-1;i;i--) s[i]=(s[i]*x%mod+s[i-1]*y%mod)%mod;
        }else cout<<(s[y]-s[x-1]+mod)%mod<<endl;
    }

    return 0;
}