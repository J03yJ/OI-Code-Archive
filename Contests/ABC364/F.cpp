#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=1e6+9;

int fa[N];
int find(int x){
    if(fa[x]==x) return x;
    else return fa[x]=find(fa[x]);
}
void merge(int x,int y){
    fa[find(y)]=find(x);
}
tuple<int,int,int> e[N];

signed main(){
    int n,q;
    cin>>n>>q;
    for(int i=1;i<=n+q;i++) fa[i]=i;
    for(int i=1;i<=q;i++) cin>>get<2>(e[i])>>get<1>(e[i])>>get<0>(e[i]);

    sort(e+1,e+q+1);
    int sum=0;
    for(int i=1;i<=q;i++){
        int l=get<2>(e[i]),r=get<1>(e[i]),k=get<0>(e[i]);
        for(int j=find(l);j+1<=r;j=find(j+1)){
            sum+=k;
            merge(find(j+1),j);
        }
        sum+=k; 
    }

    if(find(1)!=find(n)) cout<<-1<<endl;
    else cout<<sum<<endl;

    return 0;
}