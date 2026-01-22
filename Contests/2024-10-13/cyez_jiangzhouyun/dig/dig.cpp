#include<bits/stdc++.h>

using namespace std;

ifstream fin("dig.in");
ofstream fout("dig.out");
#define cin fin
#define cout fout

#define int long long
const int N=3e3+9;
const int M=3e5+9;

struct Bar{
    int lx,rx,ly,ry;
    Bar(){}
    Bar(int a,int b,int c,int d){lx=a,ly=b,rx=c,ry=d;}
    Bar operator &(Bar x){
        return Bar(max(lx,x.lx),max(ly,x.ly),min(rx,x.rx),min(ry,x.ry));
    }
};
bool Valid(Bar x){return x.lx<=x.rx&&x.ly<=x.ry;}
void Merge(vector<pair<Bar,int>> &v,Bar x,bool flag){
    if(!Valid(x)) return ;
    auto tmp=v;
    for(auto p:tmp){
        if(Valid(p.first&x)) v.push_back({p.first&x,-p.second});
    }
    if(flag) v.push_back({x,1});
}

int a[N][N],n,m,k,q;
int op[M],qx[M],qy[M],ans[M];
void Add(Bar x,int k){
    a[x.rx+1][x.ry+1]+=k;
    a[x.lx][x.ry+1]-=k;
    a[x.rx+1][x.ly]-=k;
    a[x.lx][x.ly]+=k;
}
void Calc(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            a[i][j]+=a[i][j-1]+a[i-1][j]-a[i-1][j-1];
        }
    }
}

int t[N][N],mn[N][N],r[N][N];
vector<int> w[M];
int tr[M];
void Modify(int x,int k){
    x++;
    while(x<=m+1){
        tr[x]+=k;
        x+=x&-x;
    }
}
int Query(int x){
    x++;
    int sum=0;
    while(x){
        sum+=tr[x];
        x&=x-1;
    }
    return sum;
}

signed main(){
    cin>>n>>k>>m;
    for(int i=1,tot;i<=m;i++){
        cin>>tot;
        vector<pair<int,int>> s(tot);
        for(int j=0;j<tot;j++) cin>>s[j].first>>s[j].second;
        vector<Bar> b(tot);
        for(int j=0,x,y;j<tot;j++){
            x=s[j].first,y=s[j].second;
            b[j]=Bar(max(x-k+1,1ll),max(y-k+1,1ll),x,y);
        }
        vector<pair<Bar,int>> tmp;
        for(int j=0;j<tot;j++) Merge(tmp,b[j],1);
        for(auto p:tmp) Add(p.first,p.second);
    }
    Calc();
    
    cin>>q;
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) t[i][j]=q+1;
    for(int i=1;i<=q;i++){
        cin>>op[i];
        if(op[i]==1) cin>>qx[i]>>qy[i],t[qx[i]][qy[i]]=min(t[qx[i]][qy[i]],i);
        else cin>>qx[i];
    }
    for(int i=1;i<=n;i++){
        deque<int> q;
        for(int j=n;j>=1;j--){
            while(q.size()&&q.front()>j+k-1) q.pop_front();
            while(q.size()&&t[i][q.back()]>t[i][j]) q.pop_back();
            q.push_back(j);
            mn[i][j]=t[i][q.front()];
        }
    }
    for(int j=1;j<=n;j++){
        deque<int> q;
        for(int i=n;i>=1;i--){
            while(q.size()&&q.front()>i+k-1) q.pop_front();
            while(q.size()&&mn[q.back()][j]>mn[i][j]) q.pop_back();
            q.push_back(i);
            r[i][j]=mn[q.front()][j];
            if(i<=n-k+1&&j<=n-k+1) w[r[i][j]-1].push_back(a[i][j]);
        }
    }

    for(int i=q;i>=1;i--){
        for(int x:w[i]) Modify(x,1);
        if(op[i]==2){
            if(qx[i]<=m) ans[i]=Query(m)-Query(qx[i]-1);
            else ans[i]=0;
        }
    }
    int tmp=(n-k+1)*(n-k+1);
    for(int i=1;i<=q;i++){
        if(op[i]==2) cout<<fixed<<setprecision(8)<<ans[i]/double(tmp)<<endl;
    }

    return 0;
}