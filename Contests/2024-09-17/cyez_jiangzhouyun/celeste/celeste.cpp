#include<bits/stdc++.h>

using namespace std;

ifstream fin("celeste.in");
ofstream fout("celeste.out");
#define cin fin
#define cout fout

#define double long double
const int N=5e1+9;
const double eps=1e-9;

int m,dx,dy,sp,ssp=2,jp;
int sta=0,lsta=0;
double cx,cy,vx,vy;

int Sgn(double x){
    if(x<-eps) return -1;
    if(x>eps) return 1;
    return 0;
}
struct Wall{
    double x0,y0,x1,y1;
    Wall(){}
    Wall(double a,double b,double c,double d){
        x0=a,y0=b,x1=c,y1=d;
    }
    bool In(double x,double y){
        if(Sgn(x-x0)>0&&Sgn(x1-x)>0){
            if(Sgn(y-y0)>0&&Sgn(y1-y)>0) return 1;
        }
        return 0;
    }
    bool Up(double x,double y,int flag=0){
        if(flag==1) return Sgn(y-y0)==0&&Sgn(x-x0)>=0&&Sgn(x1-x)>=0;
        else if(flag==-1) return Sgn(y-y0)==0&&Sgn(x-x0)>0&&Sgn(x1-x)>0;
        return Sgn(y-y0)==0&&Sgn(x-x0)>=0&&Sgn(x1-x)>=0;
    }
    bool Left(double x,double y,int flag=0){
        if(flag==1) return Sgn(x-x0)==0&&Sgn(y-y0)>=0&&Sgn(y1-y)>=0;
        else if(flag==-1) return Sgn(x-x0)==0&&Sgn(y-y0)>0&&Sgn(y1-y)>0;
        return Sgn(x-x0)==0&&Sgn(y-y0)>0&&Sgn(y1-y)>=0;
    }
    bool Right(double x,double y,int flag=0){
        if(flag==1) return Sgn(x-x1)==0&&Sgn(y-y0)>=0&&Sgn(y1-y)>=0;
        else if(flag==-1) return Sgn(x-x1)==0&&Sgn(y-y0)>0&&Sgn(y1-y)>0;
        return Sgn(x-x1)==0&&Sgn(y-y0)>0&&Sgn(y1-y)>=0;
    }
    bool Down(double x,double y,int flag=0){
        if(flag==1) return Sgn(y-y1)==0&&Sgn(x-x0)>=0&&Sgn(x1-x)>=0;
        else if(flag==-1) return Sgn(y-y1)==0&&Sgn(x-x0)>0&&Sgn(x1-x)>0;
        return Sgn(y-y1)==0&&Sgn(x-x0)>0&&Sgn(x1-x)>0;
    }
};
Wall w[N];
bool CheckOG(double x,double y){
    for(int i=1;i<=m;i++) if(w[i].Up(x,y)) return 1;
    return 0;
}
bool CheckOW(double x,double y){
    for(int i=1;i<=m;i++) if(w[i].Left(x,y)||w[i].Right(x,y)) return 1;
    return 0;
}
bool CheckIA(double x,double y){
    return !CheckOW(x,y)&&!CheckOG(x,y);
}
bool Valid(double x,double y){
    for(int i=1;i<=m;i++) if(!w[i].In(x,y)) return 0;
    return 1;
}
int GetVec(double x,double y){
    for(int i=1;i<=m;i++){
        if(w[i].Up(x,y)) return 1;
        else if(w[i].Down(x,y)) return 2;
        else if(w[i].Left(x,y)) return 3;
        else if(w[i].Right(x,y)) return 4;
    }
    return 0;
}

double Dist(double x,double y,double vx,double vy){
    double ans=1;
    double sx=x+eps*Sgn(vx)*2,sy=y+eps*Sgn(vy)*2;
    for(int i=1;i<=m;i++){
        if(Sgn(vx)){
            if(!w[i].Left(x,y,1)){
                double tl=(w[i].x0-x)/vx;
                if(tl>=0){
                    double yl=y+tl*vy;
                    if(w[i].Left(w[i].x0,yl,-1)) ans=min(ans,tl);
                }
            }else if(w[i].In(sx,sy)) ans=0;
            if(!w[i].Right(x,y,1)){
                double tr=(w[i].x1-x)/vx;
                if(tr>=0){
                    double yr=y+tr*vy;
                    if(w[i].Right(w[i].x1,yr,-1)) ans=min(ans,tr);
                }
            }else if(w[i].In(sx,sy)) ans=0;
        }
        if(Sgn(vy)){
            if(!w[i].Up(x,y,1)){
                double tu=(w[i].y0-y)/vy;
                if(tu>=0){
                    double xu=x+tu*vx;
                    if(w[i].Up(xu,w[i].y0,-1)) ans=min(ans,tu);
                }
            }else if(w[i].In(sx,sy)) ans=0;
            if(!w[i].Down(x,y,1)){
                double td=(w[i].y1-y)/vy;
                if(td>=0){
                    double xd=x+td*vx;
                    if(w[i].Down(xd,w[i].y1,-1)) ans=min(ans,td);
                }
            }else if(w[i].In(sx,sy)) ans=0;
        }
    }
    return ans;
}

