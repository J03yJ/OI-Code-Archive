#include<bits/stdc++.h>

using namespace std;

ifstream fin("phoenix.in");
ofstream fout("phoenix.out");
#define cin fin
#define cout fout

const int N=3e5+9;

int a[N],n,m,c,k,q;
vector<array<int,3>> op[N];
long long cnt[N],s1[N],s2[N];

struct Node{
    int l,r,t,f[11];
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define t(x) tr[x].t
#define f(x) tr[x].f

void PushUp(int x){
    for(int i=0;i<=k;i++) f(x)[i]=0;
    for(int i=0;i<=k;i++) f(x)[min(k,i+t(x))]+=f(x<<1)[i]+f(x<<1|1)[i];
    // cout<<"# "<<l(x)<<' '<<r(x)<<" : "<<t(x)<<endl;
    // for(int i=0;i<=k;i++) cout<<f(x<<1)[i]<<' ';cout<<endl;
    // for(int i=0;i<=k;i++) cout<<f(x<<1|1)[i]<<' ';cout<<endl;
    // for(int i=0;i<=k;i++) cout<<f(x)[i]<<' ';cout<<endl;
}
void Push(int x,int dlt){
    if(l(x)!=r(x)){
        t(x)+=dlt;
        PushUp(x);
    }else{
        f(x)[min(t(x),k)]--;
        t(x)+=dlt;
        f(x)[min(t(x),k)]++;
    }
    // cout<<l(x)<<' '<<r(x)<<" : ";for(int i=0;i<=k;i++) cout<<f(x)[i]<<' ';cout<<endl;
}

void Build(int x,int l,int r){
    l(x)=l,r(x)=r,t(x)=0;
    if(l(x)==r(x)){
        f(x)[0]=1;
        return ;
    }
    int mid=(l(x)+r(x))>>1;
    Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
    PushUp(x);
    // cout<<l(x)<<' '<<r(x)<<" : ";for(int i=0;i<=k;i++) cout<<f(x)[i]<<' ';cout<<endl;
}
void Modify(int x,int l,int r,int dlt){
    if(l<=l(x)&&r(x)<=r) return Push(x,dlt);
    int mid=(l(x)+r(x))>>1;
    if(l<=mid) Modify(x<<1,l,r,dlt);
    if(r>mid) Modify(x<<1|1,l,r,dlt);
    PushUp(x);
    // cout<<l(x)<<' '<<r(x)<<" : ";for(int i=0;i<=k;i++) cout<<f(x)[i]<<' ';cout<<endl;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'

    cin>>n>>m>>c>>k>>q;

    for(int i=1,l,r,u,d;i<=c;i++){
        cin>>u>>l>>d>>r;
        op[u].push_back({l,r,1});
        op[d+1].push_back({l,r,-1});
    }
    Build(1,1,m);
    for(int i=1;i<=n;i++){
        for(auto t:op[i]) Modify(1,t[0],t[1],t[2]);
        cnt[i]=f(1)[k];
        // cout<<" : ";
        // int sum=0;
        // for(int j=0;j<=k;j++) cout<<f(1)[j]<<' ',sum+=f(1)[j];cout<<sum<<endl;
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