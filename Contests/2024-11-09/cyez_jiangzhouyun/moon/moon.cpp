#include<bits/stdc++.h>

using namespace std;

ifstream fin("moon.in");
ofstream fout("moon.out");
#define cin fin
#define cout fout

#define int long long
#define ssiz(x) x.size()
const int N=5e6+9;
const int inf=1e18;

int a[N],f[N],n,m,t;

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'

    cin>>n>>m>>t;
    for(int i=1;i<=n;i++) cin>>a[i];

    queue<int> q;
    int mn=inf;
    q.push(0);
    for(int i=1;i<=n;i++){
        while(q.size()&&(a[i]-a[q.front()+1])*2>t){
            mn=min(mn,f[q.front()]-2*a[q.front()+1]);
            q.pop();
        }
        f[i]=ssiz(q)?f[q.front()]+t:inf;
        f[i]=min(f[i],mn+2*a[i]);
        q.push(i);
    }

    cout<<f[n]+m<<endl;

    return 0;
}