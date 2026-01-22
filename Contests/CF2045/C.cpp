#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;

string s,t;
int a[26],b[26];

int main(){
    cin>>s>>t;

    int n=s.size(),m=t.size();
    s=" "+s,t=" "+t;

    for(int i=2;i<=n;i++) if(!a[s[i]-'a']) a[s[i]-'a']=i;
    for(int i=m-1;i;i--) if(!b[t[i]-'a']) b[t[i]-'a']=i;

    int ans=n+m+1;
    for(int i=0;i<26;i++){
        if(!a[i]||!b[i]) continue ;
        ans=min(ans,a[i]+m-b[i]);
    }
    if(ans>n+m) cout<<-1<<endl;
    else{
        for(int i=0;i<26;i++){
            if(!a[i]||!b[i]) continue ;
            if(ans==a[i]+m-b[i]){
                for(int j=1;j<=a[i];j++) cout<<s[j];
                for(int j=b[i]+1;j<=m;j++) cout<<t[j];
                cout<<endl;
                break ;
            }
        }
    }

    return 0;
}