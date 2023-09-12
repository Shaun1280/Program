#include<bits/stdc++.h>
using namespace std;
map<int, string> Time;
int main(){
    Time[1]="one",Time[2]="two",Time[3]="three";
    Time[4]="four",Time[5]="five",Time[6]="six";
    Time[7]="seven",Time[8]="eight",Time[9]="nine";
    Time[10]="ten",Time[11]="eleven",Time[12]="twelve";
    Time[13]="thirteen",Time[14]="fourteen",Time[15]="quarter";
    Time[16]="sixteen",Time[17]="seventeen",Time[18]="eighteen";
    Time[19]="nineteen",Time[20]="twenty",Time[21]="twenty one";
    Time[22]="twenty two",Time[23]="twenty three ",Time[24]="twenty four";
    Time[25]="twenty five",Time[26]="twenty six",Time[27]="twenty seven";
    Time[28]="twenty eight",Time[29]="twenty nine",Time[30]="half past ";
    string Hour, Min;
    stringstream ss_h,ss_m;
    int h,m;
    cin>>Hour>>Min;
    ss_m<<Min, ss_m>>m;
    ss_h<<Hour,ss_h>>h;
    if(Min=="00") cout<<Time[h]<<" o' clock";
    if(Min=="30") cout<<Time[m]<<Time[h];
    if(0<m&&m<30){
        if(m==1) cout<<Time[m]<<" minute past "<<Time[h];
        else if(m==15) cout<<Time[m]<<" past "<<Time[h];
        else cout<<Time[m]<<" minutes past "<<Time[h];
    }
    if(m>30){
        if(m==59) cout<<Time[60-m]<<" minute to "<<Time[h+1];
        else if(m==45) cout<<Time[60-m]<<" to "<<Time[h+1];
        else cout<<Time[60-m]<<" minutes to "<<Time[h+1];
    }
    return 0;
}
