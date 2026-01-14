#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;
#define int long long
#define bint __int128

int a[N];

signed main(){
    int n,ans=0;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i],ans+=a[i];
    priority_queue<tuple<int,int,int>> q;
    for(int i=1;i<=n;i++) q.push(make_tuple(-a[i]*3ll,a[i],2));
    for(int i=1;i<=n-2;i++){
        int val=-get<0>(q.top()),x=get<1>(q.top()),cnt=get<2>(q.top());
        q.pop();
        ans+=val;
        val=x*(cnt+cnt+1);
        q.push(make_tuple(-val,x,++cnt));
    }
    cout<<ans<<endl;
}