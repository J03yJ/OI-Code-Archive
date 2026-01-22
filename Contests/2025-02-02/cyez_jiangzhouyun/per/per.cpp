#include<bits/stdc++.h>

using namespace std;

ifstream fin("per.in");
ofstream fout("per.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=2e1+9;
const int M=(1<<20)+9;

int a[N],f[M],n;
int ans[N],cnt[N];

int cur[N],top;
void F(int x,int sum){
    if(x>n){
        if(sum<ans[top]) ans[top]=sum,cnt[top]=1;
        else if(sum==ans[top]) cnt[top]++;
        return ;
    }
    int tmp=sum;
    for(int i=1;i<=top;i++) if(cur[i]>a[x]) tmp++;
    cur[++top]=a[x];
    F(x+1,tmp);
    top--;
    F(x+1,sum);
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];

    f[0]=0;
    for(int i=0;i<=n;i++) ans[i]=n*n;
    F(1,0);

    for(int i=1;i<=n;i++) cout<<ans[i]<<' '<<cnt[i]<<endl;
    
    return 0;
}