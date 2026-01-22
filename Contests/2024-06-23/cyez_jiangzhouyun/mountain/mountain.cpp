#include<bits/stdc++.h>

using namespace std;

ifstream fin("mountain.in");
ofstream fout("mountain.out");
#define cin fin
#define cout fout

const int N=5009;
int a[N][N],n,fa[N<<1];
int find(int x){
    if(fa[x]==x) return x;
    else return fa[x]=find(fa[x]);
}
void merge(int x,int y){
    fa[find(y)]=find(x);
}

bool vis[N];
vector<int> son[N];

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            char c;
            cin>>c;
            if(c=='1') a[i][j]=1;
        }
    }

    for(int i=1;i<=n;i++){
        if(a[i][i]){
            cout<<"No"<<endl;
            return 0;
        }
    }

    for(int i=1;i<=(n<<1);i++) fa[i]=i;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(a[i][j]){
                merge(i,j+n);merge(j,i+n);
                if(find(i)==find(i+n)||find(j)==find(j+n)){
                    cout<<"No"<<endl;
                    return 0;
                }
            }
        }
    }

    for(int i=1;i<=(n<<1);i++) son[find(i)].push_back(i);
    vector<int> v;
    for(int i=1;i<=n;i++){
        if(vis[i]) continue ;
        int cnt1=0,cnt2=0;
        for(int x:son[find(i)]){
            int y=x;
            if(y>n) y-=n,cnt2++;
            else cnt1++;
            vis[y]=1;
        }
        for(int x:son[find(i)]){
            if(x>n&&cnt1>cnt2) v.push_back(x-n);
            else if(x<=n&&cnt1<=cnt2) v.push_back(x);
        }
    }
    sort(v.begin(),v.end());
    cout<<"Yes"<<endl;
    for(int x:v) cout<<x<<' ';cout<<endl;

    return 0;
}