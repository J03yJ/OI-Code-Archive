#include<bits/stdc++.h>

using namespace std;

ifstream fin("game.in");
ofstream fout("game.out");
#define cin fin
#define cout fout

#define int long long
#define ssiz(x) (signed)x.size()
const int N=3e5+9;

int a[N],b[N],ans[N],n;
vector<int> pos,neg;
int Cnt(int k){
    int cur=k,cnt=0;
    for(auto i:pos) if(a[i]<=cur) cur+=b[i]-a[i],cnt++;
    for(auto i:neg) if(a[i]<=cur) cur+=b[i]-a[i],cnt++;
    return cnt;
}
void Solve(int l,int r,int L,int R){
    if(l>r) return ;
    if(L==R){
        for(int i=l;i<=r;i++) ans[i]=L;
        return ;
    }
    int lf=L-1,rf=R+1,m=(l+r)>>1;
    while(lf+1<rf){
        int mid=(lf+rf)>>1;
        if(Cnt(mid)>=m) rf=mid;
        else lf=mid;
    }
    ans[m]=rf;
    Solve(l,m-1,L,R),Solve(m+1,r,L,R);
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
    for(int i=1;i<=n;i++){
        if(a[i]>b[i]) neg.push_back(i);
        else pos.push_back(i);
    }
    sort(pos.begin(),pos.end(),[](int x,int y){return a[x]<a[y];});
    sort(neg.begin(),neg.end(),[](int x,int y){return b[x]>b[y];});

    Solve(1,n,0,1e18);
    for(int i=1;i<=n;i++) cout<<ans[i]<<' ';cout<<endl;
    
    return 0;
}