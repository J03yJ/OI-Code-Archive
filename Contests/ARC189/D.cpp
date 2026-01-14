#include<bits/stdc++.h>

using namespace std;

#define int long long
#define ssiz(x) (signed)x.size()
const int N=2e6+9;

struct Seg{
    int l,r,ans;
    Seg(){}
    Seg(int _l,int _r,int _ans){
        l=_l,r=_r,ans=_ans;
    }
    bool operator <(Seg s)const{return l<s.l;}
};

int a[N],s[N],pos[N],ans[N],vis[N],n,cnt;
vector<int> p[N];

#define Sum(l,r) (s[r]-s[(l)-1])
set<Seg> tr;
auto Find(int x){return --tr.lower_bound(Seg(x+1,0,0));}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i],s[i]=s[i-1]+a[i];

    vector<int> val;
    for(int i=1;i<=n;i++) val.push_back(a[i]);
    sort(val.begin(),val.end());
    val.erase(unique(val.begin(),val.end()),val.end());
    for(int i=1;i<=n;i++){
        pos[i]=lower_bound(val.begin(),val.end(),a[i])-val.begin();
        p[pos[i]].push_back(i);
    }

    tr.insert(Seg(1,n,Sum(1,n)));
    vis[0]=vis[n+1]=1;
    for(int i=ssiz(val)-1;~i;i--){
        for(int x:p[i]) ans[x]=Find(x)->ans,vis[x]=1;
        for(int x:p[i]){
            auto it=Find(x);
            int l=it->l,r=it->r,ans=it->ans;
            tr.erase(it);
            if(l<x){
                if(Sum(l,x-1)>val[i]) tr.insert(Seg(l,x-1,ans));
                else tr.insert(Seg(l,x-1,Sum(l,x-1)));
            }
            if(r>x){
                if(Sum(x+1,r)>val[i]) tr.insert(Seg(x+1,r,ans));
                else tr.insert(Seg(x+1,r,Sum(x+1,r)));
            }
        }
        for(int x:p[i]) if(vis[x-1]&&vis[x+1]) ans[x]=a[x];
    }

    for(int i=1;i<=n;i++) cout<<ans[i]<<' ';cout<<endl;

    return 0;
}