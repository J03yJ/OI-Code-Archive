#include<bits/stdc++.h>

using namespace std;

const int N=1e6+9;

int pre[N<<1],suc[N<<1],n;

int main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        string s;
        cin>>s;
        s+=s;
        for(int i=0,cur=-1;i<(n<<1);i++){
            pre[i]=cur;
            if(s[i]=='R') cur=i;
        }
        for(int i=n*2-1,cur=-1;~i;i--){
            suc[i]=cur;
            if(s[i]=='B') cur=i;
        }
        for(int i=0;i<(n<<1);i++) cout<<pre[i]<<' ';cout<<endl;
        for(int i=0;i<(n<<1);i++) cout<<suc[i]<<' ';cout<<endl;
        int flag=0;
        for(int i=0;i<(n<<1);i++){
            int x=s[i]=='R'?i:pre[i];
            int y=s[i]=='B'?i:suc[i];
            cout<<i<<' '<<x<<' '<<y<<" : ";
            if(~x) x=pre[x];
            if(~y) y=suc[y];
            cout<<x<<' '<<y<<endl;
            if(x==-1||y==-1) continue ;
            if(y-x+1<=n){
                flag=1;
                // break ;
            }
        }
        if(flag) cout<<"NO"<<endl;
        else cout<<"YES"<<endl;
    }

    return 0;
}