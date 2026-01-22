#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=4e5+9;
const int lgV=60;

struct Basis{
    ll b[lgV];int w[lgV];
    inline void Insert(ll x,int k){
        for(int i=lgV-1;~i;i--){
            if(~x>>i&1) continue ;
            if(k>w[i]){
                swap(b[i],x),swap(w[i],k);
                if(!x) break ;
            }
            x^=b[i];
        }
    }
    inline bool Find(ll x,int k){
        for(int i=lgV-1;~i;i--) if(w[i]>=k&&(x>>i&1)) x^=b[i];
        return !x;
    }
}b[N];

int n,q;
ll a[N];

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        b[i]=b[i-1];
        b[i].Insert(a[i],i);
    }

    while(q--){
        int l,r;ll x;
        cin>>l>>r>>x;

        if(b[r].Find(x,l)) cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
    }

    return 0;
}