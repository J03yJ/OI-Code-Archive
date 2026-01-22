#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=5e3+9;
const int mod=1e9+7;
inline void AddAs(int &x,int y){if((x+=y)>=mod) x-=mod;}

int n,m;
string s;

namespace TaskA{
    inline bool Check(){
        for(int i=1;i<m;i++) if(s[i]=='1') return 0;
        return s[m]=='1';
    }
    int f[N];
    inline void Solve(){
        f[0]=1;
        for(int i=1;i<m;i++){
            for(int j=i;j<=n;j++) AddAs(f[j],f[j-i]);
        }
        int sum=0;
        for(int i=0;i<=n;i++) AddAs(sum,f[i]);
        cout<<sum<<endl;
    }
}
namespace Brute{
    int ans=0;
    mt19937 rng(4649);
    map<string,int> prio;
    map<int,int> vis;
    inline void DFS(string str,int k,int c,int r){
        if(!prio[str]) prio[str]=rng();
        if(c>k) return ;
        for(int i=1;i<m;i++){
            if(str[i]=='0'&&str[i+1]=='1'){
                swap(str[i],str[i+1]);
                DFS(str,k,c+1,r);
                swap(str[i],str[i+1]);
            }
        }
        if(c){
            while((k-=c)>=0){
                r+=prio[str];
                ans+=!vis[r];
                vis[r]=1;
                for(int i=1;i<m;i++){
                    if(str[i]=='0'&&str[i+1]=='1'){
                        swap(str[i],str[i+1]);
                        DFS(str,k,c+1,r);
                        swap(str[i],str[i+1]);
                    }
                }
            }
        }
    }
    inline void Solve(){
        ans=1;
        prio.clear();
        vis.clear();
        DFS(s,n,0,0);
        cout<<ans<<endl;
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>s>>n;
    m=s.size();
    s=" "+s;

    if(TaskA::Check()) TaskA::Solve();
    else Brute::Solve();

    return 0;
}