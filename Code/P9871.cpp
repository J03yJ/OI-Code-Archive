#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=4e5+9;

int f[N][2],pos[N],len[N],w[N],n,m,k,d,c,T;
vector<pair<int,int>> op;

struct Node{
    int l,r,dat,tag;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].r
#define tag(x) tr[x].tag

void Push(int x,int k){dat(x)+=k,tag(x)+=k;}
void PushDown(int x){Push(x<<1,tag(x)),Push(x<<1|1,tag(x));}
void PushUp(int x){dat(x)=max(dat(x<<1),dat(x<<1|1));}


int main(){
    cin>>c>>T;
    while(T--){
        vector<int> val;
        cin>>n>>m>>k>>d;
        for(int i=1;i<=m;i++){
            cin>>pos[i]>>len[i]>>w[i];
            val.push_back(pos[i]);
            val.push_back(pos[i]-len[i]+1);
        }
        val.push_back(1);
        
        sort(val.begin(),val.end());
        val.erase(unique(val.begin(),val.end()),val.end());
        for(int i=1;i<=m;i++){
            f[i][0]=min(f[i-1][0],f[i-1][1]);
        }
    }

    return 0;
}