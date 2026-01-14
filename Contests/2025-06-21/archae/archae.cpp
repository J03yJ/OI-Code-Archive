#include<bits/stdc++.h>
#include"archae.h"

using namespace std;

inline int Deg(int n,int x){
    int cnt=0;
    for(int i=1;i<=n;i++) if(i!=x) cnt+=query(i,x);
    return cnt;
}
inline vector<int> Out(int n,int x){
    vector<int> v;
    for(int i=1;i<=n;i++) if(i!=x&&query(x,i)) v.push_back(i);
    return v;
}

inline bool CheckC(int n,int x){
    vector<int> v=Out(n,x);
    if(v.size()!=3) return 0;
    for(int &y:v) y=Deg(n,y);
    sort(v.begin(),v.end(),greater<int>());
    if(v[0]==v[1]&&v[1]==n/2) return 1;
    else return 0; 
}
inline bool CheckD(int n,int x){
    vector<int> v=Out(n,x);
    if(v.size()==1) return CheckC(n,v.back());
    else return 0;
}
inline vector<int> GetAnsByD(int n,int D){
    int C=Out(n,D).back();
    vector<int> out=Out(n,C);
    for(auto it=out.begin();it!=out.end();it++){
        if(*it==D){
            out.erase(it);
            break ;
        }
    }
    out.push_back(C),out.push_back(D);
    return out;
}
inline vector<int> GetAnsByC(int n,int C){
    vector<int> out=Out(n,C);
    vector<int> deg(out);
    for(int &i:deg) i=Deg(n,i);
    for(int i=0;i<3;i++){
        if(deg[i]==1){
            int D=out[i],A=out[(i+1)%3],B=out[(i+2)%3];
            return {A,B,C,D};
        }
    }
}

vector<int> archae(int n){
    setTestType(2);
    int x=1,A=0,B=0,C=0,D=0;
    vector<int> out=Out(n,x);
    if(out.size()==n/2){
        if(Deg(n,out.front())!=n/2) x=out.front();
        else x=out.back();
    }
    if(CheckD(n,x)){
        return GetAnsByD(n,x);
    }else if(CheckC(n,x)){
        return GetAnsByC(n,x);
    }
    vector<int> a({x}),b,c,d;
    for(int i=1;i<=n;i++){
        if(i==x) continue ;
        if(query(i,x)) a.push_back(i);
        else c.push_back(i);
    }
    vector<int> s(a),t(c);
    while(s.size()){
        assert(t.size());
        if(query(s.back(),t.back())) t.pop_back();
        else s.pop_back();
    }
    int y=t.back();
    if(CheckD(n,y)){
        return GetAnsByD(n,y);
    }
    b.push_back(y);
    for(int i:c){
        if(i!=y){
            if(query(y,i)) b.push_back(i);
            else d.push_back(i);
        }
    }
    for(int i:d){
        vector<int> ra,rb;
        while(a.size()||b.size()){
            if(a.size()){
                if(query(i,a.back())){
                    while(rb.size()) b.push_back(rb.back()),rb.pop_back();
                    break ;
                }else ra.push_back(a.back()),a.pop_back();
            }
            if(b.size()){
                if(query(i,b.back())){
                    while(ra.size()) a.push_back(ra.back()),ra.pop_back();
                    break ;
                }else rb.push_back(b.back()),b.pop_back();
            }
        }
        if(!a.size()&&!b.size()){
            return GetAnsByD(n,i);
        }
    }
    return {0,0,0,0};
}

// mt19937 rng(4649);
// vector<int> archae(int n){
//     setTestType(1);
//     set<int> a,b;
//     for(int i=1;i<=n;i++){
//         map<int,int> mp;
//         int cnt=5,res=0;
//         while(cnt--){            
//             int j=rng()%n+1;            
//             if(mp[j]||i==j){                
//                 cnt++;
//                 continue ;
//             }
//             res+=query(i,j);
//             mp[j]=1;
//         }        
//         if(res>2) a.insert(i);        
//         else b.insert(i);
//     }
//     while(a.size()>1){
//         int A[2]={*a.begin(),*a.rbegin()};
//         int X[2]={*b.begin(),*b.rbegin()};
//         int F[2][2];
//         for(int i:{0,1}){
//             for(int j:{0,1}) F[i][j]=query(X[i],A[j]);
//         }
//         bool err=0;
//         for(int i:{0,1}) if(F[i][0]&&F[i][1]) b.erase(X[i]),err=1;
//         if(err) continue ;
//         if((F[0][0]&&F[1][1])||(F[0][1]&&F[1][0])){
//             for(int i:{0,1}) a.erase(A[i]);
//             for(int i:{0,1}) b.erase(X[i]);
//             err=1;
//         }
//         if(err) continue ;
//         if(!F[0][0]&&!F[1][0]) a.erase(A[0]);
//         if(!F[0][1]&&!F[1][1]) a.erase(A[1]);
//     }
//     int A=*a.begin(),B,C;
//     for(int i=1;i<=n;i++) if(i!=A&&!query(A,i)) C=i;
//     for(int i=1;i<=n;i++) if(i!=C&&query(C,i)) B=i;
//     return {A,B,C};
// }