bool TryJp(string op){
    if(string::npos==op.find('K')) return 0;
    if(sp) return 0;
    if(CheckIA(cx,cy)){
        if(jp>0) sta=1;
        else return 0;
    }else if(CheckOG(cx,cy)) jp=12,sta=1;
    else jp=1,sta=1;
    return 1;
}
bool TrySp(string op){
    if(sp>0) sta=2;
    else return 0;
    return 1;
}
bool TrySsp(string op){
    if(string::npos==op.find('L')) return 0;
    if(sp) return 0;
    if(!ssp) return 0;
    sta=2;
    sp=10;
    ssp--;
    if(string::npos!=op.find('A')) dx=-1;
    else if(string::npos!=op.find('D')) dx=1;
    else dx=0;
    if(string::npos!=op.find('W')) dy=-1;
    else if(string::npos!=op.find('S')) dy=1;
    else dy=0;
    return 1;
}
void Try(string op){
    lsta=sta;
    if(!TryJp(op)){
        if(!TrySp(op)){
            if(!TrySsp(op)){
                jp=sp=0;
                sta=0;
            }
        }
    }
}

void UpdNSp(){
    if(!(lsta==2&&sta!=2)) return ;
    if(!dx) vx=0,vy=160*dy;
    else if(!dy) vx=160*dx,vy=0;
    else vx=113*dx,vy=113*dy;
    dx=dy=0;
}
void UpdOnX(string op){
    if(sta==2) return ;
    double p=Sgn(vx),k=0;
    if(string::npos!=op.find('A')) k=-1;
    else if(string::npos!=op.find('D')) k=1;
    double a=0,lim=0;
    if(!k){
        if(CheckOG(cx,cy)) a=-16.7*p;
        else a=-10.8*p;
        lim=0;
    }else if(p*k>0&&Sgn(abs(vx)-90)>0){
        if(CheckOG(cx,cy)) a=-6.7*k;
        else a=-4.3*k;
        lim=90*k;
    }else{
        if(CheckOG(cx,cy)) a=45*k;
        else a=30*k;
        lim=90*k;
    }
    double v=vx+a;
    if(Sgn((v-lim)*(vx-lim))<=0) vx=lim;
    else vx=v;
}
void UpdOnY(string op){
    if(sta==2) return ;
    double a=0,lim=0;
    if(CheckIA(cx,cy)) a=15;
    else if(CheckOW(cx,cy)) a=1.9;
    if(string::npos!=op.find('S')) lim=240;
    else lim=160;
    vy=min(lim,vy+a);
}
void UpdR(){
    if(sta==1){
        vy=-105;
        jp--;
        if(CheckOW(cx,cy)){
            if(GetVec(cx,cy)==4) vx+=130;
            else vx-=130;
        }
    }else if(sta==2){
        if(sp==10){
            if(!dx) vx=0,vy=240*dy;
            else if(!dy) vx=240*dx,vy=0;
            else vx=169*dx,vy=169*dy;
        }
        sp--;
    }
}
void Run(){
    double t=Dist(cx,cy,vx,vy);
    cx+=vx*t;
    cy+=vy*t;
    if(t!=1){
        int pos=GetVec(cx,cy);
        if(pos==1||pos==2) vy=0;
        if(pos==3||pos==4) vx=0;
    }
}
void Done(){
    if(CheckOG(cx,cy)) ssp=2;
}

int main(){
    cin>>m;
    for(int i=1;i<=m;i++){
        cin>>w[i].x0>>w[i].y0>>w[i].x1>>w[i].y1;
    }
    cin>>cx>>cy;
    int T;
    cin>>T;
    while(T--){
        string op;
        cin>>op;
        Try(op);
        UpdNSp();
        UpdOnX(op);
        UpdOnY(op);
        UpdR();
        Run();
        Done();
        cout<<fixed<<setprecision(6)<<cx<<' '<<cy<<endl;
    }
    return 0;
}