#include<bits/stdc++.h>

using namespace std;

const int N=1e6+9;

int nxt[N],buc[N],to[N],a[N],n;

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        char c;
        cin>>c;
        if(c=='p') a[i]=1;
        else a[i]=-1;
    }

    int mn=n+1;
    memset(buc,-1,sizeof buc);
    for(int i=1;i<=n;i++){
        a[i]+=a[i-1];
        mn=min(mn,a[i]);
    }
    for(int i=n;i>=0;i--){
        int tmp=a[i]-mn;
        nxt[i]=buc[tmp];
        buc[tmp]=i;
        to[i]=i;
    }

    int ans=0;
    for(int i=n,pre=n;i>=1;i--){
        if(a[i]==a[i-1]-1) pre=i-1;
        else{
            if(nxt[i-1]>=0&&a[to[nxt[i-1]]]>=a[pre]) pre=to[nxt[i-1]];
            ans=max(ans,pre-i+1);
            to[i-1]=pre;
        }
    }

    cout<<ans<<endl;

    return 0;
}