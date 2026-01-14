#include<bits/stdc++.h>

using namespace std;

#define For(i,l,r) for(int i=(l);i<=(r);i++)
#define Rof(i,r,l) for(int i=(r);i>=(l);i--)
#define Rep(i,n) for(int i=0;i<(n);i++)
#define ssiz(x) (signed)x.size()
#define allc(x) x.begin(),x.end()
#define fir(x) x.first
#define sec(x) x.second
using ll=long long;
using ull=unsigned long long;
using pii=pair<int,int>;
template<class T1,class T2>void ChMin(T1 &x,T2 y){if(y<x) x=y;}
template<class T1,class T2>void ChMax(T1 &x,T2 y){if(y>x) x=y;}
template<class T>using svector=vector<vector<T>>;
template<class T>using cvector=vector<vector<vector<T>>>;

const int N=1e6+9;

int n,m;
char s[N],t[N];

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'
    
    cin>>n>>m;
    For(i,1,n) cin>>s[i];
    For(i,1,m) cin>>t[i];

    char c=t[m--];
    sort(t+1,t+m+1,greater<char>());
    int j=1;
    For(i,1,n){
        if(s[i]<max(t[j],c)){
            if(t[j]<=c){
                Rof(k,m,j) t[k+1]=t[k];
                t[j]=c,c=0,m++;
            }
            s[i]=t[j++];
        }
    }

    if(c){
        For(i,1,n){
            if(s[i]==c){
                c=0;
                break ;
            }
        }
        if(c) s[n]=c;
    }
    For(i,1,n) cout<<s[i];cout<<endl;
    
    return 0;
}