#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
using namespace std;
#include<bits/stdc++.h>
#define random(a,b) (rand()%(b-a+1))+a
ofstream mycout("out.txt",ios::out);
struct pig
{
    int species; //黑猪为1 小花猪为2 大白花猪为3
    int id; 	//编号
    int styid;  //猪圈编号
    int gday; 	//成长天数(一个月按30天计)
    int infected=0; //被感染为1，没被感染为0
    double weight; //体重
    pig *next;
};
class pigsty
{
    private:
        pig *head=NULL;
        int isblack=0; //猪圈为黑猪圈为1，非黑为0
        int sum=0;
        int isinfected=0; //猪圈有感染猪为1, 没有为0
        int infectsum=0;
    public:
        pigsty();				//初始化
        int getspecies(int i);	//获取种类信息
        int getgday(int i);		//获取成长天数信息
        double getweight(int i);//获取重量
        double getprice();		//获取价钱
        void addpig(pig*p);		//加猪，主要用于初始化
        void insert(int i,int j);      //加猪，主要用于购买插入
        void clear();	             //出现感染猪，离开将该猪圈的猪全部清空
        int getsumspecies(int i);	//获取某种猪的数量
        int getsum()
        {
            return sum;
        }
        int getisblack()
        {
            return isblack;
        }
        int getisinfect()
        {
            return isinfected;
        }
        int getinfectsum()
        {
            return infectsum;
        }
        pig* gethead()
        {
            return head;
        }
        void setsum(int i)
        {
            sum=i;
        }
        void sethead(pig *p)
        {
            head=p;
        }
        void setisblack(int i)//设置黑猪圈,1为黑猪圈，0为非黑猪圈
        {
            isblack=i;
        }
        void setisinfect(int i)
        {
            isinfected=i;
        }
        void infectgame()
        {
            if(head==NULL)
            return;
            isinfected=1;
            infectsum++;
            pig *p;
            p=head;
            p->infected=1;
        }
        void addinfect()
        {
            srand((unsigned)time(0));
            pig *p;
            p=head;
            while(p)
            {
                if(p->infected!=1)
                {
                    if(random(1,100)<=50)
                    {
                        p->infected=1;
                        infectsum++;
                    }
                }
                p=p->next;
            }
        }
};
pigsty ps[100];
pigsty::pigsty()
{
    int sum=0;
    int isblack=0;
    head=NULL;
}
int pigsty::getspecies(int i)
{
    pig *p=head;
    for(int k=0;k<i&&p!=NULL;k++)
    {
        p=p->next;
    }
    return p->species;
}
int pigsty::getgday(int i)
{
    pig *p=head;
    for(int k=0;k<i&&p!=NULL;k++)
    {
        p=p->next;
    }
    return p->gday;
}
double pigsty::getweight(int i)
{
    pig *p=head;
    for(int k=0;k<i&&p!=NULL;k++)
    {
        p=p->next;
    }
    return p->weight;
}
double pigsty::getprice()
{
    double sellprice=0;
    if(head==0)
    return 0;
    int day,flag=0;
    pig*p=head,*p1=p;
    while(p)
    {
        day=p->gday;
        if(day>=360||p->weight>75)
        {
            if(sum==1)
            {
            setisblack(0);
            head=NULL;
            delete p;
            sum--;
            break;
            }
            if(p->species==1)
            {
                sellprice+=30*p->weight;
            }
            if(p->species==2)
            {
                sellprice+=14*p->weight;
            }
            if(p->species==3)
            {
                sellprice+=12*p->weight;
            }
            p1->next=p->next;
            delete p;
            p=p1->next;
            sum--;
            continue;
        }
        else if(flag==0)
        {
            flag=1;
            head=p;
        }
        p1=p;
        p=p1->next;
    }
    return sellprice;
}
void pigsty::addpig(pig *p)
{
    sum++;
    p->next=NULL;
    if(head==NULL)
    {
        head=p;
    }
    else
    {
        pig*p1=head;
        while(p1->next)
        {
            p1=p1->next;
        }
    p1->next=p;
    }
}
int pigsty::getsumspecies(int i)
{
    int count=0;
    pig *p=head;
    for(int k=0;k<sum&&p!=NULL;k++)
    {
        if(p->species==i)
        count++;
        p=p->next;
    }
    return count;
}
void pigsty::clear()
{
    if(head==NULL)
    {
        return;
    }
    else
    {
        pig*p=head;
        pig*p1=p;
        sum=0;
        setisblack(0);
        head=NULL;
        while(p)
        {
            p1=p;
            p=p->next;
            delete p1;
        }
        delete p;
    }
}
int getallpig(pigsty ps[])
{
    int count=0;
    for(int i=0;i<100;i++)
    {
        count+=ps[i].getsum();
    }
    return count;
}
int getallinfectpig(pigsty ps[])
{
    int count=0;
    for(int i=0;i<100;i++)
    {
        count+=ps[i].getinfectsum();
    }
    return count;
}
int getallpig1(pigsty ps[])
{
    int count=0;
    for(int i=0;i<100;i++)
    {
        count+=ps[i].getsumspecies(1);
    }
    return count;
}
int getallpig2(pigsty ps[])
{
    int count=0;
    for(int i=0;i<100;i++)
    {
        count+=ps[i].getsumspecies(2);
    }
    return count;
}
int getallpig3(pigsty ps[])
{
    int count=0;
    for(int i=0;i<100;i++)
    {
        count+=ps[i].getsumspecies(3);
    }
    return count;
}
void buypig(pigsty ps[])
{
    srand((unsigned)time(0));
    int pig1=random(0,15);
    int pig2=random(0,15);
    int pig3=random(0,15);
    mycout<<"购入"<<pig1<<"只黑猪、"<<pig2<<"只小花猪、"<<pig3<<"只大花白猪。"<<endl;
    while(pig1--)
    {
        for(int i=0;i<100;i++)
        {
            if(ps[i].getisblack()==1&&ps[i].getsum()<10)
            {
                ps[i].insert(1,i);
                break;
            }
            if(ps[i].gethead()==NULL)
            {
                ps[i].insert(1,i);
                ps[i].setisblack(1);
                break;
            }
        }
    }

    while(pig2--)
    {
        int ave=getallpig(ps)/100+1;
        for(int i=0;i<100;i++)
        {
            if(ps[i].getisblack()==0&&ps[i].getsum()<=ave)
            {
                ps[i].insert(2,i);
                break;
            }
            if(ps[i].gethead()==NULL)
            {
                ps[i].insert(2,i);
                ps[i].setisblack(0);
                break;
            }
        }
    }
    while(pig3--)
    {
        int ave=getallpig(ps)/100+1;
        for(int i=0;i<100;i++)
        {
            if(ps[i].getisblack()==0&&ps[i].getsum()<=ave)
            {
                ps[i].insert(3,i);
                break;
            }
            if(ps[i].gethead()==NULL)
            {
                ps[i].insert(3,i);
                ps[i].setisblack(0);
                break;
            }
        }
    }
}
void start(pigsty ps[])//程序开始，猪圈初始化
{
    int count=1000;	//开始先放400只猪
    pig *p;
    srand((unsigned)time(0));
    while(count--)
    {
        p=new pig;
        p->species=random(1,3);
        p->weight=random(20,50);
        p->gday=0;
        for(int i=0;i<100;i++)
        {
            if(p->species==1&&(ps[i].getisblack()==1||ps[i].gethead()==NULL)&&ps[i].getsum()<4)
            {
                p->id=ps[i].getsum();
                p->styid=i;
                ps[i].addpig(p);
                ps[i].setisblack(1);
                break;
            }
            if(p->species!=1&&ps[i].getisblack()==0&&ps[i].getsum()<4)
            {
                p->id=ps[i].getsum();
                p->styid=i;
                ps[i].addpig(p);
                break;
            }
        }
    }
}
void pigsty::insert(int i,int j)
{
    srand((unsigned)time(0));
    pig*p=new pig;
    p->species=i;
    p->styid=j;
    p->weight=random(20,30);
    p->gday=0;
    if(head==NULL)
    {
        p->id=0;
        p->next=NULL;
        head=p;
        sum++;
        return;
    }
    if(head->id!=0)
    {
        p->id=0;
        p->next=head;
        head=p;
        sum++;
        return;
    }
    else
    {
    pig*p1=head,*p2=p1;
    int k=0;
    while(p1->id==k&&p1->next)
    {
        k++;
        p2=p1;
        p1=p1->next;
    }
    if(p1->next==NULL)
    {
        p->id=sum;
        p->next=NULL;
        p1->next=p;
    }
    else
    {
        p->id=k;
        p2->next=p;
        p->next=p1;
    }
    sum++;
    }
}
void oneday(pigsty ps[])
{
    srand((unsigned)time(0));
    for(int i=0;i<100;i++)
    {
        pig *p;
        p=ps[i].gethead();
        while(p)
        {
            int w1=random(0,12);
            double w2=double(w1)/10.0;
            p->weight+=w2;
            p->gday++;
            p=p->next;
        }
    }
}
double getsumprice(pigsty ps[])
{
    double sumprice;
    for(int i=0;i<100;i++)
    {
        sumprice+=ps[i].getprice();
    }
    return sumprice;
}
void searchsty(pigsty ps[],int i)
{
    int sum,isblack;
    pig *p;
    sum=ps[i].getsum();
    isblack=ps[i].getisblack();
    p=ps[i].gethead();
    if(p==NULL)
    {
        cout<<"猪圈为空!"<<endl;
        return;
    }
    if(isblack==1)
    {
        cout<<"该猪圈是黑猪圈，共计有"<<sum<<"头黑猪。"<<endl;
    }
    else
    {
        cout<<"该猪圈为非黑猪圈，共计有"<<sum<<"头猪。"<<endl;
        int pig2=0,pig3=0;
        while(p)
        {
            if(p->species==2)
            pig2++;
            if(p->species==3)
            pig3++;
            p=p->next;
        }
        cout<<"其中小花猪有"<<pig2<<"头，"<<"大花白猪有"<<pig3<<"头。"<<endl;
    }
}
void searchpig(pigsty ps[],int i,int j)
{
    pig *p;
    p=ps[i].gethead();
    if(p==NULL)
    {
        cout<<"猪圈为空，无法查找！"<<endl;
    }
    int sp,gd,flag=0;
    double w;
    while(p)
    {
        if(p->id==j)
        {
            flag=1;
            break;
        }
        p=p->next;
    }
    if(flag==1)
    {
        sp=p->species;
        gd=p->gday;
        w=p->weight;
        cout<<"该猪的品种是：";
        if(sp==1)
        cout<<"黑猪。"<<endl;
        if(sp==2)
        cout<<"小花猪。"<<endl;
        if(sp==3)
        cout<<"大花白猪。"<<endl;
        cout<<"该猪的生长天数为："<<gd<<"天。"<<endl;
        cout<<"该猪的体重为"<<w<<"千克。"<<endl;
    }
    else
    {
        cout<<"查无此猪！"<<endl;
    }
}
void printallsty(pigsty ps[])
{
    int allpig1=0,allpig2=0,allpig3=0;
    int w1=0,w2=0,w3=0,w4=0;//w1体重0-25，w2体重25-50，w3体重50-75，w4体重>75
    int d1=0,d2=0,d3=0,d4=0;//d1饲养0-30，d2饲养31-60，d3饲养61-90，d4饲养>90
    cout<<"pigsty has "<<getallpig(ps)<<" pigs"<<endl;
    for(int i=0;i<100;i++)
    {
        pig *p=ps[i].gethead();
        while(p)
        {
            int sp,gd;
            double w;
            sp=p->species;
            gd=p->gday;
            w=p->weight;
            if(sp==1)allpig1++;
            if(sp==2)allpig2++;
            if(sp==3)allpig3++;
            if(gd>=0&&gd<=30)d1++;
            if(gd>30&&gd<=60)d2++;
            if(gd>60&&gd<=90)d3++;
            if(gd>90)d4++;
            if(w>=0&&w<=25)w1++;
            if(w>25&&w<=50)w2++;
            if(w>50&&w<=75)w3++;
            if(w>75)w4++;
            p=p->next;
        }
    }
    cout<<"blackpig:"<<allpig1<<" smallwhitepig:"<<allpig2<<" bigwhitepig:"<<allpig3<<endl;
    cout<<"weight:            0-25:"<<w1<<endl;
    cout<<"                  25-50:"<<w2<<endl;
    cout<<"                  50-75:"<<w3<<endl;
    cout<<"                    >75:"<<w4<<endl;
    cout<<"growday:           0-30:"<<d1<<endl;
    cout<<"                  31-60:"<<d2<<endl;
    cout<<"                  61-90:"<<d3<<endl;
    cout<<"                    >90:"<<d4<<endl;
 }
