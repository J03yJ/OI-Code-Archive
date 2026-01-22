#include<bits/stdc++.h>

using namespace std;

ifstream fin("seq.in");
ofstream fout("seq.out");
#define cin fin
#define cout fout

#define int long long
const int N=1e6+9;

int a[N],d[N],pre[N],suc[N],val[N];

signed main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=m;i++) cin>>a[i];
    
    for(int i=1;i<=m;i++) d[1]++,d[a[i]+1]--;
    for(int i=1;i<=n+1;i++) d[i]+=d[i-1];
    for(int i=1;i<=n;i++) pre[i]=pre[i-1]+d[i];
    for(int i=n;i>=1;i--) suc[i]=suc[i+1]+d[i];
    vector<pair<int,int>> v;
    for(int i=1;i<=n;i++){
        val[i]=(suc[i]+n-i)/(n-i+1);
        if(v.empty()||v.back().first!=val[i]) v.push_back({val[i],i});
    }
    reverse(v.begin(),v.end());
    // for(pair<int,int> p:v) cout<<p.first<<' '<<p.second<<endl;

    for(int i=1;i<=m;i++){
        int pos=(--upper_bound(v.begin(),v.end(),make_pair(i,(int)1e9)))->second;
        int l=pos-1,r=n+1;
        while(l+1<r){
            int mid=l+r>>1;
            if(pre[mid]>=i*mid) l=mid;
            else r=mid;
        }
        cout<<l-pos+1<<' ';
    }
    cout<<endl;

    return 0;
}