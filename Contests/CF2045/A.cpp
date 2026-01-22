#include<bits/stdc++.h>

using namespace std;

int cnt[128];

int main(){
    string s;
    cin>>s;
    for(char c:s) cnt[c]++;

    int ans=0;
    for(int i=0;i<=cnt['Y'];i++){
        for(int j=0;j<=min(cnt['N'],cnt['G']);j++){
            int vcnt=i+cnt['A']+cnt['O']+cnt['E']+cnt['I']+cnt['U'];
            int ccnt=s.size()-vcnt-j;
            int wcnt=min(vcnt,ccnt/2);
            ans=max(ans,wcnt*3+min(2*wcnt,j));
        }
    }

    cout<<ans<<endl;

    return 0;
}