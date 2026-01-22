#include<bits/stdc++.h>

using namespace std;

ifstream fin("math.in");
ofstream fout("math.out");
#define cin fin
#define cout fout

#define int long long
const int N=2e5+9;

vector<int> a[N];
pair<int,int> c[N];
bool f[N];
int calcA(int x,int y,int op){
    int ans=0;
    if(op){
        for(int i=0,j=0;i<a[x].size();i++){
            while(j<a[y].size()&&a[y][j]<=a[x][i]) j++;
            ans+=j;
        }
    }else{
        for(int i=0,j=0;i<a[x].size();i++){
            while(j<a[y].size()&&a[y][j]<a[x][i]) j++;
            ans+=a[y].size()-j;
        }
    }
    return ans;
}
int calcB(int x,int y,int op){
    int ans=0;
    if(op){
        for(int i=0;i<a[x].size();i++){
            ans+=upper_bound(a[y].begin(),a[y].end(),a[x][i])-a[y].begin();
        }
    }else{
        for(int i=0;i<a[x].size();i++){
            ans+=a[y].end()-lower_bound(a[y].begin(),a[y].end(),a[x][i]);
        }
    }
    return ans;
}

signed main(){
    int m,q;
    cin>>m;
    for(int i=1,n;i<=m;i++){
        cin>>n;
        for(int j=1,x;j<=n;j++) cin>>x,a[i].push_back(x);
        sort(a[i].begin(),a[i].end());
    }
    cin>>q;
    for(int i=1;i<=q;i++) cin>>c[i].first>>c[i].second;

    map<pair<int,int>,int> mp[2];
    set<pair<pair<int,int>,int>> s;
    for(int i=1;i<=q;i++){
        if(a[c[i].first].size()>a[c[i].second].size()){
            swap(c[i].first,c[i].second);
            s.insert({c[i],1});
            f[i]=1;
        }else s.insert({c[i],0});
    }
    for(pair<pair<int,int>,int> i:s){
        pair<int,int> p=i.first;int op=i.second;
        int x=a[p.first].size(),y=a[p.second].size();
        if(x*log2(y)<x+y) mp[op][p]=calcB(p.first,p.second,op);
        else mp[op][p]=calcA(p.first,p.second,op);
    }

    for(int i=1;i<=q;i++) cout<<mp[f[i]][c[i]]<<'\n';

    return 0;
}
