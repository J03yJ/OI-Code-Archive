#include<bits/stdc++.h>

using namespace std;

ifstream fin("time.in");
ofstream fout("time.out");
#define cin fin
#define cout fout
#define endl '\n'

#define fir(x) (x).first
#define sec(x) (x).second
using pii=pair<int,int>;
const int N=1e5+9;

int ax[N],ay[N],bx[N],by[N],ans[N],t[N],n,m;
#define X(p) (!sec(p)?ax[fir(p)]:bx[fir(p)])
#define Y(p) (!sec(p)?ay[fir(p)]:by[fir(p)])

inline void Solve(vector<pii> &v){
    if(v.size()<=1) return ;
    vector<pii> lv,rv;
    int len=v.size(),mid=v.size()>>1;
    for(int i=0;i<mid;i++) lv.push_back(v[i]);
    for(int i=mid;i<len;i++) rv.push_back(v[i]);
    Solve(lv),Solve(rv);
    vector<int> lq,rq;
    for(pii p:lv) if(sec(p)) lq.push_back(fir(p));
    for(pii p:rv) if(!sec(p)) rq.push_back(fir(p));
    sort(lq.begin(),lq.end(),[](int i,int j){return by[i]>by[j];});
    sort(rq.begin(),rq.end(),[](int i,int j){return ay[i]>ay[j];});
    vector<int> stk;
    for(int i=0,j=0;i<lq.size();i++){
        while(j<rq.size()&&by[lq[i]]<=ay[rq[j]]){
            while(stk.size()&&ax[rq[j]]<=ax[stk.back()]) stk.pop_back();
            if(!stk.size()||ay[rq[j]]<ay[stk.back()]) stk.push_back(rq[j]);
            j++;
        }
        int l=-1,r=stk.size();
        while(l+1<r){
            int mid=l+r>>1;
            if(ay[stk[mid]]>=t[lq[i]]) l=mid;
            else r=mid;
        }
        ans[lq[i]]+=stk.size()-r;
    }
    for(int &i:rq) i=ay[i];
    sort(rq.begin(),rq.end());
    for(int i:lq){
        auto it=lower_bound(rq.begin(),rq.end(),by[i]);
        if(it!=rq.end()) t[i]=min(t[i],*it);
    }
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>ax[i]>>ay[i];
    for(int i=1;i<=m;i++) cin>>bx[i]>>by[i];

    for(int i=1;i<=n;i++){
        int tx=ax[i]+ay[i],ty=ax[i]-ay[i];
        ax[i]=tx,ay[i]=ty;
    }
    for(int i=1;i<=m;i++){
        int tx=bx[i]+by[i],ty=bx[i]-by[i];
        bx[i]=tx,by[i]=ty;
    }

    vector<pii> p;
    for(int i=1;i<=n;i++) p.push_back({i,0});
    for(int i=1;i<=m;i++) p.push_back({i,1});
    sort(p.begin(),p.end(),[](pii p,pii q){return X(p)!=X(q)?X(p)<X(q):Y(p)<Y(q);});
    for(int i=1;i<=m;i++) t[i]=2e9;
    Solve(p);
    for(int i=1;i<=m;i++) cout<<ans[i]<<endl;

    return 0;
}