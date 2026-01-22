#include<bits/stdc++.h>

using namespace std;

const int N=3e5+9;

int a[N],pre[N],buc[N],res[N],n,m;

int tr[N];
void Add(int x,int k){
    while(x<=n){
        tr[x]+=k;
        x+=x&-x;
    }
}
int Ask(int x){
    int sum=0;
    while(x){
        sum+=tr[x];
        x&=x-1;
    }
    return sum;
}
int Ask(int l,int r){
    if(l>r) return 0;
    return Ask(r)-Ask(l-1);
}

vector<pair<int,int>> q[N];

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];

    for(int i=1;i<=n;i++){
        pre[i]=buc[a[i]];
        buc[a[i]]=i;
    }
    for(int i=1;i<=n;i++){
        if(pre[i]) q[i-1].push_back({pre[i]+1,i});
        else res[i]=m-1;
    }
    for(int i=1;i<=n;i++){
        if(pre[i]) Add(pre[i],-1);
        Add(i,1);
        for(auto p:q[i]) res[p.second]=Ask(p.first,i);
    }

    long long ans=0;
    for(int i=1;i<=n;i++) ans+=res[i];
    cout<<ans<<endl;

    return 0;
}