#include<bits/stdc++.h>

using namespace std;

int n,m,q;
vector<vector<int>> tr;
void Add(int x,int y,int k){
    // cout<<x<<' '<<y<<' '<<k<<endl;
    for(int i=x;i<=n;i+=i&-i){
        for(int j=y;j<=m;j+=j&-j){
            tr[i][j]+=k;
        }
    }
}
int Ask(int x,int y){
    int sum=0;
    for(int i=x;i;i&=i-1){
        for(int j=y;j;j&=j-1){
            sum+=tr[i][j];
        }
    }
    return sum;
}
int Ask(int l,int r,int L,int R){
    return Ask(r,R)-Ask(l-1,R)-Ask(r,L-1)+Ask(l-1,L-1);
}

int main(){
    cin>>n>>m>>q;
    
    tr=vector<vector<int>>(n+1,vector<int>(m+1,0));
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) Add(i,j,1);

    while(q--){
        int x,y;
        cin>>x>>y;
        if(Ask(x,x,y,y)){
            Add(x,y,-1);
            continue ;
        }
        if(Ask(x,x,y+1,m)){
            int l=y,r=m+1;
            while(l+1<r){
                int mid=l+r>>1;
                if(Ask(x,x,y,mid)) r=mid;
                else l=mid;
            }
            if(r<=m) Add(x,r,-1);
        }
        if(Ask(x,x,1,y-1)){
            int l=0,r=y;
            while(l+1<r){
                int mid=l+r>>1;
                if(Ask(x,x,mid,y)) l=mid;
                else r=mid;
            }
            if(l) Add(x,l,-1);
        }
        if(Ask(x+1,n,y,y)){
            int l=x,r=n+1;
            while(l+1<r){
                int mid=l+r>>1;
                // cout<<mid<<'/'<<x<<'/'<<y<<' '<<Ask(x,mid,y,y)<<endl;
                // cout<<l<<":"<<r<<":"<<mid<<endl;
                if(Ask(x,mid,y,y)) r=mid;
                else l=mid;
            }
            // cout<<l<<';'<<r<<endl;
            if(r<=n) Add(r,y,-1);
        }
        if(Ask(1,x-1,y,y)){
            int l=0,r=x;
            while(l+1<r){
                int mid=l+r>>1;
                if(Ask(mid,x,y,y)) l=mid;
                else r=mid;
            }
            if(l) Add(l,y,-1);
        }
    }
    cout<<Ask(n,m)<<endl;
}