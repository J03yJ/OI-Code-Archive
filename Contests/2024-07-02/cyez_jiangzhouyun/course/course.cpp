#include<bits/stdc++.h>

using namespace std;

const int N=5e1+9;
const int M=2e5+9;

ifstream fin("course.in");
ofstream fout("course.out");
#define cin fin
#define cout fout

int Max,c,t;
int a[N][N];

int fi[M],ne[M],to[M],w[M],adj=1;
void adeg(int x,int y,int z){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
    w[adj]=z;
}

int lev[N];
bool bfs(int S,int T){
    for(int i=1;i<=T;i++) lev[i]=0;lev[S]=1;
    queue<int> q;
    q.push(S);
    while(q.size()){
        int x=q.front();
        q.pop();
        if(x==T) return 1;
        for(int i=fi[x];i;i=ne[i]){
            int y=to[i];
            if(!w[i]) continue ;
            if(lev[y]) continue ;
            lev[y]=lev[x]+1;
            q.push(y);
        }
    }
    return 0;
}
int dfs(int x,int T,int mn){
    // cout<<x<<' '<<T<<' '<<mn<<endl;
    if(x==T) return mn;
    int k=mn;
    for(int i=fi[x];i;i=ne[i]){
        if(!w[i]) continue ;
        int y=to[i];
        if(lev[y]!=lev[x]+1) continue ;
        int tmp=dfs(y,T,min(k,w[i]));
        k-=tmp;
        w[i]-=tmp;
        w[i^1]+=tmp;
        if(!k) return mn;
    }
    return mn-k;
}

bool Solve(){
    for(int i=1;i<=c;i++){
        for(int j=1;j<=t;j++){
            if(a[i][j]){
                adeg(j,i*t+j,1);
                adeg(i*t+j,j,0);
            }
            adeg(i*t+j,(c+1)*t+i,a[i][j]);
            adeg((c+1)*t+i,i*t+j,0);
        }
    }
    int S=(c+1)*t+c+1,T=(c+1)*t+c+2;
    for(int i=1;i<=t;i++) adeg(S,i,1),adeg(i,S,0);
    for(int i=1;i<=c;i++) adeg((c+1)*t+i,T,1),adeg(T,(c+1)*t+i,1);
    int sum=0;
    while(bfs(S,T)) sum+=dfs(S,T,1e9);
    return sum==c;
}

int b[N][N],cur;
bool ans;
void D(int x){
    if(x>cur){
        bool flag=1;
        for(int i=1;i<=c;i++){
            for(int j=1;j<=t;j++) if(b[i][j]<0) flag=0;
        }
        ans|=flag;
        return ;
    }
    vector<int> p(t);
    for(int i=0;i<t;i++) p[i]=i+1;
    do{
        for(int i=0;i<t;i++) if(p[i]<=c) b[p[i]][i+1]--;
        D(x+1);
        for(int i=0;i<t;i++) if(p[i]<=c) b[p[i]][i+1]++;
    }while(next_permutation(p.begin(),p.end()));
}

int main(){
    cin>>Max>>c>>t;
    for(int i=1;i<=c;i++) for(int j=1;j<=t;j++) cin>>a[i][j],b[i][j]=a[i][j];

    if(Max==1){
        cout<<Solve()<<endl;
        return 0;
    }

    for(cur=0;;cur++){
        ans=0;
        D(1);
        if(!ans){
            cout<<cur-1<<endl;
            return 0;
        }
    }

    return 0;
}