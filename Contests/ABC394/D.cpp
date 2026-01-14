#include<bits/stdc++.h>

using namespace std;

signed main(){
    string s;
    cin>>s;
    
    vector<int> stk;
    for(char c:s){
        int t=0;
        if(c=='<'||c=='>') t=0;
        else if(c=='('||c==')') t=1;
        else if(c=='['||c==']') t=2;
        if(c=='<'||c=='['||c=='(') stk.push_back(t);
        else{
            if(!stk.size()||stk.back()!=t){
                cout<<"No"<<endl;
                return 0;
            }else stk.pop_back();
        }
    }

    if(stk.size()) cout<<"No"<<endl;
    else cout<<"Yes"<<endl;

    return 0;
}