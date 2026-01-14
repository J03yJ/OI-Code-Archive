#include<bits/stdc++.h>

using namespace std;

int main(){
    int T,n;
    cin>>T;
    while(T--){
        cin>>n;
        string s,t;
        cin>>s>>t;
        int s0=0,s1=0,flag=0;
        for(int i=0;i<n;i++){
            if(s[i]=='0') s0++;
            else s1++;
        }
        for(int i=0;i<n-1;i++){
            if(!s0||!s1) flag=1;
            if(t[i]=='0') s1--;
            else s0--;
        }
        if(flag) cout<<"NO"<<endl;
        else cout<<"YES"<<endl;
    }

    return 0;
}