#include<bits/stdc++.h>

using namespace std;

ifstream fin("seg.in");
ofstream fout("seg.out");
#define cin fin
#define cout fout

#define ssiz(x) (signed)x.size()
#define int long long

void Plus(vector<int> &a,vector<int> &b){
    while(ssiz(a)<ssiz(b)) a.push_back(0);
    for(int i=0;i<ssiz(b);i++) a[i]+=b[i];
}
struct Node{
    vector<int> f,g,ans;
    Node(){}
    Node(vector<int> F,vector<int> G,vector<int> A){f=F,g=G,ans=A;}
    Node operator*(Node x){
        Node res(f,x.g,ans);
        Plus(res.ans,x.ans);
        while(ssiz(res.f)<ssiz(x.f)+1) res.f.push_back(0);
        for(int i=0;i<ssiz(x.f);i++) res.f[i+1]+=x.f[i];
        while(ssiz(res.g)<ssiz(g)+1) res.g.push_back(0);
        for(int i=0;i<ssiz(g);i++) res.g[i+1]+=g[i];
        vector<int> tmp(ssiz(f)+ssiz(g),0);
        for(int i=0;i<ssiz(x.f);i++){
            for(int j=0;j<ssiz(g);j++){
                tmp[i+j]+=x.f[i]*g[j];
            }
        }
        Plus(res.ans,tmp);
        res.f[1]++,res.g[1]++,res.ans[1]++;
        res.ans[2]--,res.f[2]--,res.g[2]--;
        while(ssiz(res.f)&&!res.f.back()) res.f.pop_back();
        while(ssiz(res.g)&&!res.g.back()) res.g.pop_back();
        while(ssiz(res.ans)&&!res.ans.back()) res.ans.pop_back();
        return res;
    }
};
Node Leaf(){return Node({0,1},{0,1},{0,1});}
map<int,Node> mp;
Node Solve(int x){
    if(x==1) return Leaf();
    if(ssiz(mp[x].ans)) return mp[x]; 
    int mid=x>>1;
    Node lc=Solve(mid),rc=Solve(x-mid);
    return mp[x]=lc*rc;
}

signed main(){
    int c,T;
    cin>>c>>T;
    while(T--){
        int n,k;
        cin>>n>>k;
        Node a=Solve(n);
        if(k>=ssiz(a.ans)||k<=0) cout<<0<<endl;
        else cout<<a.ans[k]<<endl;
    }

    return 0;
}