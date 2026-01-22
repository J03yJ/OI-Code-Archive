#include<bits/stdc++.h>

using namespace std;

const int N=1e6+9;

int a[N],b[N],p[N],n,m,q;

struct Node{
    int l,r;
    int mx,mn,err;
}tr[N<<1];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define mx(x) tr[x].mx
#define mn(x) tr[x].mn
#define err(x) tr[x].err

void PushUp(int x){
    mx(x)=max(mx(x<<1),mx(x<<1|1));
    mn(x)=min(mn(x<<1),mn(x<<1|1));
    err(x)=err(x<<1)||err(x<<1|1)||(mx(x<<1)>mn(x<<1|1));
}
void Build(int x,int l,int r){
    mx(x)=mn(x)=err(x)=0;
    l(x)=l,r(x)=r;
    if(l(x)==r(x)) return ;
    int mid=l(x)+r(x)>>1;
    Build(x<<1,l,mid);
    Build(x<<1|1,mid+1,r);
    PushUp(x);
}
void Modify(int x,int pos,int k){
    if(l(x)==r(x)){
        mx(x)=mn(x)=k;
        err(x)=0;
        return ;
    }
    int mid=l(x)+r(x)>>1;
    if(pos<=mid) Modify(x<<1,pos,k);
    else Modify(x<<1|1,pos,k);
    PushUp(x);
}

struct PPQ{
    priority_queue<int> q1,q2;
    void insert(int x){q1.push(-x);}
    void erase(int x){q2.push(-x);}
    int top(){
        while(q2.size()&&q1.top()==q2.top()) q1.pop(),q2.pop();
        return -q1.top();
    }
    void clear(){
        while(q1.size()) q1.pop();
        while(q2.size()) q2.pop();
    }
}s[N];

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'

    int T;
    cin>>T;
    while(T--){
        cin>>n>>m>>q;
        for(int i=1;i<=n;i++) cin>>a[i],p[a[i]]=i;
        for(int i=1;i<=m;i++) cin>>b[i],b[i]=p[b[i]];
        
        Build(1,1,n);
        for(int i=1;i<=m;i++) s[b[i]].insert(i);
        for(int i=1;i<=n;i++){
            s[i].insert(m+1);
            Modify(1,i,s[i].top());
            // cout<<*s[i].begin()<<' ';
        }
        // cout<<endl;
        #define Out() (err(1)?"TIDAK":"YA")
        cout<<Out()<<endl;

        while(q--){
            int pos,k;
            cin>>pos>>k;
            k=p[k];
            if(b[pos]==k){
                cout<<Out()<<endl;
                continue ;
            }
            s[b[pos]].erase(pos);
            Modify(1,b[pos],s[b[pos]].top());
            b[pos]=k;
            s[b[pos]].insert(pos);
            Modify(1,b[pos],s[b[pos]].top());
            cout<<Out()<<endl;
        }

        for(int i=1;i<=n;i++) s[i].clear();
    }

    return 0;
}