#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;

int a[N],b[N],p[N],n,m,q;

int main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n>>m>>q;
        for(int i=1;i<=n;i++) cin>>a[i],p[a[i]]=i;
        for(int i=1;i<=m;i++) cin>>b[i];
        int cur=1;
        for(int i=1;i<=m;i++){
            if(p[b[i]]==cur) cur++;
            else if(p[b[i]]>cur){
                cout<<"TIDAK"<<endl;
                cur=-1;
                break ;
            }
        }
        if(~cur) cout<<"YA"<<endl;
    }
}