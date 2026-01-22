#include<bits/stdc++.h>

using namespace std;

const int N=1e6+9;

struct DelHeap{
    priority_queue<int> p,q;
    inline void Insert(int x){p.push(x);}
    inline void Erase(int x){q.push(x);}
    inline int Top(){
        while(q.size()&&p.top()==q.top()) p.pop(),q.pop();
        return p.top();
    }
    inline int Size(){return p.size()-q.size();}
    inline void Clear(){
        while(p.size()) p.pop();
        while(q.size()) q.pop();
    }
};

int n;
char a[2][N];
DelHeap lck[2],num[10],tmp;
set<int> rem;
inline int PopTo(int pos){
    int cnt=0;
    while(tmp.Size()&&tmp.Top()>=pos) rem.erase(tmp.Top()),tmp.Erase(tmp.Top()),cnt++;
    for(int k=0;k<=1;k++) while(lck[k].Size()&&lck[k].Top()>=pos) rem.erase(lck[k].Top()),lck[k].Erase(lck[k].Top()),cnt++;
    for(int k=1;k<=9;k++) while(num[k].Size()&&num[k].Top()>=pos) rem.erase(num[k].Top()),num[k].Erase(num[k].Top()),cnt++;
    return cnt;
}
inline void Clear(){
    tmp.Clear();
    for(int k=0;k<=1;k++) lck[k].Clear();
    for(int k=1;k<=9;k++) num[k].Clear();
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[0][i];
        for(int i=1;i<=n;i++) cin>>a[1][i];

        vector<char> stk;
        int ans[2]={0,0};
        for(int i=1,cur=0,l=0;i<=n;i+=cur,cur^=1){
            int id=i<<1|cur,tm=0;
            char op=a[cur][i];
            if(op=='Q'){
                // lck[l^1].Insert(id);
                stk.push_back('Q');
            }else if(op=='q'){
                // lck[l].Insert(id);
                stk.push_back('q');
            }else if(op=='R'){
                // tmp.Insert(id);
                stk.push_back('R');
                for(char &c:stk){
                    if(c=='Q') c='q';
                    else if(c=='q') c='Q';
                }
                // l^=1;
            }else if(op=='K'){
                // tmp.Insert(id);
                // if(!lck[l^1].Size()) continue ;
                // int pos=lck[l^1].Top();
                // lck[l^1].Erase(pos);
                // lck[l].Insert(pos);
                stk.push_back('K');
                for(int i=stk.size()-1;~i;i--){
                    if(stk[i]=='Q'){
                        stk[i]='q';
                        break ;
                    }
                }
            }else if(op=='J'){
                // int pos=lck[l^1].Size()?lck[l^1].Top():0;
                // ans[cur]+=PopTo(pos)+1;
                ans[cur]++;
                while(stk.size()){
                    char c=stk.back();
                    stk.pop_back();
                    ans[cur]++;
                    if(c=='Q') break ;
                }
            }else{
                // int t=op-'0';
                // int p0=num[t].Size()?num[t].Top():0;
                // int p1=lck[l^1].Size()?lck[l^1].Top():0;
                // if(p0>p1) ans[cur]+=tm=PopTo(p0)+1;
                // else{
                //     num[t].Insert(id);
                //     if(!lck[l^1].Size()) continue ;
                //     lck[l^1].Erase(p1);
                //     lck[l].Insert(p1);
                // }
                for(int j=stk.size()-1;~j;j--){
                    if(stk[j]==a[cur][i]){
                        ans[cur]++;
                        while(stk.size()>j) ans[cur]++,stk.pop_back();
                        goto lab;
                    }else if(stk[j]=='Q'){
                        stk[j]='q';
                        break ;
                    }
                }
                stk.push_back(a[cur][i]);
                lab:;
            }
            // for(char c:stk) cout<<c<<' ';cout<<endl;
            // cout<<ans[0]<<' '<<ans[1]<<endl;
        }

        cout<<ans[0]<<' '<<ans[1]<<endl;
        Clear();
        rem.clear();
    }

    return 0;
}