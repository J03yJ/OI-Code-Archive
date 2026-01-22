#include<bits/stdc++.h>

using namespace std;

ifstream fin("d.in");
ofstream fout("d.out");
#define cin fin
#define cout fout

#define int long long
#define bint __int128
#define endl '\n'
const int N=8e2+9;
const int p=998244353;

int qpow(int x,int y){
    int m=1;
    while(y){
        if(y&1) m=m*x%p;
        x=x*x%p;
        y>>=1;
    }
    return m;
}
inline bint Gcd(bint x,bint y){
    if(!y) return x;
    else return Gcd(y,x%y);
}
inline int Lcm(vector<int> &v){
    bint A=1,G=1;
    int ans=1;
    vector<bint> tmp;
    tmp.push_back(1);
    for(int i=0;i<v.size();i++){
        bint res=1;
        for(bint x:tmp) res=res*x%v[i];
        res=Gcd(v[i],res);
        v[i]/=res;
        ans=ans*(v[i]%p)%p;
        if(1e35/v[i]>tmp.back()) tmp.back()*=v[i];
        else tmp.push_back(v[i]);
    }
    return ans;
}

int a[N];

signed main(){
    int T;
    cin>>T;
    while(T--){
        int n,q;
        cin>>n>>q;
        for(int i=1;i<=n;i++) cin>>a[i];
        while(q--){
            int m;
            cin>>m;
            vector<int> v;
            for(int i=0,x;i<m;i++){
                cin>>x;
                v.push_back(a[x]);
            }
            cout<<Lcm(v)<<endl;
        }
    }
}