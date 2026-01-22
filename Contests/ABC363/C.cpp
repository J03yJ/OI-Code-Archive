#include<bits/stdc++.h>

using namespace std;

const int N=19;
char s[N];
int p[N];

int main(){
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>s[i],p[i]=i;

    int cnt=0;
    do{
        int flag=0;
        for(int i=1;i<=n-k+1;i++){
            bool err=1;
            for(int j=1;j<=k;j++){
                int l=i+j-1,r=i+(k-j+1)-1;
                if(s[p[l]]!=s[p[r]]) err=0;
            }
            flag|=err;
        }
        if(!flag) cnt++;
    }while(next_permutation(p+1,p+n+1));

    map<int,int> mp;
    for(int i=1;i<=n;i++){
        mp[s[i]]++;
        cnt/=mp[s[i]];
    }

    cout<<cnt<<endl;

    return 0;
}