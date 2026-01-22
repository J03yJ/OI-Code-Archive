#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=2e5+9;

int a[N],d[N],n;

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];

    vector<int> p,q;
    for(int i=1;i<n;i++){
        if(i&1) p.push_back(a[i+1]-a[i]);
        else q.push_back(a[i+1]-a[i]);
    }
    sort(p.begin(),p.end(),greater<int>());
    sort(q.begin(),q.end(),greater<int>());
    
    int cur=a[1],sum=a[1];
    for(int i=1;i<n;i++){
        if(i&1) cur+=p.back(),p.pop_back();
        else cur+=q.back(),q.pop_back();
        sum+=cur;
    }

    cout<<sum<<endl;

    return 0;
}