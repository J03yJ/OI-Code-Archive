#include<bits/stdc++.h>

using namespace std;

#define int long long
#define Check(x) if(!v[x]) v.erase(v.begin()+x)
int ans;

signed main(){
    int T;
    cin>>T;
    while(T--){
        int n,k;
        cin>>n>>k;
        vector<int> v;
        for(int i=2;i*i<=n;i++){
            if(n%i) continue ;
            v.push_back(0);
            while(n%i==0) n/=i,v.back()++;
        }
        if(n!=1) v.push_back(1);
        ans=1;
        sort(v.begin(),v.end());
        reverse(v.begin(),v.end());
        
        for(int i=0;i<v.size();i++){
            v[i]--,ans++;
        }
        sort(v.begin(),v.end());
        v.erase(v.begin(),upper_bound(v.begin(),v.end(),0));
        reverse(v.begin(),v.end());

        for(int i=0;i<v.size();i++){
            for(int j=i;j<v.size();j++){
                if(v[i]&&v[j]){
                    v[i]--,v[j]--;
                    ans++;
                }
            }
        }
        sort(v.begin(),v.end());
        v.erase(v.begin(),upper_bound(v.begin(),v.end(),0));
        reverse(v.begin(),v.end());

        for(int i=0;i<v.size();i++){
            for(int j=i;j<v.size();j++){
                for(int k=j;k<v.size();k++){
                    if(v[i]&&v[j]&&v[k]){
                        v[i]--,v[j]--,v[k]--;
                        ans++;
                    }
                }
            }
        }
        sort(v.begin(),v.end());
        v.erase(v.begin(),upper_bound(v.begin(),v.end(),0));
        reverse(v.begin(),v.end());

        if(ans>=k) cout<<"TAK"<<endl;
        else cout<<"NIE"<<endl;
    }

    return 0;
}