#include<bits/stdc++.h>

using namespace std;

ifstream fin("happy.in");
ofstream fout("happy.out");
#define cin fin
#define cout fout

#define endl '\n'
#define fir(x) (x).first
#define sec(x) (x).second
using ll=long long;
using pii=pair<int,int>;
const int N=1e6+9;

struct Node{
    int lc,rc,fa,dep;
}tr[N];
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc
#define fa(x) tr[x].fa
#define dep(x) tr[x].dep
inline void PushUp(int x){
    fa(x)=x;
    if(lc(x)) fa(lc(x))=x;
    if(rc(x)) fa(rc(x))=x;
    dep(x)=max(dep(lc(x)),dep(rc(x)))+1;
}

int vis[N];
inline int Build(vector<int> &v,int l,int r){
    if(l>r) return 0;
    int mid=l+r>>1,x=v[mid];
    lc(x)=Build(v,l,mid-1),rc(x)=Build(v,mid+1,r);
    PushUp(x);
    return x;
}
inline void Get(int x,vector<int> &v){
    if(!x) return ;
    Get(lc(x),v);
    v.push_back(x);
    Get(rc(x),v);
}
const int B=120;
inline void Maintain(int x){
    if(dep(x)<=B) return ;
    vector<int> tmp;
    Get(x,tmp);
    Build(tmp,0,tmp.size()-1);
}

mt19937 rng(4649);
inline int Merge(int x,int y){
    if(!x||!y) return x|y;
    if(rng()&1) return rc(x)=Merge(rc(x),y),PushUp(x),x;
    else return lc(y)=Merge(x,lc(y)),PushUp(y),y;
}
inline pii Split(int x,int k){
    if(!x) return {0,0};
    if(x<=k){
        pii res=Split(rc(x),k);
        rc(x)=fir(res);
        PushUp(x);
        return {x,sec(res)};
    }else{
        pii res=Split(lc(x),k);
        lc(x)=sec(res);
        PushUp(x);
        return {fir(res),x};
    }
}
inline int Find(int x){return fa(x)==x?x:Find(fa(x));}
inline int Approx(int x,int k){
    if(!x) return 0;
    if(x<=k) return max(Approx(rc(x),k),x);
    else return Approx(lc(x),k);
}

int w[N],c[N],n,m,tot;
set<int> bel[26];
inline int Pre(int x){return x?*prev(bel[c[x]].lower_bound(x)):0;}
inline int Suc(int x){return *bel[c[x]].upper_bound(x);}
inline void Modify(int x,int ch){
    int y=Pre(x);
    pii yrt=Split(Find(x+1),y); // pre(x) x+1
    pii xrt=Split(Find(x),x); // x suc(x)+1
    Maintain(Merge(fir(yrt),sec(xrt))); // pre(x) -> suc(x)+1
    
    bel[c[x]].erase(x);
    c[x]=ch;
    bel[c[x]].insert(x);

    if(bel[c[x]].size()!=1){
        int z=Pre(x);
        pii zrt=Split(Find(z?z:Suc(x)+1),z); // pre(x) suc(x)+1
        Maintain(Merge(fir(zrt),sec(yrt))); // pre(x) -> x+1
        Maintain(Merge(fir(xrt),sec(zrt))); // x -> suc(x)+1
    }
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        char ch;
        cin>>ch;
        c[i]=c[i+n]=ch-'a';
    }
    for(int i=1;i<=n;i++) cin>>w[i],w[i+n]=w[i];
    tot=n<<1;

    for(int i=0;i<26;i++) bel[i].insert(0),bel[i].insert(tot+1);
    for(int i=1;i<=tot;i++) bel[c[i]].insert(i);
    for(int i=1;i<=tot;i++) fa(i)=i;
    for(int i=tot;i>=1;i--){
        if(vis[i]) continue ;
        vector<int> tmp;
        int cur=i;
        while(cur){
            tmp.push_back(cur);
            vis[cur]=1;
            cur=Pre(cur-1);
        }
        reverse(tmp.begin(),tmp.end());
        Build(tmp,0,tmp.size()-1);
    }

    int t=clock();
    while(m--){
        int op,x;
        cin>>op>>x;
        if(op==1){
            char ch;
            cin>>ch;
            if(double(clock()-t)/CLOCKS_PER_SEC>1) continue ;
            Modify(x,ch-'a');
            Modify(x+n,ch-'a');
        }else if(op==2){
            cin>>w[x];
            w[x+n]=w[x];
        }else if(op==3){
            ll sum=0;
            int l=x,r=x+n-1,cur=Approx(Find(l),r+1);
            while(cur<=r){
                sum+=w[cur++];
                if(Suc(cur)<=r) cur=Approx(Find(cur),r+1);
            }
            cout<<sum<<endl;
        }
    }

    return 0;
}