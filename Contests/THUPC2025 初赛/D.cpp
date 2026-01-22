#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=1e5+9;
const int lgV=30;

int a[N],ans[N],vis[N],inq[N],c[N],n,lim;
int fa[N],siz[N],cnt[N];
int Find(int x){
    if(x==fa[x]) return x;
    else return Find(fa[x]);
}
inline int Query(int x){
    if(x==fa[x]) return cnt[x];
    else return cnt[x]+Query(fa[x]);
}
int Merge(int x,int y){
    x=Find(x),y=Find(y);
    if(siz[x]<siz[y]) swap(x,y);
    cnt[y]-=cnt[x];
    fa[y]=x;
    siz[x]+=siz[y];
    return x;
}

#define Re(a) a.x
#define Rsh(a) a.cnt
struct Num{
    int x,cnt;
    void R(){while(!(x&1)) x>>=1,cnt++;}
    Num(){}
    Num(int _x,int _cnt){x=_x,cnt=_cnt,R();}
    bool operator <(Num p)const{
        if(abs(cnt-p.cnt)>30) return cnt<p.cnt;
        long long a=x,b=p.x;
        if(cnt>p.cnt) a<<=cnt-p.cnt;
        else b<<=p.cnt-cnt;
        return a<b;
    }
};

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'

    cin>>n>>lim;
    for(int i=1;i<=n;i++) cin>>a[i];

    map<Num,int> mp;
    for(int i=1;i<=n;i++){
        fa[i]=i,siz[i]=1,cnt[i]=0;
        Num cur(a[i],0);
        if(!mp[cur]) mp[cur]=i;
        else mp[cur]=Merge(mp[cur],i);
    }

    int t=0,flag=0;
    priority_queue<Num> q;
    for(auto p:mp) q.push(p.first),inq[p.second]=1;
    while(q.size()){
        if(Rsh(q.top())<-30&&!flag){
            t=lim/n;
            lim%=n;
            flag=1;
        }
        Num m=q.top();q.pop();
        int x=mp[m];
        if(lim<=siz[x]){
            vector<int> nt,mx;
            for(int i=1;i<=n;i++){
                if(Find(i)!=x) continue ;
                if(Query(i)) mx.push_back(i);
                else nt.push_back(i);
            }
            sort(nt.begin(),nt.end(),greater<int>());
            sort(mx.begin(),mx.end(),[](int x,int y){
                if(a[x]!=a[y]) return a[x]<a[y];
                else return x>y;
            });
            while(nt.size()&&lim) lim--,ans[nt.back()]++,nt.pop_back();
            while(mx.size()&&lim) lim--,ans[mx.back()]++,mx.pop_back();
            break ;
        }else{
            lim-=siz[x],mp.erase(m);
            cnt[x]++;
            Rsh(m)--;
            if(!mp[m]) mp[m]=x,q.push(m);
            else mp[m]=Merge(mp[m],x);
        }
    }

    for(int i=1;i<=n;i++) ans[i]+=Query(i)+t;
    for(int i=1;i<=n;i++) cout<<ans[i]<<' ';cout<<endl;

    return 0;
}