#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;
int a[N],w[N],mx[N];

int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>w[i],mx[a[i]]=max(mx[a[i]],w[i]);
    int ans=0;
    for(int i=1;i<=n;i++) ans+=w[i]-mx[i];
    cout<<ans<<endl;
}