#include<bits/stdc++.h>

using namespace std;

using ll=long long;

signed main(){
    int T;
    cin>>T;
    while(T--){
        int n,m;
        cin>>n>>m;
        string s;
        cin>>s;
        ll ans=1;
        int cntr=0,cntq=0,sr=0,sq=0;
        for(char c:s) if(c=='R') sr++;
        for(char c:s) if(c=='?') sq++;
        for(int i=0;i<n+m-2;i++){
            if(s[i]=='R') cntr++;
            else if(s[i]=='D') ;
            else cntq++;
            int mxr=min(m-1-(sr-cntr),cntr+cntq);
            int mnr=max(max(cntr,i-n+2),m-1-(sr-cntr)-(sq-cntq));
            ans+=mxr-mnr+1;
        }
        cout<<ans<<endl;
    }

    return 0;
}