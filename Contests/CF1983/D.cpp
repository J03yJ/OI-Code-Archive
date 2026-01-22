#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;

int a[N],b[N],val[N],tmp1[N],tmp2[N];

bool check(int *a,int *b,int n){
    for(int i=1;i<=n;i++){
        tmp1[i]=a[i];
        tmp2[i]=b[i];
    }
    sort(tmp1+1,tmp1+n+1);
    sort(tmp2+1,tmp2+n+1);
    for(int i=1;i<=n;i++) if(tmp1[i]!=tmp2[i]) return 0;
    return 1;
}
int F(int *a,int n){
    for(int i=1;i<=n;i++) val[i]=a[i];
    sort(val+1,val+n+1);
    int cnt=unique(val+1,val+n+1)-val-1;
    for(int i=1;i<=n;i++) a[i]=lower_bound(val+1,val+cnt+1,a[i])-val;
    return cnt;
}

long long tr[N];
void add(int x,int k,int n){
    while(x<=n){
        tr[x]+=k;
        x+=x&-x;
    }
}
int ask(int x){
    int ans=0;
    while(x){
        ans+=tr[x];
        x&=x-1;
    }
    return ans;
}
int ask(int l,int r){
    return ask(r)-ask(l-1);
}
void clear(int n){
    for(int i=1;i<=n;i++) tr[i]=0;
}
long long calc(int *a,int n,int cnt){
    long long ans=0;
    for(int i=1;i<=n;i++){
        add(a[i],1,cnt);
        ans+=ask(a[i]+1,cnt);
    }
    clear(cnt);
    return ans;
}

int main(){
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];
        for(int i=1;i<=n;i++) cin>>b[i];
        
        if(!check(a,b,n)){
            cout<<"No"<<endl;
            continue ;
        }
        int cnt=F(a,n);F(b,n);
        int ans1=calc(a,n,cnt),ans2=calc(b,n,cnt);
        // cout<<ans1<<' '<<ans2<<endl;
        if(ans1%2==ans2%2) cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
    }
}