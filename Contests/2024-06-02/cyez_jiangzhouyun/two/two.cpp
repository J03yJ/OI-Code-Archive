#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;
const int inf=2e9;

ifstream fin("two.in");
ofstream fout("two.out");
#define cin fin
#define cout fout

int lc[N],rc[N],k[N];
int mx[N],mn[N];
void dfs(int x){
    if(!x) return ;
    dfs(lc[x]);dfs(rc[x]);
    mx[x]=max(k[x],max(mx[lc[x]],mx[rc[x]]));
    mn[x]=min(k[x],min(mn[lc[x]],mn[rc[x]]));
}

pair<int,int> s[N];
struct Val{
    int cnt;vector<int> v;
    Val(){}
    Val(int *a,int n){
        map<int,bool> mp;
        vector<int> tmp;
        for(int i=1;i<=n;i++) if(!mp[a[i]]) mp[a[i]]=1,tmp.push_back(a[i]);
        sort(tmp.begin(),tmp.end());
        v.push_back(tmp.front()-1);
        for(int x:tmp) v.push_back(x);
    }
    int Ask(int val){
        auto it=lower_bound(v.begin(),v.end(),val);
        if(it==v.begin()) return 0;
        else return it-v.begin();
    }
};

int tr[N],n;
void add(int x,int k){
    while(x<=n){
        tr[x]+=k;
        x+=x&-x;
    }
}
int ask(int x){
    int sum=0;
    while(x){
        sum+=tr[x];
        x&=x-1;
    }
    return sum;
}
int suc(int x){
    if(x<1) x=1;
    return ask(n)-ask(x-1);
}

int ans[N];
struct Q{
    pair<int,int> s;
    int id,k;
    bool operator <(Q x){
        return s.first<x.s.first;
    }
    Q(){}
    Q(pair<int,int> S,int Id,int K){
        s=S;id=Id;k=K;
    }
};
vector<Q> q;

int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>lc[i]>>rc[i]>>k[i];
    mx[0]=-inf;mn[0]=inf;
    dfs(1);

    for(int i=1;i<=n;i++) s[i]=make_pair(mn[i],mx[i]);
    sort(s+1,s+n+1);
    Val Mx(mx,n),Mn(mn,n);

    int m;
    cin>>m;
    for(int i=1;i<=m;i++){
        int l,r;
        cin>>l>>r;
        ans[i]=1;
        q.push_back(Q(make_pair(l-1,l),i,2));
        q.push_back(Q(make_pair(r,r+1),i,2));
        q.push_back(Q(make_pair(l-1,r+1),i,-2));
    }
    sort(q.begin(),q.end());

    int j=0;
    for(int i=1;i<=n&&j<q.size();i++){
        while(j<q.size()&&q[j].s.first<s[i].first){
            ans[q[j].id]+=suc(Mx.Ask(q[j].s.second))*q[j].k;
            j++;
        }
        add(Mx.Ask(s[i].second),1);
    }
    while(j<q.size()){
        ans[q[j].id]+=suc(Mx.Ask(q[j].s.second))*q[j].k;
        j++;
    }

    #define endl '\n'
    for(int i=1;i<=m;i++) cout<<ans[i]<<endl;

    return 0;
}