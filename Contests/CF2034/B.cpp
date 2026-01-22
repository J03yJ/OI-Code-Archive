#include<bits/stdc++.h>

using namespace std;

int main(){
    int T;
    cin>>T;
    while(T--){
        int n,m,k;
        cin>>n>>m>>k;
        string s;
        cin>>s;
        int ans=0;
        for(int i=0,cnt=0;i<n;i++){
            if(s[i]=='1') cnt=0;
            else{
                cnt++;
                if(cnt==m){
                    ans++;
                    for(int j=0;j<k&&i+j<n;j++) s[i+j]='1';
                    cnt=0;
                }
            }
        }
        cout<<ans<<endl;
    }

    return 0;
}