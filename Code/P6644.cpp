#include<bits/stdc++.h>

using namespace std;

const int N=2e3+9;

int a[N][N],n;
int pre[N],suc[N],pos,tl;
void add_point(int x){
    if(!pre[pos]) pos=tl;
    if(pos==tl){
        pre[x]=pos;
        tl=suc[pos]=x;
        if(!pre[pos]||a[pre[pos]][pos]==a[pos][x]) pos=tl;
    }else{
        int l=pre[pos],r=suc[pos];
        if(a[l][pos]==a[pos][x]){
            suc[x]=r;pre[x]=pos;
            suc[pos]=pre[r]=x;
            if(a[r][x]==a[pos][x]) pos=r;
            else pos=x;
        }else{
            suc[x]=pos;pre[x]=l;
            suc[l]=pre[pos]=x;
            if(a[pos][x]==a[l][x]) pos=l;
            else pos=x;
        }
    }
}

int main(){
    cin>>n;
    for(int i=2;i<=n;i++){
        for(int j=1;j<i;j++){
            char c;
            cin>>c;
            a[i][j]=a[j][i]=(c=='R');
        }
    }

    for(int i=1;i<=n;i++){
        memset(pre,0,sizeof pre);
        memset(suc,0,sizeof suc);
        pos=tl=i;
        for(int j=i%n+1;j!=i;j=j%n+1) add_point(j);
        cout<<n<<endl;
        for(int j=i;j;j=suc[j]) cout<<j<<' ';cout<<endl;
    }

    return 0;
}