#include<bits/stdc++.h>

using namespace std;

int main(){
    int n,t,p;
    cin>>n>>t>>p;
    vector<int> a(n,0);
    for(int i=0;i<n;i++) cin>>a[i],a[i]=max(t-a[i],0);
    sort(a.begin(),a.end());
    cout<<a[p-1]<<endl;
}