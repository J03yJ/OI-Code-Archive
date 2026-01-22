#include<bits/stdc++.h>

using namespace std;

ifstream fin("good.in");
ofstream fout("good.out");
#define cin fin
#define cout fout

const int N=1e7+9;
const int mod=1e9+7;
inline void AddAs(int &x,int y){x+=y;if(x>=mod) x-=mod;}
inline void SubAs(int &x,int y){x-=y;if(x<0) x+=mod;}

int a[N],p[N],tot,ans,n;
long long per[N];
#define PII(x,y) ((long long)x)<<32|y

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=1,x,y,z,w;i<=n;i++){
        cin>>x>>y>>z>>w;
        a[++tot]=x,p[tot]=z,per[tot]=PII(a[tot],tot);
        a[++tot]=y,p[tot]=w,per[tot]=PII(a[tot],tot);
        SubAs(ans,1ll*max(a[tot],a[tot-1])*z%mod*w%mod);
    }
    sort(per+1,per+tot+1);

    for(int t=1,sum=1;t<=tot;t++){
        int i=per[t];
        AddAs(ans,1ll*a[i]*p[i]%mod*sum%mod);
        AddAs(sum,p[i]);
    }

    cout<<ans<<endl;

    return 0;
}