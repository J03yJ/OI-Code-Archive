#include<bits/stdc++.h>
using namespace std;

const int N=2e5+9;
const int V=2e5;
int ans[N];
const int inf=1e9;

int main(){
    int n,m;
    cin>>n>>m;
    
    vector<int> A;
    A.push_back(m-1);
    int k=m-3;
    while(k>0&&A.back()+k<=V){
        A.push_back(A.back()+k);
        k-=2;
    }

    for(int i=1;i<=V;i++) ans[i]=inf;
    for(int i=0;i<=V;i++){
        for(int j=0;j<A.size()&&A[j]+i<=V;j++){
            ans[A[j]+i]=min(ans[A[j]+i],ans[i]+1);
        }
    }

    while(n--){
        int x;
        cin>>x;
        if(ans[x]==inf) cout<<-1<<endl;
        else cout<<ans[x]<<endl;
    }
}