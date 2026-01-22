#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;
#define int long long
int a[N];

signed main(){
    int n;
    cin>>n;
    vector<int> v;
    v.push_back(0);
    int ans=0;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        while(v.size()>1&&a[v.back()]<=a[i]){
            int x=v.back();
            v.pop_back();
            ans-=(x-v.back())*a[x];
        }
        ans+=(i-v.back())*a[i];
        v.push_back(i);
        cout<<ans+1<<' ';
    }
    cout<<endl;
    return 0;
}