#include<bits/stdc++.h>
using namespace std;
/*
const int mon7 = 215; //7 months' days

string solve(int year)
{
    short int feb; //days in february
    if(year < 1918) //julian
        feb = year%4 ? 28 : 29;
    else if(year > 1918) //gregorian
        feb = !(year%400) || year%100&&!(year%4) ? 29 : 28;
    else //dreaded 1918
        feb = 15;
    feb = 256 - (feb + mon7);
    return to_string(feb) + ".09." + to_string(year);
}
 */
class Year{
    public: 
        int year, day,month,total,Case;
        bool leap;
        Year(int initialyear);
        void year1700_1917();
        void year1918();
        void year1919_2700();
        void print();
        void day_pass(int n);
};
Year::Year(int initialyear){
    year=initialyear, total=256;
    leap=false;
    if(year<1918){
        if(year%4==0) leap=true;
    }
    else{
       if(year%4==0&&year%100!=0&&year%400!=0) leap=true;
       if(year%400==0) leap=true; 
    }
    return;
}
void Year::day_pass(int n){
    day++;
    switch (n){
        case 1: if((month==1||month==3||month==5||month==7||month==8||month==10||month==12)&&day==32) day=1,month++;
                if(month==2&&day==29&&leap==false) day=1,month++;
                if(month==2&&day==30&&leap==true) day=1,month++;
                if((month==4||month==6||month==11||month==9)&&day==31) day=1, month++;
                break;
        case 2: if((month==1||month==3||month==5||month==7||month==8||month==10||month==12)&&day==32) day=1,month++;
                if(month==2&&day==29&&leap==false) day=1,month++;
                if(month==2&&day==30&&leap==true) day=1,month++;
                if((month==4||month==6||month==11||month==9)&&day==31) day=1, month++;
                break;
    }
}
void Year::year1700_1917(){
    int temp=total-31;
    day=0, month=2,Case=1;
    for(int i=32;i<=total;i++) Year::day_pass(Case);
}
void Year::year1918(){
    int temp=total-31;
    day=14,month=2, Case=2;
    for(int i=32;i<total;i++) Year::day_pass(Case);
}
void Year::year1919_2700(){
    int temp=total-31;
    day=0, month=2,Case=2;
    for(int i=32;i<=total;i++) Year::day_pass(Case);
}
void Year::print(){
    //cout<<leap<<endl;
    cout<<setw(2)<<setfill('0')<<day<<"."<<setw(2)<<setfill('0')<<month<<"."<<year;
}
int main(){
    int year;
    scanf("%d",&year);
    Year Y(year);
    if(year<=1917) Y.year1700_1917();
    if(year==1918) Y.year1918();
    if(year>=1919) Y.year1919_2700();
    Y.print();
    return 0;
}