#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;
int a[N],b[N],val[N],f[N],g[N],cnt;
int tr[N];
void add(int x,int k){
    if(!x) return ;
    while(x<=cnt){
        tr[x]=max(tr[x],k);
        x+=x&-x;
    }
}
int ask(int x){
    if(x<=0) return 0;
    int ans=0;
    while(x){
        ans=max(ans,tr[x]);
        x&=x-1;
    }
    return ans;
}

int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i],val[i]=a[i];
    sort(val+1,val+n+1);
    cnt=unique(val+1,val+n+1)-val-1;
    for(int i=1;i<=n;i++) a[i]=lower_bound(val+1,val+cnt+1,a[i])-val,b[i]=cnt-a[i]+1;

    int err=1;
    for(int i=2;i<=n;i++) if(val[a[i]]!=val[a[i-1]]+1) err=0;
    if(err){
        cout<<n<<endl;
        return 0;
    }

    int ans=0;
    for(int i=1;i<=n;i++){
        f[i]=ask(a[i]-1)+1;
        add(a[i],f[i]);
        ans=max(ans,f[i]+(i!=n&&val[a[i]]<(1e9)));
        // cout<<f[i]<<' '<<(i!=n&&val[a[i]]<(1e9))<<endl;
    }
    memset(tr,0,sizeof(tr));
    for(int i=n;i;i--){
        g[i]=ask(b[i]-1)+1;
        add(b[i],g[i]);
        ans=max(ans,g[i]+(i!=1&&val[a[i]]>1));
        // cout<<g[i]<<' '<<(i!=1&&val[a[i]]>1)<<endl;
    }
    memset(tr,0,sizeof(tr));
    for(int i=2;i<=n;i++){
        int k=upper_bound(val+1,val+cnt+1,val[a[i]]-2)-val-1;
        // cout<<val[k]<<endl;
        ans=max(ans,ask(k)+1+g[i]);
        add(a[i-1],f[i-1]);
    }
    cout<<ans<<endl;
}