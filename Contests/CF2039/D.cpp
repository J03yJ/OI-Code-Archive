#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;

int a[N],b[N],n,m;
vector<int> ng[N];

int main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n>>m;
        for(int i=1;i<=m;i++) cin>>b[i];
        sort(b+1,b+m+1,[](int x,int y){return x>y;});

        int err=0;
        for(int i=1;i<=n;i++){
            for(int j=1,k=0;j<=m;j++){
                while(k<ng[i].size()&&ng[i][k]>b[j]) k++;
                if(k==ng[i].size()||ng[i][k]!=b[j]){
                    a[i]=b[j];
                    break ;
                }   
            }
            if(!a[i]){
                err=-1;
                break ;
            }
            for(int j=i+i;j<=n;j+=i){
                ng[j].push_back(a[i]);
            }
        }
        if(~err){
            for(int i=1;i<=n;i++) cout<<a[i]<<' ';cout<<endl;
        }else cout<<err<<endl;

        for(int i=1;i<=n;i++) ng[i].clear(),a[i]=0;
    }

    return 0;
}