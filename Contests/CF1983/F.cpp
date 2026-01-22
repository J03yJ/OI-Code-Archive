#include<bits/stdc++.h>

using namespace std;

#define int long long

const int N=2e5+9;

int a[N];

struct node{
    int dat,son[2];
    node(){}
    node(int s,int lc,int rc){
        dat=s;son[0]=lc;son[1]=rc;        
    }
};
vector<node> tr;
void insert(int x,int pos){
    int u=1;
    for(int i=29;~i;i--){
        tr[u].dat=max(tr[u].dat,pos);
        int f=x>>i&1;
        if(!tr[u].son[f]){
            tr[u].son[f]=tr.size();
            tr.push_back(node(0,0,0));
        }
        u=tr[u].son[f];
    }
    tr[u].dat=max(tr[u].dat,pos);
}
int query(int x,int k,int pos){
    int u=1,ans=0;
    for(int i=29;~i;i--){
        int f=x>>i&1,g=k>>i&1;
        if(!g){
            if(tr[u].son[f]) u=tr[u].son[f];
            else return ans;
        }else{
            ans=max(ans,tr[tr[u].son[f]].dat);
            if(tr[u].son[f^1]) u=tr[u].son[f^1];
            else return ans;
        }
    }
    ans=max(ans,tr[u].dat);
    return ans;
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        int n,k;
        cin>>n>>k;
        for(int i=1;i<=n;i++) cin>>a[i];

        int l=-1,r=(1ll<<30);
        while(l+1<r){
            int mid=l+r>>1;
            int sum=0;

            tr.push_back(node(0,0,0));
            tr.push_back(node(0,0,0));
            for(int i=1,mx=0;i<=n;i++){
                mx=max(mx,query(a[i],mid,i));
                sum+=mx;
                insert(a[i],i);
            }
            tr.clear();
            // for(int i=1;i<=n;i++) sum+=query(a[i],mid);
            // cout<<mid<<' '<<sum<<endl;
            // sum/=2;
            if(sum<k) l=mid;
            else r=mid;
        }

        cout<<r<<endl;
    }
}