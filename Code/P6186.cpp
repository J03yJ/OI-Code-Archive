#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=2e5+9;

int a[N],c[N],n,m;
struct BIT{
    int tr[N];
    void Add(int x,int k){
        while(x<=n){
            tr[x]+=k;
            x+=x&-x;
        }
    }
    int Ask(int x){
        int res=0;
        while(x){
            res+=tr[x];
            x&=x-1;
        }
        return res;
    }
    int Ask(int l,int r){
        return Ask(r)-Ask(l-1);
    }
}va,vc,s;

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++){
        c[i]=va.Ask(a[i],n);
        va.Add(a[i],1);
        if(c[i]) vc.Add(c[i],1);
        if(c[i]) s.Add(c[i],c[i]);
    }
    while(m--){
        int op,x;
        cin>>op>>x;
        if(op==1){
            if(a[x]<a[x+1]){
                if(c[x]) vc.Add(c[x],-1),s.Add(c[x],-c[x]);
                c[x]++;
                if(c[x]) vc.Add(c[x],1),s.Add(c[x],c[x]);
            }else{
                if(c[x+1]) vc.Add(c[x+1],-1),s.Add(c[x+1],-c[x+1]);
                c[x+1]--;
                if(c[x+1]) vc.Add(c[x+1],1),s.Add(c[x+1],c[x+1]);
            }
            swap(a[x],a[x+1]);
            swap(c[x],c[x+1]);
        }else{
            if(x>=n) cout<<0<<endl;
            else cout<<s.Ask(x+1,n)-vc.Ask(x+1,n)*x<<endl;
        }
    }

    return 0;
}