void fend(pigsty ps[])
{
    ofstream myycout("read.txt",ios::out);
    myycout<<getallpig(ps)<<endl;
    for(int i=0;i<100;i++)
    {
        pig *p=ps[i].gethead();
        while(p)
        {
            myycout<<p->styid<<" "<<p->id<<" "<<p->gday<<" "<<p->species<<" "<<p->weight<<endl;
            p=p->next;
        }
    }
    myycout.close();
}
void fstart(pigsty ps[])
{
    ifstream myycin("read.txt",ios::in);
    int allpig;
    myycin>>allpig;
    int myid,mygday,mysp,mystyid;
    double myweight;
    pig *p;
    for(int i=0;i<allpig;i++)
    {
        p=new pig;
        myycin>>mystyid>>myid>>mygday>>mysp>>myweight;
        p->species=mysp;
        p->weight=myweight;
        p->styid=mystyid;
        p->id=myid;
        p->gday=mygday;
        ps[mystyid].addpig(p);
        if(mysp==1)
        {
            ps[mystyid].setisblack(1);
        }
        else
        {
            ps[mystyid].setisblack(0);
        }
    }
    myycin.close();
}
void infectday(pigsty ps[])
{
    srand((unsigned)time(0));
    for(int i=0;i<100;i++)
    {
        if(ps[i].getisinfect()==1&&ps[i].gethead()!=NULL)
        {
            if(ps[i-1].getisinfect()!=1&&(i-1)>=0)
            {
                int chance=random(1,100);
                if(chance<=50)
                {
                    ps[i-1].infectgame();
                }
            }
            if(ps[i+1].getisinfect()!=1&&(i+1)<=99)
            {
                int chance=random(1,100);
                if(chance<=50)
                {
                    ps[i+1].infectgame();
                }
            }
            ps[i].addinfect();
        }
    }

}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPushButton *a=new QPushButton(this);
    a->setText("开始游戏");
    a->move(100,100);
    connect(a,&QPushButton::clicked,
            [=]()
    {
        start(ps);
    }
            );
    QPushButton *b=new QPushButton(this);
    b->setText("返回");
    b->move(100,200);
    connect(b,&QPushButton::clicked,
            [=]()
    {
        printallsty(ps);
    }
            );
    QPushButton *c=new QPushButton(this);
    c->setText("增长");
    c->move(200,200);
    connect(c,&QPushButton::clicked,
            [=]()
    {
        for(int i=0;i<30;i++)
        {
            oneday(ps);
        }
    }
            );
}

MainWindow::~MainWindow()
{
    delete ui;
}
