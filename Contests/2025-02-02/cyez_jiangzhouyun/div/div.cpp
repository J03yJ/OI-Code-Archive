#include<bits/stdc++.h>

using namespace std;

ifstream fin("div.in");
ofstream fout("div.out");
#define cin fin
#define cout fout
#define endl '\n'

#define fir(x) x.first
#define sec(x) x.second
using pii=pair<int,int>;
const int N=2e6+9;

int a[N],c[N],n,m;
vector<int> val;

template<class T> struct DelHeap{
    priority_queue<T> p,q;
    inline void Insert(T x){p.push(x);}
    inline void Erase(T x){q.push(x);}
    T Top(){
        while(q.size()&&p.top()==q.top()) p.pop(),q.pop();
        return p.top();
    }
    inline int Ssiz(){return p.size()-q.size();}
};
int t[N],tot;
bool Check(){
    for(int i=0;i<tot;i++) if(t[i]) return 0;
    return 1;
}
signed main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n>>m;
        for(int i=1;i<=n;i++) cin>>c[i]>>a[i],a[i]%=m;

        vector<int> ans;
        int sum=0;
        for(int i=1;i<=n;i++) sum+=c[i];
        if(sum%m==0) ans.push_back(1);

        for(int i=1;i<=n;i++){
            for(int k=0;k<20;k++) val.push_back((a[i]+k)%m);
        }
        sort(val.begin(),val.end());
        val.erase(unique(val.begin(),val.end()),val.end());
        tot=val.size();
        for(int i=1;i<=n;i++){
            int pos=lower_bound(val.begin(),val.end(),a[i])-val.begin();
            t[pos]-=c[i],t[(pos+1)%tot]+=c[i];
        }
        if(Check()){
            cout<<-1<<endl;
            continue ;
        }

        DelHeap<pii> q;
        DelHeap<int> mx,mn;
        vector<pii> roll;
        auto Insert=[&q,&mx,&mn](int x){
            q.Insert({abs(t[x]),x});
            mx.Insert(t[x]),mn.Insert(-t[x]);
        };
        auto Erase=[&q,&mx,&mn,&roll](int x,bool f=1){
            q.Erase({abs(t[x]),x});
            mx.Erase(t[x]),mn.Erase(-t[x]);
            if(f) roll.push_back({x,t[x]});
        };
        auto RollBack=[&roll,&Insert,&Erase](){
            while(roll.size()){
                Erase(fir(roll.back()),0);
                t[fir(roll.back())]=sec(roll.back());
                Insert(fir(roll.back()));
                roll.pop_back();
            }
        };

        for(int i=0;i<tot;i++) Insert(i);

        for(int x=2;x<=n;x++){
            while(fir(q.Top())>=x){
                int i=sec(q.Top()),j=(i+1)%tot;
                Erase(i),Erase(j);
                t[j]+=t[i]/x,t[i]%=x;
                Insert(i),Insert(j);
            }
            if(mx.Top()==-mn.Top()){
                int y=mx.Top();
                if(y==0||y==x-1||y==-(x-1)) ans.push_back(x);
            }
            RollBack();
        }

        cout<<ans.size()<<endl;
        for(int x:ans) cout<<x<<' ';cout<<endl;

        val.clear();
        for(int i=0;i<tot;i++) t[i]=0;
    }

    return 0;
}