#include<bits/stdc++.h>

using namespace std;

enum Type{Weak,Average,Strong};
enum Weapon{B,G,M};
enum Action{BasicAttack,SpecialAttack,Skill};

struct Player{
    Type type;Weapon wep;
    int lev,maxhp,batk,bdef,slev,plev,watk;
    int hp,*tdef,*tatk,sadd;
    
    bool Dead(){
        return hp<=0;
    }
};
struct Team{
    vector<Player> ply;
    vector<int> id,rid;
    int tdef,tatk;
    
    void BuildId(){
        if(ply.size()==6){
            id.push_back(5);
            id.push_back(3);
            id.push_back(1);
            id.push_back(2);
            id.push_back(4);
            id.push_back(6);
        }else if(ply.size()==5){
            id.push_back(5);
            id.push_back(3);
            id.push_back(1);
            id.push_back(2);
            id.push_back(4);
        }else if(ply.size()==4){
            id.push_back(3);
            id.push_back(1);
            id.push_back(2);
            id.push_back(4);
        }else if(ply.size()==3){
            id.push_back(3);
            id.push_back(1);
            id.push_back(2);
        }else if(ply.size()==2){
            id.push_back(1);
            id.push_back(2);
        }else{
            id.push_back(1);
        }
        rid=vector<int>(0,id.size());
        for(int i=0;i<id.size();i++) rid[id[i]]=i;
    }
};

double TypeAddition(Type a,Type b){
    if(a==Weak){
        if(b==Weak) return 1.0;
        else if(b==Average) return 0.9;
        else return 1.1;
    }else if(a==Average){
        if(b==Average) return 1.0;
        else if(b==Strong) return 0.9;
        else return 1.1;
    }else{
        if(b==Strong) return 1.0;
        else if(b==Weak) return 0.9;
        else return 1.1;
    }
}
double PosAddition(int apos,int dpos){
    int k=(apos-dpos)%6;
    if(k==0) return 1.25;
    else if(k==1||k==5) return 1.0;
    else if(k==2||k==4) return 0.75;
    else return 0.0;
}

void Action(){
    
}

int main(){

}