#include<bits/stdc++.h>

using namespace std;

ifstream fin("chat.in");
ofstream fout("chat.out");
#define cin fin
#define cout fout
#define endl '\n'

#define fir(p) p.first
#define sec(p) p.second
using pii=pair<int,int>;
using ll=long long;
const int N=1e6+9;

int a[N],b[N],typ[N],d[N],c[N],n,m;
template<class T> struct DelHeap{
    priority_queue<T> p,q;
    inline void Insert(T x){p.push(x);}
    inline void Erase(T x){q.push(x);}
    inline T Top(){
        while(q.size()&&p.top()==q.top()) p.pop(),q.pop();
        return p.top();
    }
    inline size_t Size(){return p.size()-q.size();}
};
vector<int> v[N][2];

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i]>>b[i];

    for(int i=1;i<=n;i++) typ[i]=b[i]>(m>>1),d[i]=min(b[i],m-b[i]);
    
    vector<int> p(n),chs[2];
    iota(p.begin(),p.end(),1);
    sort(p.begin(),p.end(),[](int x,int y){
        if(d[x]^d[y]) return d[x]<d[y];
        else return typ[x]<typ[y];
    });
    int lcnt=0,rcnt=0,cnt=0,tot[2]={0,0};
    for(int i:p){
        c[a[i]]=max(c[a[i]],lcnt)+1;
        if(!typ[i]) rcnt++,tot[0]++;
        else{
            lcnt++;
            int tmp=min(cnt+1,lcnt+rcnt-c[a[i]]);
            if(tmp>cnt) chs[1].push_back(i),tot[1]++;
            cnt=tmp;
        }
    }
    
    for(int i=1;i<=n;i++) if(!typ[i]) v[a[i]][0].push_back(i);
    for(int i:chs[1]) v[a[i]][1].push_back(i);
    int pos=0,del=0;
    DelHeap<pii> h;
    for(int i:chs[1]) h.Insert({d[i],i});
    for(int i=1;i<=n;i++){
        vector<int> rllb;
        for(int j:v[i][1]) rllb.push_back(j),h.Erase({d[j],j});
        sort(v[i][0].begin(),v[i][0].end(),[](int x,int y){return b[x]>b[y];});
        int num=0;
        for(int j:v[i][0]){
            if(!h.Size()) break ;
            int x=sec(h.Top());
            if(b[x]+b[j]<=m){
                rllb.push_back(x);
                h.Erase({d[x],x});
                num++;
            }
        }
        for(int j:rllb) h.Insert({d[j],j});
        int ng=v[i][0].size()-num;
        if(ng>(tot[0]-tot[1]>>1)){
            pos=i,del=(ng<<1)-(tot[0]-tot[1]);
            break ;
        }
    }
    if(!pos) del=tot[0]-tot[1]&1;

    vector<int> buf,q(chs[1]);
    if(pos){
        for(int i=1;i<=n;i++){
            if(i==pos) q.insert(q.end(),v[i][0].begin(),v[i][0].end());
            else chs[0].insert(chs[0].end(),v[i][0].begin(),v[i][0].end());
        }
    }else{
        for(int i=1;i<=n;i++){
            if(typ[i]) continue ;
            if(del) q.push_back(i);
            else chs[0].push_back(i);
        }
    }
    lcnt=rcnt=cnt=0;
    for(int i=1;i<=n;i++) c[i]=0;
    sort(q.begin(),q.end(),[](int x,int y){
        if(d[x]^d[y]) return d[x]>d[y];
        else return typ[x]>typ[y];
    });
    for(int i:q){
        c[a[i]]=max(c[a[i]],lcnt)+1;
        if(typ[i]) rcnt++;
        else{
            lcnt++;
            int tmp=min(cnt+1,lcnt+rcnt-c[a[i]]);
            if(tmp>cnt) chs[0].push_back(i);
            else buf.push_back(i);
            cnt=tmp;
        }
    }
    sort(buf.begin(),buf.end(),[](int x,int y){return b[x]>b[y];});
    while(del--) buf.pop_back();

    ll ans=0;
    for(int x:chs[0]) ans+=b[x];
    for(int x:chs[1]) ans+=b[x];
    for(int x:buf) ans+=b[x];

    cout<<ans<<endl;

    return 0;
}