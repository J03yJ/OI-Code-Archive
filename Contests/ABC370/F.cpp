#include<bits/stdc++.h>

using namespace std;

const int inf=2e9+7;
const int N=1e6+9;
const int lgN=20;

int a[N],s[N],n,m,k;
int fa[N][lgN];
int KthA(int x,int k){
    for(int i=0;i<lgN;i++) if(k>>i&1) x=fa[x][i];
    return x;
}
bool Check(int val){
    for(int i=1;i<=m;i++){
        int l=0,r=i;
        while(l+1<r){
            int mid=l+r>>1;
            if(s[i]-s[mid]>=val) l=mid;
            else r=mid;
        }
        fa[i][0]=l;
    }
    for(int j=1;j<lgN;j++){
        for(int i=1;i<=m;i++) fa[i][j]=fa[fa[i][j-1]][j-1];
    }
    for(int i=n+1;i<=m;i++){
        if(KthA(i,k)>=i-n) return 1;
    }
    return 0;
}

int main(){
    cin>>n>>k;    
    m=n<<1;
    for(int i=1;i<=n;i++) cin>>a[i],a[i+n]=a[i];
    for(int i=1;i<=m;i++) s[i]=s[i-1]+a[i]; 

    int l=0,r=inf;
    while(l+1<r){
        int mid=l+r>>1;
        if(Check(mid)) l=mid;
        else r=mid;
    }
    cout<<l<<' ';

    int ans=l,cnt=0;
    Check(l);
    for(int i=n+1;i<=m;i++){
        if(KthA(i,k)<i-n) cnt++;
    }
    cout<<cnt<<endl;

    return 0;
}