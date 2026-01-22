#include<bits/stdc++.h>

using namespace std;

ifstream fin("hash.in");
ofstream fout("hash.out");
#define cin fin
#define cout fout

#define endl '\n'
using ull=unsigned long long;
const int N=(1<<10)+9;

int op[N],a[N][N],c[N],res[N],n,m;
vector<int> v[N],tmp;

int id[N],cnt;
bitset<N> r[N];
inline void Gauss(){
    cnt=0;
    tmp.clear();
    for(int i=0;i<n;i++){
        if(!r[cnt][i]){
            int pos=cnt;
            for(int j=cnt+1;j<n;j++){
                if(r[j][i]){
                    pos=j;
                    break ;
                }
            }
            if(!r[pos][i]){
                tmp.push_back(i);
                continue ;
            }
            swap(r[cnt],r[pos]);
        }
        id[cnt++]=i;
        for(int j=i+1;j<n;j++) if(r[j][i]) r[j]^=r[i];
    }
}
inline void Solve(){
    for(int i=cnt-1;~i;i--){
        res[id[i]]=c[i];
        for(int j=0;j<n;j++) if(r[i][j]) res[id[i]]^=res[j];
    }
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n>>m;
        for(int i=1;i<=m;i++){
            cin>>op[i];
            if(op[i]==1||op[i]==2) cin>>a[i][0];
            else{
                string s;
                cin>>s;
                for(int j=0;j<s.size();j++) a[i][j]=s[j]-'0';
                for(int j=s.size();j<n;j++) a[i][j]=0;
            }
        }

        for(int i=1;i<=m;i++){
            if(op[i]==1){
                int len=a[i][0];
                for(int i=len;i<n;i++) v[i-len].push_back(i);
            }else if(op[i]==2){
                int len=a[i][0];
                for(int i=len;i<n;i++) v[i].push_back(i-len);
            }else if(op[i]==3){
                for(int j=0;j<n;j++){
                    if(a[i][j]==0){
                        v[j].clear();
                        c[j]=0;
                    }
                }
            }else if(op[i]==4){
                for(int j=0;j<n;j++){
                    if(a[i][j]==1){
                        v[j].clear();
                        c[j]=1;
                    }
                }
            }
        }

        for(int i=0;i<n;i++){
            r[i].reset();
            for(int j:v[i]) r[i].set(j,r[i][j]^1);
            r[i].set(n,c[i]);
            v[i].clear();
            c[i]=0;
        }

        Gauss();
        if(!tmp.size()) cout<<"Yes"<<endl;
        else{
            cout<<"No"<<endl;
            for(int i=0;i<n;i++) res[i]=0;
            Solve();
            for(int i=0;i<n;i++) cout<<res[i];cout<<endl;
            for(int i=0;i<n;i++) res[i]=0;
            res[tmp.front()]=1;
            Solve();
            for(int i=0;i<n;i++) cout<<res[i];cout<<endl;
        }
    }

    return 0;
}