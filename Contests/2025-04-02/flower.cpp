#include<bits/stdc++.h>

using namespace std;

ifstream fin("flower.in");
ofstream fout("flower.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=5e4+9;
const int SQ=1e3+9;
inline void ChMin(int &x,int y){if(y<x) x=y;}

int px[N],py[N],n,m,c;

vector<int> p[N];
int f[N][SQ][2];
inline int F(int n){return n*(n+1)/2;}
inline int Work(){
    memset(f,0x3f,sizeof f);
    int lim=ceil(sqrt(c*m));
    f[0][0][0]=0;
    for(int i=0;i<=n;i++){
        sort(p[i].begin(),p[i].end(),greater<int>());
        p[i].erase(unique(p[i].begin(),p[i].end()),p[i].end());
        for(int j=lim,k=0;j>=0;j--){
            while(k<p[i].size()&&j<p[i][k]) k++;
            f[i][j][0]+=c*k;
            f[i][j][1]+=c*k;
        }
        for(int j=0;j<=lim;j++){
            // cout<<i<<' '<<j<<" : "<<f[i][j][0]<<' '<<f[i][j][1]<<endl;
            ChMin(f[i][j][1],f[i][j][0]);
            ChMin(f[i+1][j][0],f[i][j][1]+2*F(j));
            // ChMin(f[i+1][max(j-1,0)][0],f[i][j][1]+F(j)+F(j-1));
            ChMin(f[i+1][max(j-1,0)][0],f[i][j][0]);
            ChMin(f[i+1][j+1][1],f[i][j][1]);
        }
    }
    return f[n+1][0][0];
}
inline void Clear(){
    for(int i=0;i<=n;i++) p[i].clear();
}

inline void PushU(){for(int i=1;i<=m;i++) if(px[i]<min(py[i],n-py[i]+1)) p[py[i]].push_back(px[i]);}
inline void PushD(){for(int i=1;i<=m;i++) if(px[i]>max(py[i],n-py[i]+1)) p[py[i]].push_back(n-px[i]+1);}
inline void PushL(){for(int i=1;i<=m;i++) if(py[i]<min(px[i],n-px[i]+1)) p[px[i]].push_back(py[i]);}
inline void PushR(){for(int i=1;i<=m;i++) if(py[i]>max(px[i],n-px[i]+1)) p[px[i]].push_back(n-py[i]+1);}
inline void PushUL(bool flag){
    for(int i=1;i<=m;i++){
        if(px[i]!=py[i]) continue ;
        if(px[i]<=(n>>1)){
            if(flag) p[px[i]].push_back(py[i]);
            else p[py[i]].push_back(px[i]);
        }
    }
}
inline void PushDR(bool flag){
    for(int i=1;i<=m;i++){
        if(px[i]!=py[i]) continue ;
        if(px[i]>=n-(n>>1)+1){
            if(flag) p[px[i]].push_back(n-py[i]+1);
            else p[py[i]].push_back(n-px[i]+1);
        }
    }
}
inline void PushUR(bool flag){
    for(int i=1;i<=m;i++){
        if(px[i]!=n-py[i]+1) continue ;
        if(px[i]<=(n>>1)){
            if(flag) p[px[i]].push_back(n-py[i]+1);
            else p[py[i]].push_back(px[i]);
        }
    }
}
inline void PushDL(bool flag){
    for(int i=1;i<=m;i++){
        if(px[i]!=n-py[i]+1) continue ;
        if(px[i]>=n-(n>>1)+1){
            if(flag) p[px[i]].push_back(py[i]);
            else p[py[i]].push_back(n-px[i]+1);
        }
    }
}

int w[4][4];

signed main(){
    cin>>n>>m>>c;
    for(int i=1;i<=m;i++) cin>>px[i]>>py[i];

    // int a[100][100];
    // memset(a,0,sizeof a);
    // for(int i=1;i<=m;i++) a[px[i]][py[i]]=1;
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=n;j++) cout<<a[i][j];
    //     cout<<endl;
    // }

    // for(int i=1;i<=m;i++) cout<<px[i]<<' '<<py[i]<<' '<<min(py[i],n-py[i]+1)<<endl;
    for(int k:{0,1,2,3}){
        PushU();
        if(k&1) PushUL(0);
        if(k&2) PushUR(0);
        w[0][k]=Work();
        // cout<<w[0][k]<<endl;
        // for(int i=1;i<=n;i++){
        //     cout<<i<<" : ";
        //     for(int x:p[i]) cout<<x<<' ';cout<<endl;
        // }
        Clear();
    }
    // cout<<endl;
    for(int k:{0,1,2,3}){
        PushR();
        if(k&1) PushUR(1);
        if(k&2) PushDR(1);
        w[1][k]=Work();
        // cout<<w[1][k]<<endl;
        // for(int i=1;i<=n;i++){
        //     cout<<i<<" : ";
        //     for(int x:p[i]) cout<<x<<' ';cout<<endl;
        // }
        Clear();
    }
    // cout<<endl;
    for(int k:{0,1,2,3}){
        PushD();
        if(k&1) PushDR(0);
        if(k&2) PushDL(0);
        w[2][k]=Work();
        // cout<<w[2][k]<<endl;
        // for(int i=1;i<=n;i++){
        //     cout<<i<<" : ";
        //     for(int x:p[i]) cout<<x<<' ';cout<<endl;
        // }
        Clear();
    }
    // cout<<endl;
    for(int k:{0,1,2,3}){
        PushL();
        if(k&1) PushDL(1);
        if(k&2) PushUL(1);
        w[3][k]=Work();
        // cout<<w[3][k]<<endl;
        // for(int i=1;i<=n;i++){
        //     cout<<i<<" : ";
        //     for(int x:p[i]) cout<<x<<' ';cout<<endl;
        // }
        Clear();
    }
    // cout<<endl;

    int ans=1e9;
    for(int sta=0;sta<16;sta++){
        int tta=sta|(sta<<4);
        int res=0;
        // cout<<sta<<" : ";
        for(int k=0;k<4;k++){
            res+=w[k][(tta>>k&3)^1];
            // cout<<((tta>>k&3)^1)<<'/'<<w[k][(tta>>k&3)^1]<<' ';
        }
        // cout<<"= "<<res<<endl;
        ans=min(ans,res);
    }
    cout<<ans<<endl;

    return 0;
}