#include<bits/stdc++.h>

using namespace std;

using ll=long long;

const int N=2e5+9;
const int lgN=2e1;

char s[N<<1],a[N];
int to[N][lgN],ot[N][lgN],pre[N],n,m;
ll sum[N][lgN],mus[N][lgN];

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n>>m;
    for(int i=1;i<=(n<<1);i++) cin>>s[i];
    for(int i=1;i<=n;i++) cin>>a[i];
    
    for(int i=1;i<=n;i++) pre[i]=pre[i-1]+a[i]-'0';
    for(int i=1,j=0,k=0;i<=(n<<1);i++){
        if(s[i]=='R') to[++k][0]=j;
        else j++;
    }
    for(int i=(n<<1),j=n+1,k=n+1;i>=1;i--){
        if(s[i]=='L') ot[--k][0]=j;
        else j--;
    }
    for(int i=1;i<=n;i++){
        sum[i][0]=pre[to[i][0]];
        mus[i][0]=pre[ot[i][0]-1];
    }

    for(int k=1;k<lgN;k++){
        for(int i=1;i<=n;i++){
            to[i][k]=to[to[i][k-1]][k-1];
            sum[i][k]=sum[i][k-1]+sum[to[i][k-1]][k-1];
            ot[i][k]=ot[ot[i][k-1]][k-1];
            mus[i][k]=mus[i][k-1]+mus[ot[i][k-1]][k-1];
        }
    }

    while(m--){
        int l,r;
        cin>>l>>r;
        
        ll ans=0;
        int lpos=l,rpos=r,cnt=0;
        for(int k=lgN-1;~k;k--){
            if(to[lpos][k]<r){
                ans+=sum[lpos][k];
                lpos=to[lpos][k];
                cnt+=1<<k;
            }
        }
        ans+=sum[lpos][0],lpos=to[lpos][0],cnt++;
        for(int k=lgN-1;~k;k--){
            if(ot[rpos][k]>l){
                ans-=mus[rpos][k];
                rpos=ot[rpos][k];
            }
        }
        ans-=mus[rpos][0],rpos=ot[rpos][0];
        
        ans+=pre[rpos-1];
        ans-=pre[lpos];
        ans+=a[l]-'0';
        ans+=a[r]-'0';

        cout<<cnt<<' '<<ans<<endl;
    }

    return 0;
}