#include<bits/stdc++.h>

using namespace std;

ifstream fin("gbc.in");
ofstream fout("gbc.out");
#define cin fin
#define cout fout

#define endl '\n'
const int N=1e6+9;
const int C=26;
const int S=(1<<13)+9;

int w[C][C],to[C],in[N],bel[N],f[S][2],g[S][2],n,c,cnt;
char s[N],t[N];

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n>>c;
    for(int i=1;i<=n;i++) cin>>s[i];
    for(int i=1;i<=n;i++) cin>>t[i];

    for(int i=0;i<C;i++) for(int j=0;j<C;j++) if(i!=j) w[i][j]+=c;
    for(int i=1;i<=n;i++){
        for(int j=0;j<C;j++){
            if(j==t[i]-'a') continue ;
            w[s[i]-'a'][j]++;
        }
    }
    for(int i=0;i<C;i++) for(int j=0;j<C;j++) if(w[i][j]<w[i][to[i]]) to[i]=j;
    
    bool flag=1;
    queue<int> q;
    for(int i=0;i<C;i++) if(to[i]!=i) in[to[i]]++;
    for(int i=0;i<C;i++) if(!in[i]) q.push(i),flag=0;
    while(q.size()){
        int x=q.front();
        q.pop();
        if(!--in[to[x]]) q.push(to[x]);
    }
    for(int i=0;i<C;i++){
        if(!in[i]) continue ;
        if(to[i]==i) continue ;
        cnt++;
        int cur=i;
        while(in[cur]){
            in[cur]=0;
            bel[cur]=cnt;
            cur=to[cur];
        }
    }
    
    memset(f,0x3f,sizeof f);
    f[(1<<cnt)-1][0]=0;
    for(int i=0;i<C;i++){
        memset(g,0x3f,sizeof g);
        for(int sta=(1<<cnt)-1;~sta;sta--){
            for(int p:{0,1}){
                for(int j=0;j<C;j++){
                    int tta=sta;
                    if(j!=to[i]&&bel[i]) tta&=((1<<cnt)-1)^(1<<bel[i]-1);
                    if((j!=to[i]||!bel[i])&&bel[j]) tta&=((1<<cnt)-1)^(1<<bel[j]-1);
                    g[tta][p|(j!=to[i])]=min(g[tta][p|(j!=to[i])],f[sta][p]+w[i][j]);
                }
            }
        }
        memcpy(f,g,sizeof f);
    }
    
    int ans=1e9;
    for(int sta=0;sta<(1<<cnt);sta++){
        for(int p=flag;p<=1;p++) ans=min(ans,f[sta][p]+c*__builtin_popcount(sta));
    }

    cout<<ans<<endl;
    
    return 0;
}