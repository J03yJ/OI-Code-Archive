#include<bits/stdc++.h>

using namespace std;

const int N=2e3+9;

int r[N],a[N],n,k;
void DFS(int x){
    if(x>n){
        int sum=0;
        for(int i=1;i<=n;i++) sum+=a[i];
        if(sum%k==0){
            for(int i=1;i<=n;i++) cout<<a[i]<<' ';
            cout<<endl;
        }
        return ;
    }
    for(int i=1;i<=r[x];i++){
        a[x]=i;
        DFS(x+1);
    }
}

int main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>r[i];
    DFS(1);
    return 0;
}