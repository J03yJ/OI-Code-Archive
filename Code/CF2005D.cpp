#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e5+9;
const int lgN=20;

int a[N],b[N],n;
struct STbl{
    int st[N][lgN],lg[N];
    void Init(int *a){
        for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
        for(int i=1;i<=n;i++) st[i][0]=a[i];
        for(int k=1;k<=lg[n];k++){
            for(int i=1;i<=n-(1<<k)+1;i++){
                st[i][k]=__gcd(st[i][k-1],st[i+(1<<k-1)][k-1]);
            }
        }
    }
    int Query(int l,int r){
        if(l>r) return 0;
        int k=lg[r-l+1];
        return __gcd(st[l][k],st[r-(1<<k)+1][k]);
    }
}ast,bst;
int Calc(int l,int r){
    return __gcd(__gcd(ast.Query(1,l-1),ast.Query(r+1,n)),bst.Query(l,r))+
           __gcd(__gcd(bst.Query(1,l-1),bst.Query(r+1,n)),ast.Query(l,r));
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];
        for(int i=1;i<=n;i++) cin>>b[i];

        ast.Init(a);
        bst.Init(b);

        vector<int> pos;
        for(int i=1;i<=n;i++){
            if(ast.Query(1,i)!=ast.Query(1,i-1)) pos.push_back(i);
            else if(ast.Query(i,n)!=ast.Query(i-1,n)) pos.push_back(i);
            else if(bst.Query(1,i)!=bst.Query(1,i-1)) pos.push_back(i);
            else if(bst.Query(i,n)!=bst.Query(i-1,n)) pos.push_back(i);
        }
        pos.push_back(n+1);

        int ans=0,cnt=0;
        for(int i=0;i<pos.size()-1;i++){
            for(int j=i+1;j<pos.size()-1;j++){
                int res=Calc(pos[i+1]-1,pos[j]); 
            }
        }
    }
    return 0;
}