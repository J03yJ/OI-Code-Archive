#include<bits/stdc++.h>

using namespace std;

const int N=1e6+9;

int a[N];

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'

    int T;
    cin>>T;
    while(T--){
        int n,x;
        cin>>n>>x;
        for(int i=1;i<=n;i++) cin>>a[i];

        int tmp=1e9+7;
        vector<int> v;
        for(int i=1;i<=n;i++){
            if(abs(i-x)<=1) v.push_back(a[i]);
            else tmp=min(tmp,a[i]);
        }
        v.push_back(tmp);
        sort(v.begin(),v.end());
        v.pop_back();
        int ans=v.back();

        sort(a+1,a+n+1);
        ans=max(ans,a[min(n,3)]);

        cout<<ans<<endl;
    }

    return 0;
}