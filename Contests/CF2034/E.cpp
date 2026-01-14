#include<bits/stdc++.h>

using namespace std;

int Check(vector<int> &a,vector<int> &b,int n){
    if(a.size()!=b.size()) return 0;
    if(a==b) return 1;
    for(int i=0;i<a.size();i++) if(a[i]+b[i]!=n+1) return 0;
    return 1;
}

int main(){
    int T;
    cin>>T;
    while(T--){
        int n,k;
        cin>>n>>k;
        if(n==1&&k==1){
            cout<<"YES"<<endl;
            cout<<1<<endl;
            continue ;
        }else if(n%2==0&&k%2==1||k==1){
            cout<<"NO"<<endl;
            continue ;
        }
        if(n<=10){
            int t=1;
            for(int i=1;i<=n;i++) t*=i;
            if(k%2==1) t-=3;
            if(k>t){
                cout<<"NO"<<endl;
                continue ;
            }
        }

        cout<<"YES"<<endl;
        vector<int> p,q,r;
        if(k&1){
            p=q=r=vector<int>(n,0);
            iota(p.begin(),p.end(),1);
            for(int i=0,j=n;j;i=(i+2)%n) q[i]=j--;
            for(int i=n-1,j=1;j<=n;i=(i+n-2)%n) r[i]=j++;
            for(int x:p) cout<<x<<' ';cout<<endl;
            for(int x:q) cout<<x<<' ';cout<<endl;
            for(int x:r) cout<<x<<' ';cout<<endl;
            k-=3;
        }

        vector<int> a(n,0);
        iota(a.begin(),a.end(),1);
        do{
            if(!k) break ;
            if(Check(a,p,n)) continue ;
            if(Check(a,q,n)) continue ;
            if(Check(a,r,n)) continue ;
            for(int x:a) cout<<x<<' ';cout<<endl;
            for(int x:a) cout<<n-x+1<<' ';cout<<endl;
            k-=2;
        }while(next_permutation(a.begin(),a.end()));
    }

    return 0;
}