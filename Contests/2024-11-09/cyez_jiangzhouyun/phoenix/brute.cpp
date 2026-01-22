#include<bits/stdc++.h>

using namespace std;

const int N=3e5+9;
const int K=6e2+9;

int a[N],blk[N],n,m,c,k,q,B;
vector<array<int,3>> op[N];
long long cnt[N],s1[N],s2[N];
short buc[N<<1];

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'

    cin>>n>>m>>c>>k>>q;
    B=sqrt(m)*2.2;
    for(int i=1;i<=n;i++) blk[i]=(i-1)/B+1;

    for(int i=1,l,r,u,d;i<=c;i++){
        cin>>u>>l>>d>>r;
        op[u].push_back({l,r,1});
        op[d+1].push_back({l,r,-1});
    }
    for(int l=1,r,dlt,res,ql,qr,tmp;l<=m;l=r+1){
        r=min(l+B-1,m),dlt=0,res=0;
        buc[0]=r-l+1;
        for(int i=1;i<=n;i++){
            for(auto &t:op[i]){
                ql=t[0],qr=t[1],tmp=t[2];
                if(ql<=l&&r<=qr){
                    if(tmp==1){
                        dlt++;
                        if(dlt<=k) res+=buc[k-dlt];
                    }else{
                        if(dlt<=k) res-=buc[k-dlt];
                        dlt--;
                    }
                }else{
                    if(ql<l) ql=l;
                    if(qr>r) qr=r;
                    if(ql>qr) continue ;
                    res=0;
                    for(int j=l;j<=r;j++){
                        --buc[a[j]];
                        a[j]+=dlt;
                        if(ql<=j&&j<=qr) a[j]+=tmp;
                        ++buc[a[j]];
                        if(a[j]>=k) ++res;
                    }
                    dlt=0;
                }
            }
            cnt[i]+=res;
        }
        for(int i=l;i<=r;i++) --buc[a[i]];
    }
    for(int i=1;i<=n;i++) cnt[i]=min(cnt[i],m-cnt[i]);
    sort(cnt+1,cnt+n+1);
    for(int i=1;i<=n;i++){
        s1[i]=s1[i-1]+cnt[i];
        s2[i]=s2[i-1]+cnt[i]*cnt[i];
    }
    while(q--){
        long long x,y,ans,tmp;
        cin>>x>>y,tmp=y>>1;
        int pos=lower_bound(cnt+1,cnt+n+1,tmp)-cnt;
        if(n-pos+1>x) ans=tmp*(y-tmp)*x;
        else ans=tmp*(y-tmp)*(n-pos+1)+(s1[pos-1]-s1[n-x])*y-(s2[pos-1]-s2[n-x]);
        cout<<ans<<endl;
    }

    return 0;
}