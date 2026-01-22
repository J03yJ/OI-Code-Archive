#include<bits/stdc++.h>

using namespace std;

const int N=1e6+9;

int a[N],d[N],n,m,k;

int main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n>>m>>k;
        for(int i=1;i<=n;i++) cin>>d[i]>>a[i];

        int cnt=0;
        d[n+1]=3e6;
        deque<int> q;
        for(int i=1,cur=-1;i<=n;i++){
            cur=max(cur,d[i]);
            q.push_back(i);
            while(q.size()&&cur<d[i+1]){
                int tmp=m;
                while(q.size()&&d[q.front()]<=cur-k) q.pop_front();
                if(a[q.back()]>tmp){
                    int cc=min(d[i+1]-cur,a[q.back()]/m);
                    cc=min(cc,d[q.back()]+k-cur);
                    a[q.back()]-=cc*m;
                    cur+=cc;
                    cnt+=cc;
                }else{
                    while(q.size()&&a[q.back()]<=tmp){
                        tmp-=a[q.back()];
                        q.pop_back();
                    }
                    if(q.size()){
                        a[q.back()]-=tmp;
                        tmp=0;
                    }
                    if(!tmp) cnt++;
                    cur++;
                }
            }
        }
        cout<<cnt<<endl;
    }

    return 0;
}