#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;

char s[N],t[N];

signed main(){
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        for(int i=1;i<=n;i++) cin>>s[i];
        for(int i=1;i<=n;i++) cin>>t[i];
        bool flag=0,err=0;
        for(int i=1;i<=n;i++){
            if(s[i]=='0'&&t[i]=='1'&&!flag){
                err=1;
                break ;
            }
            if(s[i]=='1') flag=1;
        }
        if(err) cout<<"NO"<<endl;
        else cout<<"YES"<<endl;
    }
}