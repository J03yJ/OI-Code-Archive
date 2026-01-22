#include<bits/stdc++.h>

using namespace std;

ifstream fin("cof.in");
ofstream fout("cof.out");
#define cin fin
#define cout fout

#define int long long
const int N=1e6+9;
const int inf=2e9;

int a[N],n,m,k,cnt,ans;
vector<int> tic[N];

bool check(int val){
    cnt=ans=0;
    priority_queue<pair<int,int>> q;
    for(int i=1;i<=n;i++){
        q.push({-(a[i]-val),0});
        for(int t:tic[i]){
            if(!q.size()) break ;
            if(-q.top().first-t<0){
                if(!q.top().second) cnt++;
                ans+=-q.top().first-t;
                q.pop();
                q.push({-t,1});
            }
        }
    }
    return cnt<=k;
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i],tic[i].push_back(0);
    for(int i=1,r,w;i<=n;i++) cin>>r>>w,tic[r].push_back(w);
    cin>>k;

    int l=-inf,r=inf;
    while(l+1<r){
        int mid=l+r>>1;
        if(check(mid)) l=mid;
        else r=mid;
    }
    check(l);
    cout<<ans+k*l<<endl;

    return 0;
}