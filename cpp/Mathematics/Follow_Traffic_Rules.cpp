#include<bits/stdc++.h>
/*
CF5D Follow Traffic Rules
https://www.luogu.org/blog/user48611/cf5d-follow-traffic-rules
*/
using namespace std;
int main(){
    double a, v, l, d, w ,v0;
    double time1, time2, time3, time4, total;/*double 精度足够*/
    cin >> a >> v >> l >> d >> w;
    /*若限速大于等于v 则速度达到v之前可以一直加速行驶*/
    if(w >= v){ 
        if((v * v / (2.0 * a)) <= l){ 
            time1 = v / a, time2 = (l - (v * v / (2.0 * a) ) ) / v; 
            total = time1 + time2;
        } /*加速到v后 匀速到达终点*/
        else total = sqrt( 2.0 * l / a); 
        /*全程加速到达终点*/
    }
    /*若限速小于v 到达d的速度必须为w 并且之后速度达到v && 到终点之前可以一直加速行驶*/
        //计算从d 到 l 的时间
    if( (v * v - (w * w) ) / (2.0 * a) >= l - d)
        time4 = (-w + sqrt(w * w - (2 * a * (d - l)))) / a;
        //直接加速到终点 wt + 1/2t^2 = l - d 
    else 
        time4 = (v - w) / a + ((l - d - ( (v * v - w * w ) / (2.0 * a) ))) / v ;
         //先加速再匀速到达终点 
    /*0 - d 加速到v对应的 s < d */
    if(w < v && v * v < 2.0 * a * d){
        if( (v * v + (v * v) - (w * w) ) / (2.0 * a) < d){
            //加速到v 匀速time3 再从 v 减速到 w 
            time1 = v / a ;
            time2 = (v - w) / a;
            time3 = (d - ((2 * v * v - (w * w) ) / (2.0 * a))) / v;
            total = time1 + time2 + time3 + time4;
        } else {
            //则加速到一个比w大的v0再减速到w
            v0 = sqrt( w * w /2.0 + (a * d));
            total = v0 / a + (v0 - w) / a + time4;
        }
    }
    /*0 - d 加速到v对应的 s >= d */
    if(w < v && v * v >= 2.0 * a * d){
        if( w * w / (2.0 * a) >= d){
            if((v * v / (2.0 * a)) <= l){
                time1 = v / a, time2 = (l - (v * v / (2.0 * a) ) ) / v; 
                total = time1 + time2;
            }
            else total = sqrt( 2.0 * l / a);
        } else {
            v0 = sqrt( w * w /2.0 + (a * d));
            total = v0 / a + (v0 - w) / a + time4; 
        }
    }
    printf("%.7f", total);
    return 0;
}