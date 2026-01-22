#include<bits/stdc++.h>

using namespace std;

int main(){
    int T;
    cin>>T;
    while(T--){
        int n,mx=0;
        cin>>n;
        map<int,int> mp;
        vector<int> a;
        for(int i=1,x;i<=n;i++){
            cin>>x;
            if(!mp[x]) a.push_back(x);
            mp[x]++;
        }
        sort(a.begin(),a.end());
        bool flag=0;
        for(int i=a.size()-1;~i;i--) if(mp[a[i]]%2) flag=1;
        if(flag) cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
}