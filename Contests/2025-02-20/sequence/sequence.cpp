#include<bits/stdc++.h>

using namespace std;

ifstream fin("sequence.in");
ofstream fout("sequence.out");
#define cin fin
#define cout fout

using ll=long long;

int n,m;
inline ll Encode(vector<int> &a){
    ll res=0;
    for(int i=n;i>=1;i--) res=res*(m<<1)+a[i];
    return res;
}
inline vector<int> Decode(ll x){
    vector<int> res(n+1,0);
    for(int i=1;i<=n;i++){
        res[i]=x%(m<<1);
        x/=(m<<1);
    }
    return res;
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n>>m;
        vector<int> a(n+1,0),b(n+1,0);
        for(int i=1;i<=n;i++) cin>>a[i];
        for(int i=1;i<=n;i++) cin>>b[i];

        ll s=Encode(a),t=Encode(b);
        map<ll,int> f;
        f[s]=1;
        queue<ll> q;
        q.push(s);
        while(q.size()){
            ll x=q.front();
            q.pop();
            vector<int> a=Decode(x);
            for(int l=1;l<=n;l++){
                for(int r=l;r<=n;r++){
                    vector<int> c=a;
                    int mina=m<<1|1,minb=m<<1|1;
                    for(int i=l;i<=r;i++) mina=min(mina,c[i]);
                    for(int i=l;i<=r;i++) minb=min(minb,b[i]);
                    if(mina==minb) continue ;
                    for(int i=l;i<=r;i++) if(c[i]==mina) c[i]=minb;
                    ll y=Encode(c);
                    if(f[y]) continue ;
                    f[y]=f[x]+1;
                    q.push(y);
                }
            }
        }

        cout<<f[t]-1<<endl;
    }

    return 0;
}