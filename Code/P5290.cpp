#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;

int fi[N],ne[N<<1],to[N<<1],adj;
void AddEdge(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

int a[N],n;
void Merge(multiset<int> &s,multiset<int> &t){
    if(s.size()<t.size()) swap(s,t);
    vector<int> p,q(t.begin(),t.end());
    for(auto it=s.begin();;it++){
        if(p.size()==t.size()){
            s.erase(s.begin(),it);
            break ;
        }
        p.push_back(*it);
    }
    for(int i=0;i<t.size();i++) p[i]=min(p[i],q[i]);
    s.insert(p.begin(),p.end());
}
void DFS(int x,multiset<int> &res){
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        multiset<int> tmp;
        DFS(y,tmp);
        Merge(res,tmp);
    }
    res.insert(-a[x]);
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=2,fa;i<=n;i++) cin>>fa,AddEdge(fa,i);

    multiset<int> res;
    DFS(1,res);
    cout<<-accumulate(res.begin(),res.end(),0ll)<<endl;

    return 0;
}