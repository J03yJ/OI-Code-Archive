#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e2+9;

int f[N],a[N],b[N],op[N],id[N],n;
inline bool Check(int l,int r){
    int len=r-l+1,mid=l+r>>1,hf=len>>1;
    if(len&1) return 0;
    for(int i=l;i<=mid;i++){
        if(!id[i]) continue ;
        if(op[i]==0){
            if(b[id[i]]!=-1&&b[id[i]]!=i+hf) return 0;
            else if(b[id[i]]==-1&&id[i+hf]) return 0;
        }else return 0;
    }
    for(int i=mid+1;i<=r;i++){
        if(!id[i]) continue ;
        if(op[i]==1){
            if(a[id[i]]!=-1&&a[id[i]]!=i-hf) return 0;
            else if(a[id[i]]==-1&&id[i-hf]) return 0;
        }else return 0;
    }
    return 1;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i]>>b[i];

    for(int i=1;i<=n;i++){
        if(a[i]!=-1){
            if(id[a[i]]){
                cout<<"No"<<endl;
                return 0;
            }
            op[a[i]]=0,id[a[i]]=i;
        }
        if(b[i]!=-1){
            if(id[b[i]]){
                cout<<"No"<<endl;
                return 0;
            }
            op[b[i]]=1,id[b[i]]=i;
        }
    }
    f[0]=1;
    for(int i=1;i<=(n<<1);i++){
        for(int j=1;j<=i;j++) f[i]|=f[j-1]&Check(j,i);
    }

    if(f[n<<1]) cout<<"Yes"<<endl;
    else cout<<"No"<<endl;

    return 0;
}