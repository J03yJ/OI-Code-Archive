#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=2e5+9;
const int K=10;

int h[K][N],A[N],B[N],n,q;
int a[K][N],b[K][N];

signed main(){
    mt19937 myrand(11);

    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>A[i];
    for(int i=1;i<=n;i++) cin>>B[i];

    for(int k=0;k<K;k++){
        for(int i=1;i<=n;i++) h[k][i]=myrand();
    }
    for(int k=0;k<K;k++){
        for(int i=1;i<=n;i++) a[k][i]=a[k][i-1]+h[k][A[i]];
        for(int i=1;i<=n;i++) b[k][i]=b[k][i-1]+h[k][B[i]];
    }

    while(q--){
        int l,r,L,R;
        cin>>l>>r>>L>>R;
        bool flag=((r-l+1)==(R-L+1));
        for(int k=0;k<K;k++){
            if(a[k][r]-a[k][l-1]!=b[k][R]-b[k][L-1]) flag=0;
        }
        if(flag) cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
    }
    
    return 0;
}