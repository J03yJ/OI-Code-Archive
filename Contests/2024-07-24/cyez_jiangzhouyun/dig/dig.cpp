#include<bits/stdc++.h>

using namespace std;

ifstream fin("dig.in");
ofstream fout("dig.out");
#define cin fin
#define cout fout

const int N=69;

int n,dep,B,cnt,tot;
int blk[N],L[N],R[N];
int id[N][519],w[N][N];
vector<int> a[N][N];

int ocnt,acnt,pcnt;
vector<int> tmp[N];

vector<int> calc(int l,int r){
    vector<int> res;
    res.push_back(0);
    if(l==r){
        for(int i=1;i<=R[l]-L[l]+1;i++) res.push_back(w[l][i]);
        return res;
    }
    int mid=l+r>>1;
    vector<int> lc=calc(l,mid),rc=calc(mid+1,r);
    int lim=lc.size()-1+rc.size()-1;
    for(int i=0;i<lc.size();i++){
        for(int j=0;j<rc.size();j++){
            if(!i&&!j) continue ;
            if(!i) tmp[j].push_back(rc[j]);
            else if(!j) tmp[i].push_back(lc[i]);
            else{
                tmp[i+j].push_back(++cnt);
                cout<<"AND "<<2<<' '<<lc[i]<<' '<<rc[j]<<endl;
                acnt++;
                pcnt+=2;
            }
        }
    }
    for(int i=1;i<=lim;i++){
        if(tmp[i].size()>1){
            res.push_back(++cnt);
            cout<<"OR "<<tmp[i].size();
            for(int x:tmp[i]) cout<<' '<<x;
            cout<<endl;
            ocnt++;
            pcnt+=tmp[i].size();
        }else if(tmp[i].size()) res.push_back(tmp[i].back());
        tmp[i].clear();
    }
    return res;
}

int main(){
    cin>>n>>dep;

    B=sqrt(n);
    for(int i=1;i<=n;i++){
        blk[i]=(i-1)/B+1;
        if(!L[blk[i]]) L[blk[i]]=i;
        R[blk[i]]=i;
    }

    cnt=n;
    for(int i=1;i<=blk[n];i++){
        int len=R[i]-L[i]+1;
        for(int j=0;j<len;j++) id[i][1<<j]=L[i]+j;
        for(int sta=1;sta<(1<<len);sta++){
            a[i][__builtin_popcount(sta)].push_back(id[i][sta]);
            for(int j=0;j<len;j++){
                if(sta>>j&1) continue ;
                if(id[i][sta|(1<<j)]) continue ;
                id[i][sta|(1<<j)]=++cnt;
                cout<<"AND "<<2<<' '<<id[i][sta]<<' '<<id[i][1<<j]<<endl;
                acnt++;
                pcnt+=2;
                for(int k=j+1;k<len;k++){
                    if(sta>>k&1) continue ;
                    if(id[i][sta|(1<<j)|(1<<k)]) continue ;
                    id[i][sta|(1<<j)|(1<<k)]=++cnt;
                    cout<<"AND "<<3<<' '<<id[i][sta]<<' '<<id[i][1<<j]<<' '<<id[i][1<<k]<<endl;
                    acnt++;
                    pcnt+=3;
                }
            }
        }
        for(int j=1;j<=len;j++){
            if(a[i][j].size()>1){
                w[i][j]=++cnt;
                cout<<"OR "<<a[i][j].size();
                for(int x:a[i][j]) cout<<' '<<x;
                cout<<endl;
                ocnt++;
                pcnt+=a[i][j].size();
            }else if(a[i][j].size()) w[i][j]=a[i][j].back();
        }
    }

    vector<int> res=calc(1,blk[n]);
    cout<<"AND 1 "<<res[(n+1)/2]<<endl;
    cout<<"END"<<endl;

    // cout<<acnt<<' '<<ocnt<<' '<<pcnt<<endl;

    return 0;
}