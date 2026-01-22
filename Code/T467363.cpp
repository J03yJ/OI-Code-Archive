#include<bits/stdc++.h>

using namespace std;

const int N=1e6+9;

int ans[N],cnt[N];
void insert(int x){
    int k=cnt[x];
    for(int i=1;i*i<=k;i++){
        if(k%i) continue ;
        ans[i]++;
        if(i*i!=k) ans[k/i]++;
    }
    cnt[x]++;
}
void erase(int x){
    cnt[x]--;
    int k=cnt[x];
    for(int i=1;i*i<=k;i++){
        if(k%i) continue ;
        ans[i]--;
        if(i*i!=k) ans[k/i]--;
    }
}

int main(){
    int n,q;
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        insert(x);
    }
    while(q--){
        int op,k;
        cin>>op>>k;
        if(op==1) insert(k);
        else if(op==2) erase(k);
        else cout<<ans[k]<<endl;
    }
    return 0;
}