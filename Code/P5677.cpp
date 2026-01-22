#include<bits/stdc++.h>

using namespace std;

const int N=3e5+9;

int n,m;
int a[N],per[N];
pair<int,int> q[N];
inline void ins(vector<pair<int,int>> &v,pair<int,int> p){
    if(p.first>p.second) swap(p.first,p.second);
    v.push_back(p);
}
bool cmp(pair<int,int> a,pair<int,int> b){
    return a.second<b.second;
}
bool Icmp(int x,int y){
    return cmp(q[x],q[y]);
}

int tr[N];
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

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=m;i++) cin>>q[i].first>>q[i].second;

    if(n==1){
        cout<<0<<endl;
        return 0;
    }

    set<pair<int,int>> s;
    vector<pair<int,int>> tmp;
    for(int i=1;i<=n;i++) s.insert({a[i],i});
    for(int i=1;i<=n;i++){
        if(i==s.begin()->second){
            int y=s.upper_bound({a[i],i})->second;
            ins(tmp,{i,y});
        }
        else if(s.upper_bound({a[i],i})==s.end()){
            int y=(--s.lower_bound({a[i],i}))->second;
            ins(tmp,{i,y});
        }
        else{
            int u=s.upper_bound({a[i],i})->second,v=(--s.lower_bound({a[i],i}))->second;
            if(abs(a[u]-a[i])<=abs(a[v]-a[i])) ins(tmp,{i,u});
            if(abs(a[u]-a[i])>=abs(a[v]-a[i])) ins(tmp,{i,v});
        }
    }

    for(int i=1;i<=m;i++) per[i]=i;
    sort(tmp.begin(),tmp.end(),cmp);
    sort(per+1,per+m+1,Icmp);

    long long ans=0;
    for(int i=1,j=1,k=0;i<=n;i++){
        while(k<tmp.size()&&tmp[k].second==i) add(tmp[k++].first,1);
        while(j<=m&&q[per[j]].second==i){
            ans+=1ll*(ask(n)-ask(q[per[j]].first-1))*per[j];
            j++;
        }
    }

    cout<<ans<<endl;

    return 0;
}