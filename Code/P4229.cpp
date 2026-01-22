#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;
const int mod=998244353;
inline void AddAs(int &x,int y){if((x+=y)>=mod) x-=mod;}
inline void SubAs(int &x,int y){if((x-=y)<0) x+=mod;}
inline void MulAs(int &x,int y){x=1ll*x*y%mod;}
inline int Add(int x,int y){if((x+=y)>=mod) x-=mod;return x;}
inline int Sub(int x,int y){if((x-=y)<0) x+=mod;return x;}
inline int Mul(int x,int y){return 1ll*x*y%mod;}
inline int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=1ll*res*x%mod;
        x=1ll*x*x%mod;
        y>>=1;
    }
    return res;
}
#define Inv(x) QPow(x,mod-2)

int ql[N],qr[N],qk[N],n,m,q,tot,num;
vector<int> val,tmp;
inline void Disc(){
    for(int i=1;i<=q;i++){
        val.push_back(ql[i]);
        val.push_back(qr[i]+1);
        tmp.push_back(qk[i]);
    }
    val.push_back(0);
    val.push_back(1);
    val.push_back(n+1);
    tmp.push_back(0);
    tmp.push_back(m+1);
    sort(val.begin(),val.end());
    sort(tmp.begin(),tmp.end());
    val.erase(unique(val.begin(),val.end()),val.end());
    tmp.erase(unique(tmp.begin(),tmp.end()),tmp.end());
    tot=val.size()-2;
    num=tmp.size()-1;
    for(int i=1;i<=q;i++){
        ql[i]=lower_bound(val.begin(),val.end(),ql[i])-val.begin();
        qr[i]=upper_bound(val.begin(),val.end(),qr[i])-val.begin()-1;
        qk[i]=lower_bound(tmp.begin(),tmp.end(),qk[i])-tmp.begin();
    }
}
int lim[N];
vector<int> st[N],ed[N],pnt[N],qry[N];
inline void GetLim(){
    for(int i=1;i<=q;i++) st[ql[i]].push_back(i);
    for(int i=1;i<=q;i++) ed[qr[i]].push_back(i);
    priority_queue<int> p,r;
    p.push(-num);
    for(int i=1;i<=tot;i++){
        for(int j:st[i]) p.push(-qk[j]);
        while(r.size()&&p.top()==r.top()) p.pop(),r.pop();
        lim[i]=-p.top();
        for(int j:ed[i]) r.push(-qk[j]);
    }
    for(int i=1;i<=tot;i++) pnt[lim[i]].push_back(i);
    for(int i=1;i<=q;i++) qry[qk[i]].push_back(i);
}
int f[N],lp[N];
inline int Work(int k){
    if(tmp[k]==1) return 1;
    const int n=pnt[k].size();
    pnt[k].insert(pnt[k].begin(),0);
    for(int i=0;i<=n;i++) lp[i]=-1;
    for(int i:qry[k]){
        int l=lower_bound(pnt[k].begin(),pnt[k].end(),ql[i])-pnt[k].begin();
        int r=upper_bound(pnt[k].begin(),pnt[k].end(),qr[i])-pnt[k].begin()-1;
        if(l>r) return 0;
        lp[r]=max(lp[r],l);
    }
    int sum=f[0]=1,tag=1;
    for(int i=1,j=0;i<pnt[k].size();i++){
        int w0=QPow(tmp[k]-1,val[pnt[k][i]+1]-val[pnt[k][i]]);
        int w1=Sub(QPow(tmp[k],val[pnt[k][i]+1]-val[pnt[k][i]]),w0);
        MulAs(tag,w0);
        f[i]=Mul(Inv(tag),Mul(sum,w1));
        MulAs(sum,w0);
        AddAs(sum,Mul(f[i],tag));
        while(j<lp[i]) SubAs(sum,Mul(f[j++],tag));
    }
    return sum;
}

inline void Clear(){
    val.clear();
    tmp.clear();
    for(int i=1;i<=tot;i++){
        st[i].clear();
        ed[i].clear();
        f[i]=lp[i]=0;
    }
    for(int i=1;i<=num;i++){
        pnt[i].clear();
        qry[i].clear();
    }
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n>>q>>m;
        for(int i=1;i<=q;i++) cin>>ql[i]>>qr[i]>>qk[i];
        Disc();

        int ans=1;
        GetLim();
        for(int i=1;i<num;i++) MulAs(ans,Work(i));
        for(int i:pnt[num]) MulAs(ans,QPow(m,val[i+1]-val[i]));
        Clear();

        cout<<ans<<endl;
    }

    return 0;
}