#include<bits/stdc++.h>

using namespace std;

ifstream fin("ring.in");
ofstream fout("ring.out");
#define cin fin
#define cout fout
#define endl '\n'

#define fir(x) (x).first
#define sec(x) (x).second
using pii=pair<int,int>;
const int N=2e3+9;

int n,m,L,B;
vector<pii> ans;
inline void Init(int x){
    x*=L;
    for(int i=0;i<L;i++){
        int j=(i+1)%L;
        ans.push_back({x+i,x+j});
    }
}
inline void Link(int x,int y,int st){
    x*=L,y*=L;
    for(int i=0,j=st;i<L;i++,j=(j+B)%L){
        ans.push_back({x+i,y+j});
    }
}
inline int E(int l){
    int b=l>>1;
    int m=n/l,cnt=0;
    for(int i=0;i<m;i++) cnt+=l;
    for(int k=0;k<l;k++){
        int l=1<<(k<<1);
        for(int i=l;i<m;i++) cnt+=l;
    }
    for(int i=m*l;i<n;i++) cnt++;
    return cnt;
}

signed main(){
    cin>>n;

    L=5,B;
    for(int i:{5,7,11,13,17,19}) if(E(i)>E(L)) L=i;

    m=n/L,B=L>>1;
    for(int i=0;i<m;i++) Init(i);
    for(int k=0;k<L;k++){
        int l=1<<(k<<1);
        for(int i=l;i<m;i++) Link(i-l,i,k);
    }
    for(int i=m*L;i<n;i++) ans.push_back({i-m*L,i});

    cout<<ans.size()<<endl;
    for(pii p:ans) cout<<fir(p)+1<<' '<<sec(p)+1<<endl;

    return 0;
}