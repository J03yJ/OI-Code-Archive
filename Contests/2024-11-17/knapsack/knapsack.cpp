#include<bits/stdc++.h>

using namespace std;

ifstream fin("knapsack.in");
ofstream fout("knapsack.out");
#define cin fin
#define cout fout

#define int long long
#define ssiz(x) (signed)x.size()
const int N=5e3+9;
const int W=1e4+9;

int f[W],v[N],w[N],p[N],res[N],n,V,k;

signed main(){
    cin>>n>>V>>k;
    for(int i=1;i<=n;i++) cin>>w[i]>>v[i],p[i]=i;

    sort(p+1,p+n+1,[](int x,int y){return w[x]<w[y];});
    priority_queue<int> q;
    for(int i=n,sum=0;i>=1;i--){
        q.push(-v[p[i]]),sum+=v[p[i]];
        if(ssiz(q)>k) sum+=q.top(),q.pop();
        res[i]=sum;
    }
    memset(f,-1,sizeof f);
    f[0]=0;
    int ans=0;
    for(int i=1;i<=n;i++){
        for(int j=V;j>=w[p[i]];j--){
            if(f[j-w[p[i]]]==-1) continue ;
            f[j]=max(f[j],f[j-w[p[i]]]+v[p[i]]);
        }
        for(int j=0;j<=V;j++) if(f[j]!=-1) ans=max(ans,f[j]+res[i+1]);
    }

    cout<<ans<<endl;

    return 0;
}