#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=5e3+9;

int ans[N][N];
inline ll F(int n){
    return (1ll*n*((n-1)/2)*(n/2)-1ll*n*(n-1)*(n-2)/6)>>1;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    int T;
    cin>>T;
    while(T--){
        int n;ll m;
        cin>>n>>m;
        // cout<<F(n)<<' '<<m<<endl;
        if(m>F(n)){
            cout<<"No"<<endl;
            continue ;
        }else cout<<"Yes"<<endl;
        
        int k=0;
        while(F(k)<m) k++;
        int stp=F(k)-m;
        vector<int> b(n);
        if(k&1) b[(k-1)/2]=k;
        else b[k/2]=b[(k-1)/2]=k/2;
        for(int i=k;i<n;i++) b[i]++;
        while(stp){
            for(int i=1;i<n-1;i++){
                if(b[i]>1){
                    int tmp=min(b[i]>>1,stp);
                    b[i-1]+=tmp;
                    b[i+1]+=tmp;
                    b[i]-=tmp<<1;
                    stp-=tmp;
                }
            }
        }
        vector<int> d;
        for(int i=0;i<n;i++) while(b[i]--) d.push_back(i);
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++) ans[i][j]=0;
        }
        vector<int> p(n);
        iota(p.begin(),p.end(),0);
        for(int i=0;i<n;i++){
            sort(p.begin()+i,p.end(),[&d](int x,int y){return d[x]<d[y];});
            for(int j=i+1;j<i+d[p[i]]+1;j++){
                ans[p[i]][p[j]]=1;
                ans[p[j]][p[i]]=0;
            }
            for(int j=i+d[p[i]]+1;j<n;j++){
                ans[p[j]][p[i]]=1;
                ans[p[i]][p[j]]=0;
                d[p[j]]--;
            }
        }
        for(int i=1;i<n;i++){
            for(int j=0;j<i;j++) cout<<ans[i][j];
            cout<<endl;
        }
    }

    return 0;
}