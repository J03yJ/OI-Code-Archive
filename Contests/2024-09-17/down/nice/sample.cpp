#include<bits/stdc++.h>

namespace IO{
    const int P=(1ll<<31)-1;
    int N,M,A,B;
    void GetSeed(int &n,int &m){
        scanf("%d%d%d%d",&N,&M,&A,&B);
        n=N,m=M;
    }
    int GetInt(){
        A=((A^B)+(B>>16)+(B<<16))&P;
        B=((A^B)+(A>>16)+(A<<16))&P;
        return (A^B)%N+1;
    }
    void GetEdge(int &u,int &v){
        u=GetInt(),v=GetInt();
        if(u==v) GetEdge(u,v);
    }
    const int MOD=998244353;
    int now,num;
    void PutInt(int x){
        ++num,++x;
        now+=1ll*num*x%MOD;
        now%=MOD;
    }
    void Flush(){
        printf("%d\n",now);
        now=num=0;
    }
}

namespace USER{
    int Solve(int u,int v){
        return 0;
    }
}

int main(){
    int T; scanf("%d",&T);
    while(T--){
        int n,m; IO::GetSeed(n,m);
        for(int i=1;i<=m;++i){
            int u,v; IO::GetEdge(u,v); // Get u and v
            int ans=USER::Solve(u,v); // Solve questions
            IO::PutInt(ans); // Put answers
        }
        IO::Flush(); // Flush answers
    }
    return 0;
}
